# Gisi et al. (I.S. Rivers 2025) — sources et concepts utiles à MwambaWiper

## Document étudié

Gisi, M. F. S. et al. (2025), *Clean sensors, happy data: Field test of low-tech wiper designs for optical sensors and river applications* / *Capteurs propres, données fiables…*, poster I.S. RIVERS 2025, Lyon. [PDF du poster](https://www.graie.org/graie/graiedoc/doc_telech/ISRIV25/I.S.RIVERS%202025_Resumes_etendus/D3/Posters/D3-ISR25-102-Gisi-Maria.pdf). Il s’agit d’un poster de conférence, pas d’un article de revue avec protocole complet.

Le projet open source associé est [Turbidity_01](https://github.com/mariagisi/Turbidity_01). La branche [Wiper](https://github.com/mariagisi/Turbidity_01/tree/Wiper) contient notamment un [schéma du wiper](https://github.com/mariagisi/Turbidity_01/blob/Wiper/wiper%20schematic%20(1).pdf), une [liste de pièces](https://github.com/mariagisi/Turbidity_01/blob/Wiper/Shopping%20list-wiper.txt) et un support sur la consommation.

## Ce que montre le concept mécanique

Le dispositif transmet l’effort sans moteur immergé : un actionneur linéaire sec pousse une seringue; de l’eau dans un tube PVC transmet la pression à une seconde seringue qui déplace une brosse en nylon. Le poster donne un actionneur de 150 N, un balayage de 10 s chaque heure, et place actionneur, carte, batterie et panneau solaire dans un boîtier sec hors du cours d’eau. Les pièces immergées sont des pièces passives (PP, PVC, inox). La liste de pièces de la branche Wiper mentionne un actionneur 12 V, course 30 mm, force annoncée 180 N, vitesse à vide 5 mm/s, des seringues Luer 5 mL, un tube/raccord Luer et une brosse nylon.

Le principe de transmission hydraulique découple l’actionnement électrique de la tête mouillée. Il réduit les traversées électriques immergées, mais ajoute tuyau, raccords, seringues et fluide à maintenir étanches et sans bulles. Il faut distinguer la force nominale annoncée par la fiche d’achat (180 N) de la valeur utilisée dans le poster (150 N); la force réellement appliquée à la brosse n’est pas donnée.

## Résultats : lecture prudente

Le poster décrit 11 semaines d’exposition dans un bassin de jardin à Melbourne. Le capteur SEN0189 mesure par atténuation lumineuse à 940 nm. Les lectures de suivi sont faites deux fois par semaine dans deux solutions de bentonite (0 et 1 000 NTU), et l’encrassement est évalué visuellement / par images. Les auteurs comparent protection mécanique, ruban de cuivre et contrôle.

La méthode détaillée indique six coques, deux par traitement, et une seule sonde turbidimétrique passée successivement dans les coques. Il faut donc lire les données comme un petit essai avec deux répétitions de coque par traitement, et des mesures répétées, pas comme six instruments indépendants. À 1 000 NTU, la pente du capteur 1 protégé mécaniquement n’est pas significative (p = 0,889); pour le contrôle du capteur 3 à 0 NTU, elle l’est (p = 0,000359). Un p élevé signifie qu’une tendance n’a pas été détectée dans ces données; il ne prouve ni l’absence de dérive ni la stabilité à long terme. Deux étalons extrêmes ne caractérisent pas toute la linéarité, la répétabilité ou l’exactitude d’un capteur.

Le résultat soutient l’intérêt de tester un essuie-glace et un protocole avant/après. Il ne donne pas une fréquence universelle d’essuyage ni une performance garantie sur un capteur différent.

## Concepts à retenir pour MwambaWiper

1. **Biofilm = biais optique possible.** Une couche sur la fenêtre change le trajet lumineux et peut être interprétée comme un changement de l’eau. Les fenêtres, lentilles, fibres et angles de mesure n’ont pas tous la même sensibilité.
2. **Nettoyer uniquement la zone optique utile.** Le montage ne doit ni masquer le faisceau, ni rayer la fenêtre, ni laisser la brosse se désaligner. La géométrie de contact est propre à chaque tête de capteur.
3. **Séparer le mécanisme de la surface optique.** Le projet Gisi garde l’actionneur sec et ne transmet qu’un déplacement mécanique par une liaison hydraulique. MwambaWiper, lui, envisage un servo submersible directement près de la tête : c’est un autre compromis d’étanchéité, d’encombrement et de maintenance.
4. **La fréquence doit être mesurée, pas copiée.** « 10 secondes chaque heure » est le réglage de leur démonstrateur, pas une prescription. Comparer l’intervalle de mesure, la vitesse d’encrassement du site, le nombre de coups et l’énergie par cycle.
5. **Garder un témoin de l’action.** Journaliser l’heure, la durée et la consigne de chaque cycle; analyser séparément les mesures prises pendant le balayage et la stabilisation qui suit.
6. **Concevoir pour l’entretien.** Brosse/lèvre remplaçable, inspectable et accessible; vérifier après essais si des particules abrasives sont entraînées sur la fenêtre.

## Sources citées par le poster et ce qu’elles étayent

- **Ridd, P. & Larcombe, P. (1994).** “Biofouling control for optical backscatter suspended sediment sensors”, *Marine Geology*, 116(3–4), 255–258. [DOI: 10.1016/0025-3227(94)90044-2](https://doi.org/10.1016/0025-3227(94)90044-2). Étude expérimentale directement pertinente : un mécanisme d’essuyage sur un néphélomètre a permis d’allonger le déploiement dans un environnement côtier fortement encrassant. Le poster cite « Strom et al., 1994 » mais cette référence n’apparaît pas dans sa bibliographie; Ridd & Larcombe est une référence de 1994 correspondant précisément au sujet, mais l’attribution doit être vérifiée auprès des auteurs.
- **Downing, J. (2006).** “Twenty-five years with OBS sensors: The good, the bad, and the ugly”, *Continental Shelf Research*, 26, 2299–2318. [DOI: 10.1016/j.csr.2006.07.018](https://doi.org/10.1016/j.csr.2006.07.018). Contexte sur le fonctionnement et les limites des capteurs optiques de rétrodiffusion et les interférences de mesure.
- **Gillett, D. & Marchiori, A. (2019).** “A Low-Cost Continuous Turbidity Monitor”, *Sensors*, 19(14), 3039. [DOI: 10.3390/s19143039](https://doi.org/10.3390/s19143039). Conception et validation d’un turbidimètre économique; utile pour les contraintes de mesure optique, pas une validation du wiper Gisi.
- **Langhorst, T. et al. (2023).** “Increased scale and accessibility of sediment transport research in rivers through practical, open-source turbidity and depth sensors”, *Nature Water*, 1, 760–768. [DOI: 10.1038/s44221-023-00124-2](https://doi.org/10.1038/s44221-023-00124-2). Contexte sur les instruments ouverts et le suivi en rivière, pas une étude d’essuie-glace.
- **Di Pippo, F. et al. (2018).** “Biofilm growth and control in cooling water industrial systems”, *FEMS Microbiology Ecology*, 94(5), fiy044. [DOI: 10.1093/femsec/fiy044](https://doi.org/10.1093/femsec/fiy044). Revue des biofilms et de leur contrôle en circuits industriels; le transfert à une fenêtre optique en rivière est indirect.
- **Gameiro, C. et al. (2011).** “Light control on phytoplankton production in a shallow and turbid estuarine system”, *Hydrobiologia*, 669, 249–263. Étaye le rôle de la lumière pour le phytoplancton; ce n’est pas une mesure directe de la vitesse de biofouling d’un capteur.
- **Austin, Å. N. et al. (2017).** “Relationships between aquatic vegetation and water turbidity…”, *PLOS ONE*, 12(8), e0181419. [DOI: 10.1371/journal.pone.0181419](https://doi.org/10.1371/journal.pone.0181419). Porte sur les liens végétation/turbidité; elle ne semble pas étayer directement l’affirmation du poster selon laquelle un biofilm très mince fausse les capteurs en eau claire.

## Traduction en essais MwambaWiper

Pour valider le système sur une tête MwambaPAR/MwambaSpecDT, faire d’abord un essai de mouvement hors eau puis en eau propre; contrôler l’absence de collision et la course utile. Comparer ensuite, sur le même capteur, une série sans essuyage et une série avec essuyage, en gardant fixes l’éclairage, la position et la séquence de mesure. Enregistrer les valeurs brutes avant le cycle, pendant le cycle et après stabilisation. Inspecter la fenêtre et la brosse à intervalles réguliers; relever le courant et la durée de chaque cycle. Enfin, réaliser un essai de terrain suffisamment long, avec répétitions et étalons qui couvrent la plage réelle du capteur.

Ce protocole est une proposition de validation. Le poster ne démontre pas la compatibilité avec une fenêtre optique Mwamba, avec le servo ROVMAKER, ni avec un caisson de 2 pouces.

## Bibliographie complémentaire du projet

Delgado, A., Briciu-Burghina, C. & Regan, F. (2021). *Antifouling Strategies for Sensors Used in Water Monitoring: Review and Future Perspectives*. **Sensors, 21**(2), 389. [DOI: 10.3390/s21020389](https://doi.org/10.3390/s21020389). Revue des méthodes et compromis anti-encrassement, déjà résumée dans [REVUE_ANTIFOULING.md](REVUE_ANTIFOULING.md).
