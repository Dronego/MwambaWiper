# Référence — stratégies anti-biofouling pour capteurs aquatiques

## Référence bibliographique

Delgado, A., Briciu-Burghina, C. & Regan, F. (2021). *Antifouling Strategies for Sensors Used in Water Monitoring: Review and Future Perspectives*. **Sensors, 21**(2), 389. https://doi.org/10.3390/s21020389

[Article en accès ouvert (MDPI)](https://www.mdpi.com/1424-8220/21/2/389)

## Résultats utiles au projet

Cette revue couvre les méthodes anti-biofouling utilisées sur les capteurs de suivi de l’eau. Elle rappelle que les dépôts biologiques sur les fenêtres optiques peuvent perturber le signal et provoquer une dérive des données. Les systèmes de nettoyage mécanique par brosse ou essuie-glace sont employés sur des sondes commerciales et peuvent être intégrés ou ajoutés comme module autonome.

La revue souligne aussi les limites à traiter dès la conception : abrasion de la fenêtre, usure et remplacement de la lèvre, blocage du mécanisme par du macrofouling, consommation électrique qui réduit l’autonomie, et risque de corrosion ou d’entrée d’eau au niveau des arbres, moteurs et connecteurs submersibles. Elle recommande une conception adaptée au capteur et à son matériau optique ; il n’existe pas de solution universelle.

## Conséquences pour MwambaWiper

1. **Protéger la fenêtre.** Choisir la matière et la pression de la lèvre à partir d’essais répétés sur le hublot réel. Inspecter la fenêtre après essais d’abrasion ; une brosse plus dure n’est pas automatiquement préférable.
2. **Rendre la pièce d’usure remplaçable.** Concevoir la lèvre/brush insert et son support comme consommables démontables, sans devoir remplacer le servo.
3. **Limiter les blocages.** Prévoir des jeux qui tolèrent les particules, éviter les pièges à sédiments et vérifier que le mouvement reste libre après dépôt/salissure.
4. **Protéger les interfaces.** Traiter l’étanchéité du servo, du câble Cobalt et de la traversée du caisson ; surveiller corrosion et état des joints après immersion.
5. **Mesurer l’énergie réelle.** Ajouter au budget énergétique l’énergie d’un cycle complet et le courant de repos du Wi‑Fi ; un essuie-glace sous tension peut réduire la durée d’un déploiement.
6. **Garder la traçabilité scientifique.** Journaliser départ/fin et paramètres des cycles, conserver les mesures brutes pendant/après nettoyage et marquer les fenêtres de stabilisation pour analyse.
7. **Qualifier sur le capteur final.** Comparer réponse et répétabilité avant/après cycles de nettoyage et avant/après déploiement. La revue ne valide pas le design MwambaWiper en particulier : ces essais restent à mener.

## Statut

La revue soutient la pertinence du besoin et fournit des critères de conception. Elle ne détermine ni la matière optimale de la lèvre pour le PMMA/diffuseur Mwamba, ni la pression de contact, ni la fréquence de brossage : ces choix doivent être établis expérimentalement sur le prototype.
