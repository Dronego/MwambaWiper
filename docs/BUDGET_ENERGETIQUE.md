# Budget énergétique — choix du pack 3S

## Données de départ

Le pack envisagé est un lithium 3S de 3 000 ou 5 000 mAh. Un pack 3S LiPo courant est nominalement à 11,1 V et atteint 12,6 V en fin de charge ; sa tension diminue ensuite pendant la décharge. Les valeurs exactes de coupure, de charge et de courant admissible doivent venir de la fiche du pack choisi.

| Pack 3S | Énergie nominale calculée à 11,1 V | Comparaison |
|---|---:|---|
| 3 000 mAh (3 Ah) | 33,3 Wh | Base |
| 5 000 mAh (5 Ah) | 55,5 Wh | 1,67 × la capacité nominale |

Ces énergies sont théoriques. L’énergie réellement exploitable sera inférieure en fonction de la tension de coupure retenue, du rendement des convertisseurs, de la température, de l’âge du pack et du courant demandé.

## Deux rails d’alimentation

### Logique : 5 V

Le régulateur 5 V déjà utilisé sur le grand PCB circulaire sera également intégré au PCB de 2 pouces. Il alimentera la carte ESP32 et la logique/RTC selon leurs exigences électriques. Le courant admissible et l’échauffement du régulateur doivent être vérifiés avec le Wi‑Fi actif et les périphériques réellement montés.

Sur la Feather ESP32-S3 retenue (4 Mo flash / 2 Mo PSRAM), amener le 5 V régulé sur la broche **USB** et relier le 0 V à **GND**. Ne pas appliquer 5 V sur **BAT** ni sur **3V** : BAT est le rail batterie LiPo/chargeur et 3V est la sortie régulée 3,3 V. Éviter d’alimenter cette broche USB depuis le régulateur pendant qu’un câble USB est connecté à un ordinateur, car cela peut renvoyer le 5 V vers le port hôte; couper l’alimentation externe avant la programmation USB, ou prévoir une isolation matérielle appropriée.

### Servo : rail dédié

La documentation ROVMAKER retrouvée pour le servo 15 kg indique une plage d’alimentation de 12–28 V, un signal PWM 50 Hz et un courant de 0,2–0,6 A. Le servo reçu de 213 g est probablement cette variante, mais la référence exacte et le courant sous charge restent à confirmer.

Un pack 3S ne fournit pas 12 V régulés sur toute sa décharge : il est nominalement à 11,1 V et peut descendre sous 12 V. Si la plage 12–28 V est confirmée, prévoir un **convertisseur buck-boost dédié réglé à 12 V** entre le pack et le servo. Ne pas relier le servo à la sortie 5 V du PCB. Relier le 0 V logique et le 0 V servo en commun pour référencer la commande PWM, selon le schéma de masse retenu.

Le courant de sortie du convertisseur, le câblage, le connecteur et la protection doivent être dimensionnés à partir du courant mesuré pendant un mouvement chargé et lors d’un effort mécanique maximal. La valeur 0,2–0,6 A citée par le fabricant ne remplace pas une mesure sur le montage final.

## Estimer l’autonomie

Mesurer le courant **à l’entrée batterie**, boîtier fermé, dans le mode d’usage réel. Le Wi‑Fi du firmware initial reste actif ; il peut représenter une part majeure de la consommation moyenne. Relever séparément :

1. le courant de repos avec Wi‑Fi actif et sans cycle ;
2. le courant de repos avec Wi‑Fi désactivé, si ce mode est ajouté ;
3. l’énergie consommée par un cycle complet, avec le nombre et le délai de passages retenus ;
4. la consommation des cartes de régulation 5 V et 12 V, y compris leur courant propre ;
5. la tension du pack sous charge et à la fin de l’essai.

Si la consommation est mesurée à l’entrée batterie :

`Autonomie (h) ≈ énergie réellement utilisable du pack (Wh) / puissance moyenne mesurée à l’entrée batterie (W)`

Pour une mesure en courant :

`Autonomie (h) ≈ capacité utilisable du pack (Ah) / courant moyen à l’entrée batterie (A)`

On peut décomposer la puissance moyenne ainsi :

`P_moy ≈ P_repos + (nombre de cycles par jour × énergie d’un cycle) / 24 h`

La capacité 5 000 mAh apporte environ 67 % d’énergie nominale de plus que la 3 000 mAh à tension identique, mais elle ne garantit pas une autonomie donnée. Il faut d’abord mesurer le repos Wi‑Fi et l’énergie d’un cycle.

## Conditions d’intégration

- Vérifier que le pack choisi entre dans le diamètre intérieur utile du tube 2 pouces de 150 mm avec le DG-Core, les cartes et le câblage.
- Confirmer le courant de décharge continu et de pointe du pack, la protection, le connecteur, l’équilibrage et la méthode de recharge.
- Ne pas faire reposer la sécurité du pack uniquement sur la tension lue par l’ESP32.
- Contrôler l’échauffement du régulateur 5 V et du convertisseur 12 V dans le volume fermé.
- Fixer le pack pour éviter qu’il se déplace ou tire sur les connexions.

## Sources matérielles

- [ROVMAKER — caractéristiques du servo 15 kg (forum constructeur)](https://forum.rovmaker.org/t/topic/2017)
- [Exemple de fiche technique d’un pack LiPo 3S 11,1 V / 12,6 V](https://tracerpower.com/wp-content/uploads/2022/11/BP2545-Data-Sheet.pdf)
