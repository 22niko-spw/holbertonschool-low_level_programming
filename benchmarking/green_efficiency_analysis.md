Measurement Methodology

Pour garantir l'intégrité de cette analyse de performance, les expériences ont été menées à l'aide d'un script de benchmarking contrôlé. La principale métrique collectée est le temps d'exécution (temps réel écoulé) mesuré en secondes. La méthodologie a consisté à exécuter deux versions distinctes de la même logique : une implémentation dite "Naive" (naïve) et une implémentation optimisée "Single-pass" (en une seule passe).
Chaque algorithme a été exécuté trois fois consécutives afin de prendre en compte les interférences potentielles des processus système en arrière-plan et d'assurer une cohérence statistique. Le test a traité une charge de travail de 100 000 000 d'itérations. La moyenne de ces trois passages a ensuite été calculée pour établir la base de référence de notre comparaison d'efficacité. Tous les tests ont été effectués sur le même environnement matériel pour garantir que les variables telles que la fréquence du processeur et la latence de la mémoire restent constantes.

Observed Performance Differences

Les données empiriques recueillies révèlent une différence d'efficacité stupéfiante entre les deux approches. L'algorithme Naïf a nécessité plus de 1,5 seconde pour accomplir la tâche, tandis que l'algorithme Single-pass l'a terminée en une fraction de milliseconde.
Les résultats mesurés montrent que l'algorithme Naïf est environ 27 673 fois plus lent que la version Single-pass. Alors que la version Naïve présente de légères fluctuations (probablement dues à des échecs de cache ou à l'ordonnancement de l'OS), la version Single-pass reste remarquablement stable en raison de son empreinte computationnelle minimale.

Relation Between Runtime and Energy Consumption
En informatique, il existe une corrélation directe entre le nombre d'instructions exécutées et l'énergie électrique consommée. En utilisant la relation physique fondamentale : 

						E = P x t 

où E représente l'énergie, P la puissance moyenne consommée par le processeur et $t$ le temps d'exécution, nous pouvons analyser l'impact environnemental.L'algorithme Naïf maintient le processeur dans un état de haute puissance pendant 1,577 seconde. En revanche, l'algorithme Single-pass atteint le même objectif en 0,000057 seconde. Comme la consommation d'énergie reste relativement similaire pendant l'exécution active, la version Single-pass consomme 99,99 % d'énergie en moins que la version Naïve. Cela illustre que le "Green IT" ne concerne pas seulement le matériel, mais surtout le choix d'algorithmes qui minimisent le cycle d'utilisation du processeur.

Limitations of the Experiment
Malgré la clarté des résultats, certaines limites s'appliquent à cette expérience :Résolution de la mesure : À 0,000057 seconde, nous approchons des limites de précision de l'horloge système standard. Des tests futurs pourraient nécessiter des outils de profilage à plus haute résolution.
Surcharge vs Charge utile : Pour des ensembles de données très petits, la surcharge liée au démarrage du programme pourrait l'emporter sur le temps d'exécution, faussant potentiellement le ratio.
Abstraction matérielle : Le calcul de l'énergie est une estimation basée sur le temps. Il ne tient pas compte de l'énergie consommée par la RAM ou le contrôleur de stockage, qui ne s'adaptent pas forcément de la même manière que la puissance des cœurs CPU.

Practical Engineering Takeaway
La principale conclusion de ce benchmark est l'impact dramatique de la complexité algorithmique sur la performance et la durabilité. Une différence de 27 673x n'est pas une simple optimisation ; c'est un changement fondamental dans l'utilisation des ressources.Pour un développeur, cela prouve que l'écriture d'un code "écologique" ne nécessite pas toujours des changements matériels complexes, mais plutôt une priorité accordée à la réduction : réduction des itérations, réduction des accès mémoire et réduction du temps d'exécution. L'extension de l'algorithme Naïf à une échelle mondiale (millions d'utilisateurs) entraînerait un gaspillage d'énergie massif, tandis que l'approche Single-pass conserve une empreinte carbone négligeable, même à grande échelle.