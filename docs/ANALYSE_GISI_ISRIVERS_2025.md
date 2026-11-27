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


## Complément — panorama PatSnap et DOI 10.3390/s21020389

La page [PatSnap Eureka — Non-Toxic Biofouling Prevention for Marine Sensors](https://eureka.patsnap.com/resources/blog/rd-blog/biofouling-prevention-for-marine-sensors-patsnap-eureka/) reprend la revue de Delgado, Briciu-Burghina & Regan (2021), [*Antifouling Strategies for Sensors Used in Water Monitoring: Review and Future Perspectives*](https://doi.org/10.3390/s21020389). Elle organise les pistes en quatre familles : action mécanique/énergétique (essuie-glace, vibration/ultrasons, jets ou bulles), UV/photoniques, ingénierie de surface (revêtements transparents et films), et architecture (chambre protégée, volet ou surface déformable).

### Ce que la revue et les études primaires ajoutent

| Piste | Principe et niveau de preuve | Pertinence pour MwambaWiper |
|---|---|---|
| Essuie-glace / brosse | Méthode déjà intégrée aux sondes de terrain; la revue rappelle l’abrasion, le blocage par le macrofouling, l’usure, le besoin d’énergie et les traversées étanches/corrosion. Ridd & Larcombe (1994) apportent une démonstration directe sur un capteur optique de turbidité. | **Piste la plus directe** pour le prototype actuel. Choisir un matériau de contact doux, remplaçable et compatible avec la fenêtre; vérifier l’abrasion et l’entraînement de grains. |
| Ultrason / vibration | Salimi et al. (2023) testent des transducteurs haute puissance marinés pour détacher localement le biofouling d’une plaque d’accès d’éolienne. Leur montage, leurs fréquences et niveaux d’énergie concernent une grande structure, pas une petite fenêtre optique. | **Piste exploratoire, non recommandée comme remplacement immédiat** : transducteur, électronique de puissance, transmission mécanique jusqu’à la fenêtre, effets sur l’optique et compatibilité avec les capteurs doivent être étudiés séparément. Ne pas reprendre simplement « 27,5 kHz » comme fréquence de conception. |
| UV / photonic | Irradiation pour limiter/inactiver des organismes, parfois dans une chambre de mesure fermée. Un brevet décrit une chambre qui mesure un échantillon puis l’irradie avant le cycle suivant; un brevet décrit un concept, pas à lui seul une preuve d’efficacité sur le capteur Mwamba. | Peut être pertinent à une chambre de prélèvement ou de mesure fermée. Sur une tête ouverte, il faut vérifier la géométrie, la dose, l’énergie, le vieillissement des matériaux et l’exposition biologique; ce n’est pas un simple ajout au firmware. |
| Revêtement transparent | Wilson et al. (2019) testent des revêtements sol-gel ORMOSIL sur des panneaux de verre en baie de Galway (études de micro- et macrofouling jusqu’à 9 et 13 mois). Les résultats dépendent de la formulation et de la surface; les panneaux ne valident pas directement le traitement d’une fenêtre PMMA ou d’un diffuseur PTFE. | Une piste à évaluer sur éprouvettes optiques avant toute application à une fenêtre réelle : transmission spectrale, voile/diffusion, adhésion, abrasion et compatibilité avec PMMA, verre ou diffuseur. |
| Chambre / volet / barrière physique | Protéger la surface lorsque la mesure ne se fait pas, ou prélever dans une chambre contrôlée. Cela limite l’exposition mais modifie le chemin optique ou la représentativité de l’échantillon si la conception n’est pas adaptée. | Idée envisageable si MwambaSpecDT peut mesurer par séquences avec une fenêtre protégée entre les mesures. Pour une mesure PAR ambiante continue, un volet masquerait précisément le signal recherché. |

### Qualité et limites de la page PatSnap

PatSnap est utile ici comme **carte de veille** et taxonomie des familles de solutions, pas comme source primaire d’efficacité. Son article juxtapose brevets, publications, données de paysage et recommandations stratégiques; le corpus annoncé (50+ documents) et ses décomptes ne remplacent pas une revue systématique reproductible. Les brevets décrivent des revendications et réalisations potentielles : ils ne démontrent pas à eux seuls une performance en déploiement.

La page affiche deux dates de publication différentes (10 juillet 2025 dans les métadonnées et 6 mai 2026 dans le corps), alors qu’elle annonce aussi une couverture allant jusqu’en 2026. Il faut donc éviter d’en déduire une chronologie précise sans consulter les publications et les familles de brevets sous-jacentes.

### Sources primaires ajoutées

- Delgado, A., Briciu-Burghina, C. & Regan, F. (2021). *Sensors*, 21(2), 389. [DOI: 10.3390/s21020389](https://doi.org/10.3390/s21020389). Revue de référence : critères et compromis des méthodes mécaniques, UV, matériaux et protections architecturales.
- Salimi, M. et al. (2023). “Biofouling Removal Using a Novel Electronic System for Driving an Array of High Power Marinised Transducers”, *Applied Sciences*, 13(6), 3749. [DOI: 10.3390/app13063749](https://doi.org/10.3390/app13063749). Démonstrateur ultrasonore sur plaque/structure marine, pas sur capteur optique compact.
- Wilson, L. et al. (2019). “Assessment of Antifouling Potential of Novel Transparent Sol Gel Coatings for Application in the Marine Environment”, *Molecules*, 24(16), 2983. [DOI: 10.3390/molecules24162983](https://doi.org/10.3390/molecules24162983). Essais de panneaux de verre revêtus, pas validation sur fenêtre de capteur.
- De la revue vers une autre étude de terrain : Delauney et al. (2023), “Design and In Situ Validation of Low-Cost and Easy to Apply Anti-Biofouling Techniques for Oceanographic Continuous Monitoring with Optical Instruments”, *Sensors*, 23(2), 605. [DOI: 10.3390/s23020605](https://doi.org/10.3390/s23020605). Comparaison de six protections sur capteur optique de turbidité en mer; les auteurs insistent sur le fait que le nettoyage agressif peut modifier l’état de la zone sensible et compliquer la comparaison métrologique avant/après déploiement.

**Décision de conception provisoire :** garder le servo et la brosse comme solution de prototype, puisque c’est l’approche la plus directement testable avec l’architecture actuelle. Utiliser la revue pour bâtir la grille d’essai (abrasion, blocage, étanchéité, corrosion, énergie, stabilité optique), et traiter ultrason, UV, revêtements et volets comme des pistes distinctes, chacune avec ses propres essais de compatibilité.
