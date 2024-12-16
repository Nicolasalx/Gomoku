/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** GetMonteCarloResult
*/

#include <chrono>
#include <memory>
#ifdef GOMOKU_DEBUG
    #include <iostream>
#endif
#include <mutex>
#include <thread>
#include "MonteCarlo.hpp"
#include "MonteCarloThread.hpp"

std::unique_ptr<go::MonteCarlo::Node> go::MonteCarlo::createMonteCarloTree(
    const BoardManager &board,
    std::size_t nbIteration
)
{
    std::unique_ptr<Node> root = std::make_unique<Node>(board, nullptr);

    for (std::size_t i = 0; i < nbIteration; ++i) {
        Node *current = selectAndExpand(root.get());
        GameStatus status = simulateGame(current);

        backPropagation(current, status);
    }
    return root;
}

std::vector<std::pair<go::Pos, std::size_t>> go::MonteCarlo::getMonteCarloResult(
    const BoardManager &board,
    const std::chrono::high_resolution_clock::time_point &startTime
)
{
    std::vector<std::pair<Pos, std::size_t>> rootOfAllTree(board.remainingPlayArea.size(), {{0, 0}, 0});
    std::size_t nbIterationPerTree = 0;
    MonteCarloThread mtThread;
    std::mutex mutex;
    std::size_t nbUsedThread = std::thread::hardware_concurrency();

    for (std::size_t i = 0; i < rootOfAllTree.size(); ++i) {
        rootOfAllTree[i].first = board.remainingPlayArea[i];
    }
    nbIterationPerTree = static_cast<std::size_t>(
        ((go::MonteCarlo::NB_PARALLEL_SIMULATION / static_cast<double>(nbUsedThread)) /
         static_cast<double>(board.remainingPlayArea.size())) *
        400.0
    );

#ifdef GOMOKU_DEBUG
    std::cout << "DEBUG Max Parallel Simulation: \e[94m" << nbIterationPerTree * nbUsedThread << "\e[0m on \e[94m"
              << nbUsedThread << "\e[0m thread." << std::endl;
#endif

    mtThread.registerTask([&board, &nbIterationPerTree, &rootOfAllTree, &mutex]() {
        std::unique_ptr<go::MonteCarlo::Node> root = createMonteCarloTree(board, nbIterationPerTree);
        {
            std::scoped_lock<std::mutex> lock(mutex);

            for (std::size_t i = 0; i < root->child.size(); ++i) {
                rootOfAllTree[i].second += root->child[i]->nbSimulation;
            }
        }
    });

    mtThread.launchThread(nbUsedThread);
    std::this_thread::sleep_for(
        std::chrono::milliseconds(go::MonteCarlo::TARGET_EXECUTION_TIME) -
        (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime))
    );
    mtThread.stopThread();
    mtThread.waitThread();
    return rootOfAllTree;
}
