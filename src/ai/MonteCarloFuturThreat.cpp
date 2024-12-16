/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** MonteCarloThreat
*/

#include "MonteCarloFuturThreat.hpp"
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include "GameManager.hpp"
#include "MonteCarlo.hpp"
#include "Pos.hpp"

std::unordered_map<std::string, int> go::MonteCarloFuturThreat::threatPatern = {
    {"EEE--", 1},
    {"-EEE-", 1},
    {"--EEE", 1},
    {"EEEE-", 1},
    {"-EEEE", 1},
};

int go::MonteCarloFuturThreat::_countFuturThreat(
    const BoardManager &board,
    Pos pos,
    Direction direction,
    CellState player
)
{
    std::string threat;
    int nbThreat = 0;
    int destX = 0;
    int destY = 0;

    for (int offset = -4; offset <= 4; ++offset) {
        for (int i = 0; i < 5; ++i) {
            destX = pos.y + (offset + i) * direction.y;
            destY = pos.x + (offset + i) * direction.x;
            if (destX < 0 || destX >= go::BoardManager::BOARD_SIZE || destY < 0 ||
                destY >= go::BoardManager::BOARD_SIZE) {
                threat += '-';
            } else {
                if (board.get({destY, destX}) == player) {
                    threat += 'E';
                } else if ((player == CellState::ENEMY && board.get({destY, destX}) == go::CellState::SELF) ||
                           (player == CellState::SELF && board.get({destY, destX}) == go::CellState::ENEMY)) {
                    threat += 'S';
                } else {
                    threat += '-';
                }
            }
        }
        if (MonteCarloFuturThreat::threatPatern.contains(threat)) {
            nbThreat += MonteCarloFuturThreat::threatPatern.at(threat);
        }
        threat.clear();
    }
    return nbThreat;
}

int go::MonteCarloFuturThreat::_detectFuturThreat(const BoardManager &board, Pos pos, CellState player)
{
    return _countFuturThreat(board, pos, {0, 1}, player) + _countFuturThreat(board, pos, {1, 0}, player) +
        _countFuturThreat(board, pos, {1, 1}, player) + _countFuturThreat(board, pos, {-1, 1}, player);
}

std::unordered_set<go::Pos> go::MonteCarloFuturThreat::_getFuturThreat(
    go::BoardManager board,
    go::CellState player,
    int minThreatLevel
)
{
    std::unordered_set<go::Pos> futurThreat;

    for (std::uint8_t y = 0; y < BoardManager::BOARD_SIZE; ++y) {
        // std::cout << "DEBUG |" << std::setw(2) << static_cast<int>(y) << " ";
        for (std::uint8_t x = 0; x < BoardManager::BOARD_SIZE; ++x) {
            if (board.get({x, y}) != CellState::PLAY_AREA) {
                // std::cout << "_ ";
                continue;
            }
            board.set({x, y}, player);
            int detectedThreat = _detectFuturThreat(board, {x, y}, player);
            // std::cout << detectedThreat << " ";
            if (detectedThreat >= minThreatLevel) {
                futurThreat.insert({x, y});
            }
            board.set({x, y}, CellState::PLAY_AREA);
        }
        // std::cout << std::endl;
    }
    return futurThreat;
}

go::MonteCarloFuturThreat::MonteCarloFuturThreat(const BoardManager &board)
{
    _enemyFuturThreat = _getFuturThreat(board, CellState::ENEMY, 5);
    _selfFuturThreat = _getFuturThreat(board, CellState::SELF, 5);
}

go::Pos go::MonteCarloFuturThreat::counter(
    const std::vector<std::pair<Pos, std::size_t>> &rootOfAllTree,
    std::size_t bestMove
)
{
    std::vector<std::pair<Pos, std::size_t>> bestEnemyCounter;

    if (!_enemyFuturThreat.empty() && !_enemyFuturThreat.contains(rootOfAllTree[bestMove].first) &&
        !_selfFuturThreat.contains(rootOfAllTree[bestMove].first)) {
        for (const auto &it : rootOfAllTree) {
            if (_enemyFuturThreat.contains(it.first)) {
                bestEnemyCounter.push_back(it);
            }
        }
        return bestEnemyCounter[go::MonteCarlo::getBestPlayIndex(bestEnemyCounter)].first;
    }
    return Pos::max();
}
