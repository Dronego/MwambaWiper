/*
 * MwambaWiper — autonomous underwater optical-window wiper
 * Prototype firmware: ESP32 Arduino / PlatformIO
 *
 * The servo is open-loop: the journal records commands and timing, not verified
 * physical movement. Tune pulse limits and travel time on the assembled mechanism.
 */
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <LittleFS.h>
#include <Wire.h>
#include <RTClib.h>
#include <ESP32Servo.h>

// ---- Board configuration: replace these placeholders for the DG-Core board ----
static constexpr uint8_t SERVO_PIN = 5;
static constexpr int I2C_SDA_PIN = 8;
static constexpr int I2C_SCL_PIN = 9;
// Define MW_USE_PCF8523 in build_flags to use a PCF8523 instead of DS3231.
#ifdef MW_USE_PCF8523
RTC_PCF8523 rtc;
#else
RTC_DS3231 rtc;
#endif

static constexpr char LOG_PATH[] = "/events.csv";
static constexpr uint16_t SAFE_PULSE_MIN_US = 900;
static constexpr uint16_t SAFE_PULSE_MAX_US = 2100;
static constexpr uint32_t DEFAULT_INTERVAL_MIN = 360;
static constexpr uint16_t DEFAULT_STROKES = 3;
static constexpr uint16_t DEFAULT_TRAVEL_MS = 1200;
static constexpr uint16_t DEFAULT_GAP_MS = 500;
static constexpr uint16_t DEFAULT_PULSE_A_US = 1250;
static constexpr uint16_t DEFAULT_PULSE_B_US = 1750;
static constexpr uint16_t DEFAULT_PARK_US = 1500;

struct Config {
  uint32_t intervalMin = DEFAULT_INTERVAL_MIN;
  uint16_t strokes = DEFAULT_STROKES;
  uint16_t travelMs = DEFAULT_TRAVEL_MS;
  uint16_t gapMs = DEFAULT_GAP_MS;
  uint16_t pulseAUs = DEFAULT_PULSE_A_US;
  uint16_t pulseBUs = DEFAULT_PULSE_B_US;
  uint16_t parkUs = DEFAULT_PARK_US;
};

enum class Stage : uint8_t { IDLE, POSITION, SWEEP, GAP, PARK };
Config cfg;
Preferences prefs;
WebServer server(80);
Servo wiper;
bool fsReady = false;
bool rtcReady = false;
bool servoAttached = false;
uint64_t nextDueEpoch = 0;
Stage stage = Stage::IDLE;
uint16_t strokesDone = 0;
uint16_t nextPulseUs = 0;
uint32_t stageDueMs = 0;
String cycleSource = "AUTO";

const char *stageName(Stage value) {
  switch (value) {
    case Stage::POSITION: return "POSITION";
    case Stage::SWEEP: return "SWEEP";
    case Stage::GAP: return "GAP";
    case Stage::PARK: return "PARK";
    default: return "IDLE";
  }
}

String timestampLocal() {
  if (!rtcReady) return "NO_RTC";
  DateTime now = rtc.now();
  return String(now.timestamp(DateTime::TIMESTAMP_FULL));
}

void appendLog(const char *eventName, int stroke = -1, int pulseUs = -1,
               const String &detail = "") {
  if (!fsReady) return;
  File file = LittleFS.open(LOG_PATH, FILE_APPEND);
  if (!file) return;
  file.printf("%s,%lu,%s,%d,%d,%u,%lu,%s\n",
              timestampLocal().c_str(),
              static_cast<unsigned long>(millis()),
              eventName,
              stroke,
              pulseUs,
              cfg.strokes,
              static_cast<unsigned long>(cfg.intervalMin),
              detail.c_str());
  file.close();
}

void loadConfig() {
  prefs.begin("mw-wiper", false);
  cfg.intervalMin = prefs.getUInt("interval", DEFAULT_INTERVAL_MIN);
  cfg.strokes = prefs.getUShort("strokes", DEFAULT_STROKES);
  cfg.travelMs = prefs.getUShort("travel", DEFAULT_TRAVEL_MS);
  cfg.gapMs = prefs.getUShort("gap", DEFAULT_GAP_MS);
  cfg.pulseAUs = prefs.getUShort("pulseA", DEFAULT_PULSE_A_US);
  cfg.pulseBUs = prefs.getUShort("pulseB", DEFAULT_PULSE_B_US);
  cfg.parkUs = prefs.getUShort("park", DEFAULT_PARK_US);
  nextDueEpoch = prefs.getULong64("nextDue", 0);
}

void saveConfig() {
  prefs.putUInt("interval", cfg.intervalMin);
  prefs.putUShort("strokes", cfg.strokes);
  prefs.putUShort("travel", cfg.travelMs);
  prefs.putUShort("gap", cfg.gapMs);
  prefs.putUShort("pulseA", cfg.pulseAUs);
  prefs.putUShort("pulseB", cfg.pulseBUs);
  prefs.putUShort("park", cfg.parkUs);
}

String getOrCreateApPassword() {
  String password = prefs.getString("apPass", "");
  if (password.length() >= 12) return password;
  char generated[13];
  snprintf(generated, sizeof(generated), "MW%08lX%02X",
           static_cast<unsigned long>(esp_random()),
           static_cast<unsigned int>(esp_random() & 0xFF));
  password = String(generated);
  prefs.putString("apPass", password);
  return password;
}

String apSsid() {
  uint64_t mac = ESP.getEfuseMac();
  char ssid[32];
  snprintf(ssid, sizeof(ssid), "MwambaWiper-%04X",
           static_cast<unsigned int>((mac >> 32) & 0xFFFF));
  return String(ssid);
}

void commandServo(uint16_t pulseUs) {
  if (!servoAttached) {
    wiper.setPeriodHertz(50);
    servoAttached = wiper.attach(SERVO_PIN, 500, 2500);
  }
  if (servoAttached) wiper.writeMicroseconds(pulseUs);
}

bool startCycle(const String &source) {
  if (stage != Stage::IDLE || !servoAttached && wiper.attached() == false) {
    // Servo.attach is performed lazily by commandServo; only reject an active cycle.
    if (stage != Stage::IDLE) return false;
  }
  cycleSource = source;
  strokesDone = 0;
  commandServo(cfg.pulseAUs);  // Uncounted move to the first edge.
  stage = Stage::POSITION;
  stageDueMs = millis() + cfg.travelMs;
  appendLog(source == "MANUAL" ? "MANUAL_REQUEST" : "CYCLE_START",
            -1, cfg.pulseAUs, source);
  appendLog("POSITION_START", -1, cfg.pulseAUs, source);
  return servoAttached;
}

void finishCycle() {
  appendLog("CYCLE_END", strokesDone, cfg.parkUs,
            cycleSource + "_COMMANDS_SENT_NO_POSITION_FEEDBACK");
  stage = Stage::IDLE;
}

void serviceCycle() {
  if (stage == Stage::IDLE ||
      static_cast<int32_t>(millis() - stageDueMs) < 0) return;

  if (stage == Stage::POSITION) {
    nextPulseUs = cfg.pulseBUs;
    commandServo(nextPulseUs);
    stage = Stage::SWEEP;
    stageDueMs = millis() + cfg.travelMs;
    appendLog("STROKE_CMD", 1, nextPulseUs, cycleSource);
    return;
  }

  if (stage == Stage::SWEEP) {
    strokesDone++;
    if (strokesDone >= cfg.strokes) {
      commandServo(cfg.parkUs);
      stage = Stage::PARK;
      stageDueMs = millis() + cfg.travelMs;
      appendLog("PARK_CMD", strokesDone, cfg.parkUs, cycleSource);
    } else {
      nextPulseUs = (strokesDone % 2 == 1) ? cfg.pulseAUs : cfg.pulseBUs;
      stage = Stage::GAP;
      stageDueMs = millis() + cfg.gapMs;
    }
    return;
  }

  if (stage == Stage::GAP) {
    commandServo(nextPulseUs);
    stage = Stage::SWEEP;
    stageDueMs = millis() + cfg.travelMs;
    appendLog("STROKE_CMD", strokesDone + 1, nextPulseUs, cycleSource);
    return;
  }

  if (stage == Stage::PARK) {
    finishCycle();
  }
}

void serviceSchedule() {
  if (!rtcReady || stage != Stage::IDLE) return;
  const uint64_t nowEpoch = rtc.now().unixtime();
  if (nextDueEpoch == 0) {
    nextDueEpoch = nowEpoch + static_cast<uint64_t>(cfg.intervalMin) * 60ULL;
    prefs.putULong64("nextDue", nextDueEpoch);
  } else if (nowEpoch >= nextDueEpoch) {
    nextDueEpoch = nowEpoch + static_cast<uint64_t>(cfg.intervalMin) * 60ULL;
    prefs.putULong64("nextDue", nextDueEpoch); // One cycle after downtime; no catch-up burst.
    startCycle("AUTO");
  }
}

String jsonStatus() {
  String json = "{";
  json += "\"now\":\"" + timestampLocal() + "\",";
  json += "\"rtc_ok\":" + String(rtcReady ? "true" : "false") + ",";
  json += "\"fs_ok\":" + String(fsReady ? "true" : "false") + ",";
  json += "\"active\":" + String(stage != Stage::IDLE ? "true" : "false") + ",";
  json += "\"stage\":\"" + String(stageName(stage)) + "\",";
  json += "\"strokes_done\":" + String(strokesDone) + ",";
  json += "\"strokes_target\":" + String(cfg.strokes) + ",";
  json += "\"interval_min\":" + String(cfg.intervalMin) + ",";
  json += "\"next_due_epoch\":" + String(static_cast<unsigned long long>(nextDueEpoch));
  json += "}";
  return json;
}

bool readConfigFromRequest(Config &candidate) {
  candidate.intervalMin = server.arg("interval_min").toInt();
  candidate.strokes = server.arg("strokes").toInt();
  candidate.travelMs = server.arg("travel_ms").toInt();
  candidate.gapMs = server.arg("gap_ms").toInt();
  candidate.pulseAUs = server.arg("pulse_a_us").toInt();
  candidate.pulseBUs = server.arg("pulse_b_us").toInt();
  candidate.parkUs = server.arg("park_us").toInt();
  if (candidate.intervalMin < 1 || candidate.intervalMin > 43200) return false;
  if (candidate.strokes < 1 || candidate.strokes > 20) return false;
  if (candidate.travelMs < 250 || candidate.travelMs > 5000) return false;
  if (candidate.gapMs > 10000) return false;
  if (candidate.pulseAUs < SAFE_PULSE_MIN_US ||
      candidate.pulseAUs > SAFE_PULSE_MAX_US) return false;
  if (candidate.pulseBUs < SAFE_PULSE_MIN_US ||
      candidate.pulseBUs > SAFE_PULSE_MAX_US) return false;
  if (candidate.parkUs < SAFE_PULSE_MIN_US ||
      candidate.parkUs > SAFE_PULSE_MAX_US) return false;
  if (abs(static_cast<int>(candidate.pulseAUs) -
          static_cast<int>(candidate.pulseBUs)) < 100) return false;
  return true;
}

void handleConfig() {
  if (stage != Stage::IDLE) {
    server.send(409, "application/json", "{\"ok\":false,\"error\":\"cycle_active\"}");
    return;
  }
  Config candidate;
  if (!readConfigFromRequest(candidate)) {
    server.send(400, "application/json", "{\"ok\":false,\"error\":\"invalid_config\"}");
    return;
  }
  cfg = candidate;
  saveConfig();
  if (rtcReady) {
    nextDueEpoch = rtc.now().unixtime() + static_cast<uint64_t>(cfg.intervalMin) * 60ULL;
    prefs.putULong64("nextDue", nextDueEpoch);
  }
  appendLog("CONFIG_UPDATE");
  server.send(200, "application/json", "{\"ok\":true}");
}

void handleSetTime() {
  String value = server.arg("value"); // YYYY-MM-DDTHH:MM, local wall time
  int y = value.substring(0, 4).toInt();
  int mo = value.substring(5, 7).toInt();
  int d = value.substring(8, 10).toInt();
  int h = value.substring(11, 13).toInt();
  int mi = value.substring(14, 16).toInt();
  if (!rtcReady || value.length() < 16 || y < 2024 || mo < 1 || mo > 12 ||
      d < 1 || d > 31 || h > 23 || mi > 59) {
    server.send(400, "application/json", "{\"ok\":false,\"error\":\"invalid_time\"}");
    return;
  }
  rtc.adjust(DateTime(y, mo, d, h, mi, 0));
  nextDueEpoch = rtc.now().unixtime() + static_cast<uint64_t>(cfg.intervalMin) * 60ULL;
  prefs.putULong64("nextDue", nextDueEpoch);
  appendLog("RTC_SET");
  server.send(200, "application/json", "{\"ok\":true}");
}

void setupRoutes() {
  server.on("/", HTTP_GET, []() {
    File page = fsReady ? LittleFS.open("/index.html", FILE_READ) : File();
    if (page) {
      server.streamFile(page, "text/html; charset=utf-8");
      page.close();
    } else {
      server.send(503, "text/plain; charset=utf-8",
                  "Interface missing: upload firmware/data with pio run -t uploadfs");
    }
  });
  server.on("/api/status", HTTP_GET, []() {
    server.send(200, "application/json", jsonStatus());
  });
  server.on("/api/config", HTTP_POST, handleConfig);
  server.on("/api/run", HTTP_POST, []() {
    if (stage != Stage::IDLE) {
      server.send(409, "application/json", "{\"ok\":false,\"error\":\"cycle_active\"}");
      return;
    }
    bool started = startCycle("MANUAL");
    server.send(started ? 200 : 500, "application/json",
                started ? "{\"ok\":true}" : "{\"ok\":false,\"error\":\"servo_attach_failed\"}");
  });
  server.on("/api/time", HTTP_POST, handleSetTime);
  server.on("/events.csv", HTTP_GET, []() {
    if (!fsReady || !LittleFS.exists(LOG_PATH)) {
      server.send(404, "text/plain", "Journal not available");
      return;
    }
    File file = LittleFS.open(LOG_PATH, FILE_READ);
    server.sendHeader("Content-Disposition", "attachment; filename=mwambawiper-events.csv");
    server.streamFile(file, "text/csv; charset=utf-8");
    file.close();
  });
  server.onNotFound([]() { server.send(404, "text/plain", "Not found"); });
}

void setup() {
  Serial.begin(115200);
  delay(100);
  loadConfig();

  fsReady = LittleFS.begin(false);
  if (fsReady && !LittleFS.exists(LOG_PATH)) {
    File file = LittleFS.open(LOG_PATH, FILE_WRITE);
    if (file) {
      file.println("timestamp_local,uptime_ms,event,stroke,target_us,stroke_count,interval_min,detail");
      file.close();
    }
  }

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  rtcReady = rtc.begin();
  if (rtcReady) {
    if (rtc.lostPower()) appendLog("RTC_ERROR", -1, -1, "RTC_LOST_POWER_SET_TIME_IN_WEB_UI");
  } else {
    appendLog("RTC_ERROR", -1, -1, "RTC_NOT_FOUND_AUTO_SCHEDULE_DISABLED");
  }

  const String ssid = apSsid();
  const String password = getOrCreateApPassword();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid.c_str(), password.c_str());
  Serial.println();
  Serial.println("MwambaWiper local access point");
  Serial.printf("SSID: %s\nPassword: %s\nURL: http://192.168.4.1\n",
                ssid.c_str(), password.c_str());

  setupRoutes();
  server.begin();
  appendLog("BOOT", -1, -1, rtcReady ? "RTC_OK" : "RTC_MISSING");
}

void loop() {
  server.handleClient();
  serviceCycle();
  serviceSchedule();
  delay(2);
}
