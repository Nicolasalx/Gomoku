# Gomoku AI Bot

## Introduction

Le **Gomoku** (aussi appelé Wuzi Qi, Slope, Darpion ou Five in a Row) est un jeu à deux joueurs joué sur un plateau de 20x20. Le but est d’aligner 5 pierres de manière consécutive, que ce soit horizontalement, verticalement ou en diagonale. Ce projet vise à développer un bot capable de jouer à ce jeu avec une intelligence artificielle performante.

![image](https://github.com/user-attachments/assets/94d72fc6-041c-4666-90a1-5eed1193bde4)

## Explication du projet

Le but de ce projet est de créer un bot pour le jeu Gomoku en utilisant un algorithme de votre choix pour l'intelligence artificielle, tout en respectant un protocole de communication spécifique (au moins la partie "commandes obligatoires"). L'accent est mis sur l’efficacité de l'IA, qui sera évaluée principalement sur sa performance en jeu.

L'algorithme peut être un **Min-Max**, **Monte Carlo**, **Machine Learning**, ou tout autre algorithme de votre choix. L’objectif principal est d’optimiser l’IA pour maximiser ses victoires contre d’autres bots.

## Règles du jeu

Gomoku est un jeu à deux joueurs joué sur un plateau de 20x20. Les règles sont simples :
- Les joueurs placent chacun à leur tour une pierre sur le plateau.
- Le premier joueur à aligner 5 pierres consécutives (horizontalement, verticalement ou en diagonale) gagne la partie.
- Le jeu se termine dès qu’un joueur remporte la partie.

## Monte-Carlo Tree Search (MCTS)

L'algorithme choisi pour ce projet est le **Monte-Carlo Tree Search (MCTS)**, qui est largement utilisé dans les jeux de stratégie pour prendre des décisions en temps réel. Cet algorithme se décompose en quatre phases principales :

1. **Sélection** : Le processus consiste à choisir les noeuds du jeu à explorer en fonction d'un critère d'optimisation.
2. **Expansion** : De nouveaux noeuds sont ajoutés à l'arbre de recherche.
3. **Simulation** : Une simulation est effectuée à partir du noeud nouvellement ajouté pour évaluer le résultat possible.
4. **Backpropagation** : Les résultats de la simulation sont remontés dans l’arbre pour ajuster les valeurs des noeuds parents.

![image](https://github.com/user-attachments/assets/4d54d307-dc56-4f24-81a4-c9c836a50681)

## Résultats

Après avoir joué plus d'une centaine de parties contre des humains, l'IA a remporté **100%** des matchs testés.

Voici une vidéo montrant un humain jouant contre l'IA :  

[Vidéo de l'IA en action](https://github.com/user-attachments/assets/0d619c9c-64dc-436e-ad36-f227ca487cd1)

## Contraintes techniques

- **Temps de jeu** : 5 secondes maximum par coup.
- **Mémoire** : 70 MB de mémoire par bot.
- **Mouvement interdit** : Un coup interdit entraîne une défaite immédiate.
- **Bibliothèques interdites** : L’utilisation de bibliothèques interdites (comme TensorFlow ou scikit-learn) entraîne l’élimination du projet.
- **Langage** : Le programme doit être compilé sous Linux avec un `Makefile` (si compilation nécessaire), en utilisant uniquement les bibliothèques standard.

## Structure du projet

Le projet est conçu pour être compilé et testé automatiquement contre d'autres programmes dans le cadre d'une évaluation de la performance de l'IA.

## Conclusion

Ce projet a permis de développer un bot de jeu Gomoku performant, en utilisant l'algorithme **Monte-Carlo Tree Search (MCTS)** pour prendre des décisions stratégiques en temps réel. L'IA a été optimisée pour jouer à un niveau compétitif, en évaluant les coups possibles et en sélectionnant les meilleurs à chaque tour. Après avoir été testée dans plus d'une centaine de parties contre des joueurs humains, l'IA a remporté **100%** des matchs, démontrant ainsi son efficacité et sa capacité à rivaliser contre des bots de niveaux faibles à moyens.
