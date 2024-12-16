/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** MonteCarloThreat
*/

#include "MonteCarloThreat.hpp"
#include <cstddef>
#include <utility>
#include <vector>
#include "GameManager.hpp"
#include "MonteCarlo.hpp"
#include "MonteCarloFuturThreat.hpp"
#include "Pos.hpp"
#include <unordered_set>

std::unordered_map<std::string, std::vector<int>> go::MonteCarloThreat::threatPatern = {
    // 012345
    {"-E-EE-", {2}},    // fix: "-ESEE-"
    {"-EE-E-", {3}},    // fix: "-EESE-"
    {"-EEE--", {0, 4}}, // fix: "SEEES-"
    {"--EEE-", {1, 5}}, // fix: "-SEEES"
};

std::unordered_set<go::Pos> go::MonteCarloThreat::_counterThreat(
    const BoardManager &board,
    Pos pos,
    Direction direction,
    CellState player
)
{
    std::string threat;
    std::unordered_set<go::Pos> threatCounter;
    int destX = 0;
    int destY = 0;

    for (int offset = -(PATERN_SIZE - 1); offset <= (PATERN_SIZE - 1); ++offset) {
        for (int i = 0; i < PATERN_SIZE; ++i) {
            destX = pos.x + (offset + i) * direction.x;
            destY = pos.y + (offset + i) * direction.y;
            if (destX < 0 || destX >= go::BoardManager::BOARD_SIZE || destY < 0 ||
                destY >= go::BoardManager::BOARD_SIZE) {
                threat += '-';
            } else {
                if (board.get({destX, destY}) == player) {
                    threat += 'E';
                } else if ((player == CellState::ENEMY && board.get({destX, destY}) == go::CellState::SELF) ||
                           (player == CellState::SELF && board.get({destX, destY}) == go::CellState::ENEMY)) {
                    threat += 'S';
                } else {
                    threat += '-';
                }
            }
        }
        if (MonteCarloThreat::threatPatern.contains(threat)) {
            for (const auto &it : MonteCarloThreat::threatPatern.at(threat)) {
                threatCounter.insert({pos.x + (offset + it) * direction.x, pos.y + (offset + it) * direction.y});
            }
        }
        threat.clear();
    }
    return threatCounter;
}

std::unordered_set<go::Pos> go::MonteCarloThreat::_detectThreat(const BoardManager &board, Pos pos, CellState player)
{
    std::unordered_set<go::Pos> currentCounter;
    std::unordered_set<go::Pos> threatCounter;

    for (const auto &dir : THREAT_DIRECTION) {
        currentCounter = _counterThreat(board, pos, dir, player);
        threatCounter.insert(currentCounter.begin(), currentCounter.end());
    }
    return threatCounter;
}

std::unordered_set<go::Pos> go::MonteCarloThreat::_getThreat(const BoardManager &board, CellState player)
{
    std::unordered_set<go::Pos> threatCounter;

    for (std::uint8_t y = 0; y < BoardManager::BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < BoardManager::BOARD_SIZE; ++x) {
            if (board.get({x, y}) == CellState::EMPTY || board.get({x, y}) == CellState::PLAY_AREA) {
                continue;
            }
            auto detectedThreat = _detectThreat(board, {x, y}, player);
            threatCounter.insert(detectedThreat.begin(), detectedThreat.end());
        }
    }
    return threatCounter;
}

go::MonteCarloThreat::MonteCarloThreat(const BoardManager &board)
{
    _enemyThreat = _getThreat(board, CellState::ENEMY);
    _selfThreat = _getThreat(board, CellState::SELF);
}

go::Pos go::MonteCarloThreat::counter(
    const std::vector<std::pair<Pos, std::size_t>> &rootOfAllTree,
    std::size_t bestMove,
    const MonteCarloFuturThreat &futurThreat
)
{
    std::vector<std::pair<Pos, std::size_t>> bestEnemyCounter;

    if (!_enemyThreat.empty() && !_enemyThreat.contains(rootOfAllTree[bestMove].first) &&
        !_selfThreat.contains(rootOfAllTree[bestMove].first) &&
        !futurThreat.getFuturEnemyThreat().contains(rootOfAllTree[bestMove].first) &&
        !futurThreat.getFuturSelfThreat().contains(rootOfAllTree[bestMove].first)) {
        for (const auto &it : rootOfAllTree) {
            if (_enemyThreat.contains(it.first)) {
                bestEnemyCounter.emplace_back(
                    it.first, it.second * (futurThreat.getFuturEnemyThreat().contains(it.first) + 1)
                );
            }
        }
        return bestEnemyCounter[go::MonteCarlo::getBestPlayIndex(bestEnemyCounter)].first;
    }
    return Pos::max();
}

bool go::MonteCarloThreat::threatDetected() const
{
    return !_enemyThreat.empty() || !_selfThreat.empty();
}
