/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** MonteCarlo
*/

#include "MonteCarlo.hpp"
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <limits>
#include <memory>
#include "MonteCarloDebug.hpp"
#include "MonteCarloFuturThreat.hpp"
#include "MonteCarloThreat.hpp"
#ifdef GOMOKU_DEBUG
    #include <iostream>
    #include <numeric>
    #include <ostream>
#endif
#include <random>
#include <thread>
#include <utility>
#include <vector>
#include "GameManager.hpp"
#include "Pos.hpp"

std::size_t go::MonteCarlo::getRandomEmptyCell(const go::BoardManager &board)
{
    static thread_local std::mt19937 gen(std::clock() + std::hash<std::thread::id>{}(std::this_thread::get_id()));

    std::uniform_int_distribution<std::size_t> dist(0, board.remainingPlayArea.size() - 1);

    return dist(gen);
}

double go::MonteCarlo::computeUCB1(const Node &child, double parentLogSimulation)
{
    const double exploitation = child.score / child.nbSimulation;
    const double exploration = std::sqrt(parentLogSimulation / child.nbSimulation);
    return exploitation + EXPLORATION_CONSTANT * exploration;
}

go::MonteCarlo::Node *go::MonteCarlo::selectUcb(Node *node)
{
    const double parentLogSimulation = std::log(node->nbSimulation + 1);
    std::size_t bestChild = std::numeric_limits<std::size_t>::max();
    double bestScore = std::numeric_limits<double>::lowest();
    double score = 0;

    for (std::size_t i = 0; i < node->child.size(); ++i) {
        score = computeUCB1(*node->child[i], parentLogSimulation);
        if (score > bestScore) {
            bestScore = score;
            bestChild = i;
        }
    }
    return node->child[bestChild].get();
}

go::MonteCarlo::Node *go::MonteCarlo::selectAndExpand(Node *node)
{
    Node *it = node;
    std::size_t nextMoveToExplore = 0;

    while (true) {
        if (it->board.isGameFinish()) {
            return it;
        }
        nextMoveToExplore = it->child.size();
        if (nextMoveToExplore < it->board.remainingPlayArea.size()) {
            it->child.push_back(
                std::make_unique<go::MonteCarlo::Node>(it->board, it, it->board.remainingPlayArea[nextMoveToExplore])
            );
            it->child.back()->depth = it->depth + 1;
            return it->child.back().get();
        }
        it = selectUcb(it);
    }
}

go::GameStatus go::MonteCarlo::simulateGame(Node *node)
{
    BoardManager newBoard = node->board;
    std::size_t cellIndex = 0;

    while (!newBoard.isGameFinish()) {
        cellIndex = getRandomEmptyCell(newBoard);
        newBoard.hellOptimizedFillCell(newBoard.remainingPlayArea[cellIndex], cellIndex);
    }
    return newBoard.status;
}

double go::MonteCarlo::computeScore(go::GameStatus status, double depth)
{
    if (status == go::GameStatus::SELF_WIN) {
        return (1.0 / depth);
    }
    if (status == go::GameStatus::ENEMY_WIN) {
        return -(1.0 / depth);
    }
    if (status == go::GameStatus::TIE) {
        return 0.001;
    }
    return 0.0;
}

void go::MonteCarlo::backPropagation(Node *node, GameStatus status)
{
    Node *it = node;

    while (it) {
        it->score += computeScore(status, it->depth);
        it->nbSimulation += 1;
        it = it->parent;
    }
}

go::MonteCarlo::Node *go::MonteCarlo::bestNode(Node *node)
{
    return std::max_element(
               node->child.begin(),
               node->child.end(),
               [](const std::unique_ptr<Node> &n1, const std::unique_ptr<Node> &n2) -> bool {
                   return n1->nbSimulation < n2->nbSimulation;
               }
    )->get();
}

std::size_t go::MonteCarlo::getBestPlayIndex(const std::vector<std::pair<Pos, std::size_t>> &play)
{
    return std::distance(
        play.begin(),
        std::max_element(
            play.begin(),
            play.end(),
            [](const std::pair<go::Pos, int> &it1, const std::pair<go::Pos, int> &it2) {
                return it1.second < it2.second;
            }
        )
    );
}

go::Pos go::MonteCarlo::nextBestPlay(const go::GameManager &game)
{
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    go::MonteCarloThreat threat(game.board);
    go::MonteCarloFuturThreat futurThreat(game.board);
    std::vector<std::pair<Pos, std::size_t>> rootOfAllTree;
    std::size_t bestMove = 0;
    Pos play = Pos::max();

    MonteCarloDebug::printThreatStat(threat, futurThreat);

    play = handleCriticalPlay(game.board);
    if (play != Pos::max()) {
        MonteCarloDebug::printBoard(game.board, play, threat);
        return play;
    }
    rootOfAllTree = getMonteCarloResult(game.board, startTime);
    bestMove = getBestPlayIndex(rootOfAllTree);

#ifdef GOMOKU_DEBUG
    std::cout << "DEBUG MonteCarlo have simulate: \e[92m" << std::accumulate(rootOfAllTree.begin(), rootOfAllTree.end(), 0, [](std::size_t res, const std::pair<Pos, std::size_t> &it) { return res + it.second; }) << "\e[0m game." << std::endl;
#endif

    play = threat.counter(rootOfAllTree, bestMove, futurThreat);
    if (play != Pos::max()) {
        MonteCarloDebug::printBoard(game.board, play, threat);
        return play;
    }
    if (!threat.threatDetected()) {
        play = futurThreat.counter(rootOfAllTree, bestMove);
        if (play != Pos::max()) {
            MonteCarloDebug::printBoard(game.board, play, threat);
            return play;
        }
    }
    MonteCarloDebug::printBoard(game.board, rootOfAllTree[bestMove].first, threat);
    return rootOfAllTree[bestMove].first;
}
