/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** GameManager
*/

#pragma once

#include <array>
#include <vector>
#include "Pos.hpp"

namespace go {

enum class CellState : std::uint8_t {
    EMPTY,
    PLAY_AREA,
    ENEMY,
    SELF
};

enum class GameStatus : std::uint8_t {
    SELF_PLAY,
    ENEMY_PLAY,
    SELF_WIN,
    ENEMY_WIN,
    TIE
};

std::ostream &operator<<(std::ostream &os, CellState state);
std::ostream &operator<<(std::ostream &os, GameStatus status);

class BoardManager {
    public:
    static constexpr std::uint8_t START_PLAY_AREA_RADIUS = 4;
    static constexpr std::uint8_t PLAY_AREA_RADIUS = 3;
    static constexpr int BOARD_SIZE = 20;

    std::array<std::uint8_t, (BOARD_SIZE * BOARD_SIZE) / 4> content;
    GameStatus status = GameStatus::ENEMY_PLAY;
    CellState lastPlayerTurn = CellState::SELF;
    std::vector<Pos> remainingPlayArea;

    void set(Pos pos, CellState state);
    CellState get(Pos pos) const;

    void printContent() const;
    void setSelfBegin();
    void hellOptimizedFillCell(go::Pos pos, std::size_t posIndex);
    void fillCell(go::Pos pos, bool playAreaExpension = true);
    std::vector<Pos> getEmptyCell() const;
    bool isPlayerWin(Pos pos, CellState player) const;
    bool isGameFinish() const;
    void applyPlayArea(Pos pos, std::uint8_t radius);
    void resetContent();

    private:
    bool _isHorizontalWin(Pos pos, CellState player) const;
    bool _isVerticalWin(Pos pos, CellState player) const;
    bool _isLeftDiagonalWin(Pos pos, CellState player) const;
    bool _isRightDiagonalWin(Pos pos, CellState player) const;
};

struct GameManager {
    bool stopGame = false;
    BoardManager board;
};

} // namespace go
