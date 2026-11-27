# MwambaWiper

**Essuie-glace sous-marin autonome pour surfaces optiques** — projet Mwamba Électronique.

MwambaWiper pilote un servomoteur submersible ROVMAKER afin de balayer la fenêtre optique d’un capteur et d’y limiter les dépôts. Le premier prototype est autonome : batterie, ESP32 et RTC dans un caisson aluminium de 2 pouces et 150 mm, avec commande du servo via une traversée Cobalt et un câble dédié.

## Fonctions prévues

- Réglage Wi‑Fi du nombre de passages par cycle, de l’intervalle entre cycles, du temps de déplacement et des positions du servo.
- Déclenchement automatique sur horloge RTC et commande manuelle depuis l’interface.
- Journal horodaté exportable en CSV.
- Repérage des périodes de brossage et de stabilisation pour leur mise en regard avec les mesures optiques MwambaPAR/MwambaSpecDT.
- Interface locale portant la marque **Mwamba Électronique**.

## Architecture prototype

- **Actionneur :** servo numérique sous-marin ROVMAKER (référence exacte et tension à confirmer à réception).
- **Traversée :** Cobalt bulkhead 3 broches, M10 × 1,5, monté sur une surface plane/lisse du bouchon du caisson.
- **Câble :** connecteur Cobalt associé et terminaison compatible avec le câble réel du servo.
- **Contrôleur :** carte ESP32 (modèle à confirmer), servo commandé en PWM.
- **Temps :** RTC DS3231 par défaut dans le firmware ; possibilité de basculer vers PCF8523.
- **Journal :** mémoire flash LittleFS pour le prototype.
- **Boîtier :** tube aluminium 2 pouces, longueur 150 mm, avec LED et interrupteur existants. Géométrie et interfaces à relever avant plan coté.

## Démarrage logiciel

Le firmware est une base Arduino/PlatformIO. Avant compilation et câblage, régler les broches de la carte dans `firmware/src/main.cpp` et sélectionner le modèle de carte dans `firmware/platformio.ini`. L’interface est servie depuis LittleFS :

```sh
cd firmware
pio run
pio run -t upload
pio run -t uploadfs
```

Au premier démarrage, le point d’accès Wi‑Fi crée un SSID et un mot de passe aléatoire, affichés sur le moniteur série. L’interface est disponible à `http://192.168.4.1`.

## Sécurité et limites du prototype

- La fin d’un cycle signifie que les commandes PWM ont été émises et temporisées. Le servo trois fils ne renvoie pas sa position : le système ne confirme donc pas mécaniquement que la brosse a bougé.
- Les impulsions min/max et la course doivent être réglées progressivement à sec, puis dans l’eau, sans atteindre les butées mécaniques.
- La puissance servo doit être régulée séparément de l’ESP32. Dimensionner batterie, convertisseur, câblage, protection et autonomie après mesure du courant réel.
- Le boîtier aluminium et la traversée inox 316 doivent être protégés contre la corrosion galvanique en eau de mer.
- Le premier firmware garde le Wi‑Fi actif pour faciliter la mise au point ; l’autonomie réelle reste à mesurer.

## Documents

- [Séquences de fonctionnement et de mesure](docs/SEQUENCES_MESURE.md)
- [Schéma mécanique conceptuel](mechanical/SCHEMA_CONCEPTUEL.md)
- [Nomenclature initiale (BOM)](BOM.md)
- [Firmware](firmware/src/main.cpp)
- [Interface web](firmware/data/index.html)

## Sources matérielles

- [ROVMAKER — Underwater Digital Servo](https://rovmaker.org/product/underwater-digital-servo/)
- [Blue Trail Engineering — Cobalt Series Bulkhead Connector](https://www.bluetrailengineering.com/product-page/cobalt-series-bulkhead-connector)
- [Blue Trail Engineering — Cobalt Series Cable Termination Kit](https://www.bluetrailengineering.com/product-page/cable-termination-kit)

## État

Prototype fonctionnel en préparation. Les choix de séquence et le firmware sont une première base ; le modèle exact de servo, la carte ESP32, les cotes de la tête optique, le raccordement du commutateur/LED et la capacité batterie restent à confirmer.
