# Nomenclature initiale — MwambaWiper

BOM de prototype. Les références sans quantité ou sans spécification finale sont à confirmer avant achat. Aucun coût n’est figé ici.

| Qté | Sous-ensemble | Élément / spécification de départ | Statut / remarque |
|---:|---|---|---|
| 1 | Actionneur | Servo numérique immergeable ROVMAKER, probablement modèle 15 kg·cm (masse mesurée/annoncée : 213 g) | Hypothèse d’identification à confirmer par référence ; le fabricant indique pour le 15 kg : 12–28 V, PWM 50 Hz, 0,2–0,6 A. Vérifier la fiche de l’exemplaire et le courant sous charge |
| 1 | Connectique caisson | Cobalt bulkhead 3 broches, M10 × 1,5, traversée 10 mm | À monter sur une surface plane et lisse ; 3-pin standard ou 3-pin Power à sélectionner |
| 1 | Connectique câble | Cobalt cable termination kit assorti au bulkhead et au câble servo | Vérifier diamètre/type de gaine, coque régulière/grande, outil de terminaison et résine de potting |
| 1 | Câble | Câble trois conducteurs : servo +V, 0 V, PWM | Section selon courant, longueur, chute de tension et choix de kit |
| 1 | Caisson commande | Tube aluminium 2 pouces, longueur 150 mm, avec bouchons/joints adaptés | Boîtier indiqué par le projet ; relever les dimensions réelles |
| 1 | Support interne | DG-Core / support électronique démontable | Géométrie et matériau à confirmer avec le caisson |
| 1 | Contrôleur | Carte ESP32 (ESP32-S3 envisagé) | Référence à choisir ; GPIO PWM/I²C à configurer |
| 1 | Horloge | RTC DS3231 (firmware par défaut) ou PCF8523 | Choisir le module exact, batterie de sauvegarde et niveau logique I²C |
| 1 | Stockage journal | LittleFS dans la mémoire flash ESP32 | Pas de carte SD pour le premier prototype |
| 1 | Batterie | Pack rechargeable protégé, capacité dimensionnée sur l’autonomie cible | Chimie, tension et capacité à définir après mesure du courant et du temps d’usage Wi‑Fi |
| 1 | Conversion servo | Alimentation régulée dans la plage confirmée du servo, avec marge sur le courant mesuré sous charge | Valeurs constructeur du modèle 15 kg à confirmer pour l’exemplaire reçu ; ne pas alimenter depuis la carte ESP32 |
| 1 | Conversion logique | Régulateur adapté à la carte ESP32 / RTC | Dimensionner selon la carte retenue et les pics radio |
| 1 | Protection | Fusible ou protection électronique sur la branche servo | Valeur à choisir après mesure du courant de blocage/pointe et de la capacité du convertisseur |
| 1 | Interruption de puissance | Interrupteur existant du caisson | Identifier s’il coupe toute l’alimentation ou commande une entrée logique |
| 1 | Signalisation | LED existante du caisson | Identifier couleur, résistance/driver et raccordement |
| 1 | Mécanique d’essuyage | Bras, moyeu/palonnier et fixation anti-desserrage | Dessin à finaliser après relevé de la tête optique et du servo |
| 1 | Contact d’essuyage | Lèvre souple remplaçable | Matière à choisir après essais sur le matériau du hublot |
| 1 | Support servo | Bride/support démontable et anticorrosion | À dimensionner selon plan coté du servo |
| 1 | Consommables d’étanchéité | Joint, potting compatible, protection anticorrosion/isolante | Respecter les instructions de terminaison du fabricant et la portée des joints |

## Contrôles avant commande

- Confirmer le modèle servo et sa plage de tension : la page ROVMAKER décrit une famille de servos, le modèle probable est le 15 kg·cm (213 g), mais sa référence et sa fiche électrique doivent être confirmées.
- Confirmer la charge électrique de chaque broche du Cobalt, la terminaison mâle/femelle, le diamètre du câble et l’outil compatible.
- Vérifier que le bouchon offre une surface plane et lisse autour du joint torique du bulkhead.
- Calculer l’autonomie à partir du courant réel au repos, pendant le Wi‑Fi et pendant chaque cycle de brossage.
- Vérifier la compatibilité chimique de la lèvre avec le PMMA/verre/diffuseur et son absence de rayures après essais.
- Mesurer le courant de pointe et le courant de blocage avant de choisir convertisseur, section de câble et fusible.

## Sources

- [Servo numérique sous-marin ROVMAKER](https://rovmaker.org/product/underwater-digital-servo/)
- [Données ROVMAKER du servo 15 kg : PWM 50 Hz, 12–28 V, 0,2–0,6 A](https://forum.rovmaker.org/t/topic/2017)
- [Bulkhead Cobalt Blue Trail Engineering](https://www.bluetrailengineering.com/product-page/cobalt-series-bulkhead-connector)
- [Kit de terminaison Cobalt Blue Trail Engineering](https://www.bluetrailengineering.com/product-page/cable-termination-kit)
