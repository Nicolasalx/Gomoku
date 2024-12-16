/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** MonteCarloThreat
*/

#pragma once

#include <string>
#include <utility>
#include "GameManager.hpp"
#include "Pos.hpp"
#include <unordered_map>
#include <unordered_set>

namespace go {

class MonteCarloFuturThreat {
    private:
    std::unordered_set<go::Pos> _enemyFuturThreat;
    std::unordered_set<go::Pos> _selfFuturThreat;

    static std::unordered_map<std::string, int> threatPatern;

    int _countFuturThreat(const BoardManager &board, Pos pos, Direction direction, CellState player);
    int _detectFuturThreat(const BoardManager &board, Pos pos, CellState player);

    std::unordered_set<go::Pos> _getFuturThreat(BoardManager board, CellState player, int minThreatLevel);

    public:
    MonteCarloFuturThreat(const BoardManager &board);
    Pos counter(const std::vector<std::pair<Pos, std::size_t>> &rootOfAllTree, std::size_t bestMove);

    const std::unordered_set<go::Pos> &getFuturEnemyThreat() const
    {
        return _enemyFuturThreat;
    }

    const std::unordered_set<go::Pos> &getFuturSelfThreat() const
    {
        return _selfFuturThreat;
    }
};

} // namespace go
