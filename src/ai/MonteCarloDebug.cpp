/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** MonteCarloDebug
*/

#include "MonteCarloDebug.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "GameManager.hpp"
#include "MonteCarloFuturThreat.hpp"
#include "MonteCarloThreat.hpp"
#include "Pos.hpp"

bool go::MonteCarloDebug::printBoardThreat(std::uint8_t x, std::uint8_t y, Pos pos, const go::MonteCarloThreat &threat)
{
    Pos currentPos = {x, y};

    if (threat.getEnemyThreat().contains(currentPos)) {
        if (currentPos == pos) {
            std::cout << "\e[96mO\e[0m ";
        } else {
            std::cout << "\e[93m!\e[0m ";
        }
        return true;
    }
    if (threat.getSelfThreat().contains(currentPos)) {
        if (currentPos == pos) {
            std::cout << "\e[1;95mO\e[0m ";
        } else {
            std::cout << "\e[1;95m+\e[0m ";
        }
        return true;
    }
    return false;
}

void go::MonteCarloDebug::printBoard(
    [[maybe_unused]] const BoardManager &board,
    [[maybe_unused]] go::Pos pos,
    [[maybe_unused]] const go::MonteCarloThreat &threat
)
{
#ifdef GOMOKU_DEBUG
    std::cout << "DEBUG NB REMAINING PLAY AREA: " << board.remainingPlayArea.size() << std::endl;
    std::cout << "DEBUG | # ";
    for (std::uint8_t i = 0; i < go::BoardManager::BOARD_SIZE; ++i) {
        std::cout << static_cast<int>(i) << " ";
    }
    std::cout << std::endl;

    for (std::uint8_t y = 0; y < go::BoardManager::BOARD_SIZE; ++y) {
        std::cout << "DEBUG |" << std::setw(2) << static_cast<int>(y) << " ";
        for (std::uint8_t x = 0; x < go::BoardManager::BOARD_SIZE; ++x) {
            if (printBoardThreat(x, y, pos, threat)) {
                continue;
            }
            if (Pos{x, y} == pos) {
                std::cout << "\e[92mO\e[0m ";
                continue;
            }
            switch (board.get(Pos{x, y})) {
                case go::CellState::EMPTY:
                    std::cout << "@ ";
                    break;
                case go::CellState::PLAY_AREA:
                    std::cout << "\e[2m=\e[0m ";
                    break;
                case go::CellState::SELF:
                    std::cout << "\e[94mO\e[0m ";
                    break;
                case go::CellState::ENEMY:
                    std::cout << "\e[91mX\e[0m ";
                    break;
            }
        }
        std::cout << std::endl;
    }
#endif
}

void go::MonteCarloDebug::printThreatStat(
    [[maybe_unused]] const MonteCarloThreat &threat,
    [[maybe_unused]] const MonteCarloFuturThreat &futurThreat
)
{
#ifdef GOMOKU_DEBUG
    std::cout << "DEBUG \e[4;96m" << threat.getSelfThreat().size() << " Self Threat detected.\e[0m" << std::endl;
    for (const auto &it : threat.getSelfThreat()) {
        std::cout << "DEBUG >> \e[4;96m" << it << "\e[0m" << std::endl;
    }
    std::cout << "DEBUG \e[4;93m" << threat.getEnemyThreat().size() << " Enemy Threat detected.\e[0m" << std::endl;
    for (const auto &it : threat.getEnemyThreat()) {
        std::cout << "DEBUG >> \e[4;93m" << it << "\e[0m" << std::endl;
    }

    std::cout << "DEBUG \e[96m" << futurThreat.getFuturSelfThreat().size() << " Futur Self Threat detected.\e[0m" << std::endl;
    for (const auto &it : futurThreat.getFuturSelfThreat()) {
        std::cout << "DEBUG >> \e[96m" << it << "\e[0m" << std::endl;
    }
    std::cout << "DEBUG \e[93m" << futurThreat.getFuturEnemyThreat().size() << " Futur Enemy Threat detected.\e[0m" << std::endl;
    for (const auto &it : futurThreat.getFuturEnemyThreat()) {
        std::cout << "DEBUG >> \e[93m" << it << "\e[0m" << std::endl;
    }
#endif
}

void go::MonteCarloDebug::printCellScore([[maybe_unused]] std::vector<std::pair<Pos, std::size_t>> rootOfAllTree)
{
#ifdef GOMOKU_DEBUG
    std::sort(
        rootOfAllTree.begin(),
        rootOfAllTree.end(),
        [](const std::pair<Pos, std::size_t> &it1, const std::pair<Pos, std::size_t> &it2) {
            return it1.second > it2.second;
        }
    );
    for (std::size_t i = 0; i < rootOfAllTree.size(); ++i) {
        std::cout << "DEBUG ";
        if (i == 0) {
            std::cout << "\e[91m";
        }
        std::cout << "Pos: {" << rootOfAllTree[i].first << "}, Nb simulation: " << rootOfAllTree[i].second;
        if (i == 0) {
            std::cout << "\e[0m";
        }
        std::cout << std::endl;
    }
#endif
}
