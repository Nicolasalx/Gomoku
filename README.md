# Gomoku AI Bot

## Introduction

**Gomoku** (also known as Wuzi Qi, Slope, Darpion, or Five in a Row) is a two-player game played on a 20x20 board. The objective is to align 5 consecutive stones, either horizontally, vertically, or diagonally. This project aims to develop a bot capable of playing this game with an advanced artificial intelligence.

![image](https://github.com/user-attachments/assets/94d72fc6-041c-4666-90a1-5eed1193bde4)

## Project Overview

The goal of this project is to create a bot for the game Gomoku using an artificial intelligence algorithm of your choice, while adhering to a specific communication protocol (at least the "mandatory commands" section). The focus is on the efficiency of the AI, which will be evaluated mainly on its performance in gameplay.

The algorithm can be a **Min-Max**, **Monte Carlo**, **Machine Learning**, or any other algorithm of your choice. The primary objective is to optimize the AI to maximize its victories against other bots.

## Game Rules

Gomoku is a two-player game played on a 20x20 board. The rules are simple:
- Players take turns placing a stone on the board.
- The first player to align 5 consecutive stones (horizontally, vertically, or diagonally) wins the game.
- The game ends as soon as a player wins.

## Monte-Carlo Tree Search (MCTS)

The algorithm chosen for this project is **Monte-Carlo Tree Search (MCTS)**, which is widely used in strategy games for making decisions in real time. The algorithm is broken down into four main phases:

1. **Selection**: The process of selecting game nodes to explore based on an optimization criterion.
2. **Expansion**: New nodes are added to the search tree.
3. **Simulation**: A simulation is run from the newly added node to evaluate the possible outcome.
4. **Backpropagation**: The results of the simulation are propagated up the tree to adjust the values of parent nodes.

![image](https://github.com/user-attachments/assets/4d54d307-dc56-4f24-81a4-c9c836a50681)

## Results

After playing over a hundred games against humans, the AI won **100%** of the tested matches.

Here is a video showing a human playing against the AI:  

[Video of AI in Action](https://github.com/user-attachments/assets/0d619c9c-64dc-436e-ad36-f227ca487cd1)

## Technical Constraints

- **Move Time**: 5 seconds maximum per move.
- **Memory**: 70 MB of memory per bot.
- **Forbidden Move**: A forbidden move results in an immediate defeat.
- **Forbidden Libraries**: The use of forbidden libraries (such as TensorFlow or scikit-learn) results in disqualification.
- **Language**: The program must be compiled on Linux using a `Makefile` (if compilation is necessary), and it should only use standard libraries.

## Project Structure

The project is designed to be compiled and automatically tested against other programs as part of an AI performance evaluation.

## Conclusion

This project successfully developed a performant Gomoku bot, using the **Monte-Carlo Tree Search (MCTS)** algorithm to make strategic decisions in real-time. The AI was optimized to play at a competitive level by evaluating possible moves and selecting the best ones at each turn. After being tested in over a hundred games against human players, the AI won **100%** of the matches, demonstrating its efficiency and ability to compete against low-to-medium level bots.
