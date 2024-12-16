/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** MonteCarlo
*/

#pragma once

#include <chrono>
#include <cmath>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>
#include "GameManager.hpp"
#include "Pos.hpp"

namespace go {

class MonteCarlo {
    private:
    struct Node {
        BoardManager board;
        int nbSimulation = 0;
        int depth = 0;
        double score = 0;
        go::Pos play;

        Node *parent;
        std::vector<std::unique_ptr<Node>> child;

        // ! only used for the root
        Node(BoardManager gameBoard, Node *parent) : board(std::move(gameBoard)), parent(parent)
        {
            child.reserve(board.remainingPlayArea.size());
        }

        Node(BoardManager gameBoard, Node *parent, go::Pos play)
            : board(std::move(gameBoard)), play(play), parent(parent)
        {
            board.fillCell(play, false);
            child.reserve(board.remainingPlayArea.size());
        }
    };

    static constexpr double EXPLORATION_CONSTANT = 10;
    static constexpr std::size_t DEFAULT_NB_THREAD_USED = 8; // not currently used
    static constexpr std::size_t NB_PARALLEL_SIMULATION = 11000;
    static constexpr std::size_t TARGET_EXECUTION_TIME = 4.5 * 1000; // ms

    static std::size_t getRandomEmptyCell(const go::BoardManager &board);

    static double computeUCB1(const Node &child, double parentLogSimulation);
    static Node *selectUcb(Node *node);

    static double computeScore(go::GameStatus status, double depth);

    static Node *selectAndExpand(Node *node);
    static GameStatus simulateGame(Node *node);
    static void backPropagation(Node *node, GameStatus status);
    static Node *bestNode(Node *node);

    static go::Pos checkCriticalLose(go::BoardManager board);
    static go::Pos checkInstantWin(go::BoardManager board);
    static go::Pos handleCriticalPlay(const go::BoardManager &board);

    static std::unique_ptr<Node> createMonteCarloTree(const BoardManager &board, std::size_t nbIteration);
    static std::vector<std::pair<Pos, std::size_t>> getMonteCarloResult(
        const BoardManager &board,
        const std::chrono::high_resolution_clock::time_point &startTime
    );

    public:
    static std::size_t getBestPlayIndex(const std::vector<std::pair<Pos, std::size_t>> &play);
    static go::Pos nextBestPlay(const GameManager &game);
};

} // namespace go
