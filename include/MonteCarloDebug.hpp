/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** MonteCarloLog
*/

#pragma once

#include "MonteCarloFuturThreat.hpp"
#include "MonteCarloThreat.hpp"
#include "Pos.hpp"

namespace go {

class MonteCarloDebug {
    static bool printBoardThreat(std::uint8_t x, std::uint8_t y, Pos pos, const go::MonteCarloThreat &threat);

    public:
    static void printBoard(const BoardManager &board, Pos pos, const MonteCarloThreat &threat);
    static void printThreatStat(const MonteCarloThreat &threat, const MonteCarloFuturThreat &futurThreat);
    static void printCellScore(std::vector<std::pair<Pos, std::size_t>> rootOfAllTree);
};

} // namespace go
