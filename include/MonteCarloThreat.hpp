/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** MonteCarloThreat
*/

#pragma once

#include <utility>
#include <vector>
#include "GameManager.hpp"
#include "MonteCarloFuturThreat.hpp"
#include "Pos.hpp"
#include <unordered_set>

namespace go {

class MonteCarloThreat {
    private:
    std::unordered_set<go::Pos> _enemyThreat;
    std::unordered_set<go::Pos> _selfThreat;

    static std::unordered_map<std::string, std::vector<int>> threatPatern;
    static constexpr int PATERN_SIZE = 6;
    static constexpr std::array<Direction, 4> THREAT_DIRECTION = {{{0, 1}, {1, 0}, {1, 1}, {-1, 1}}};

    std::unordered_set<go::Pos> _counterThreat(
        const BoardManager &board,
        Pos pos,
        Direction direction,
        CellState player
    );
    std::unordered_set<go::Pos> _detectThreat(const BoardManager &board, Pos pos, CellState player);
    std::unordered_set<go::Pos> _getThreat(const BoardManager &board, CellState player);

    public:
    MonteCarloThreat(const BoardManager &board);
    Pos counter(
        const std::vector<std::pair<Pos, std::size_t>> &rootOfAllTree,
        std::size_t bestMove,
        const MonteCarloFuturThreat &futurThreat
    );
    bool threatDetected() const;

    const std::unordered_set<go::Pos> &getEnemyThreat() const
    {
        return _enemyThreat;
    }

    const std::unordered_set<go::Pos> &getSelfThreat() const
    {
        return _selfThreat;
    }
};

} // namespace go
