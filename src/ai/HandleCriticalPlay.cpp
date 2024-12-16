/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** HandleCriticalPlay
*/

#include "MonteCarlo.hpp"

go::Pos go::MonteCarlo::checkCriticalLose(go::BoardManager board)
{
    CellState prevState = CellState::EMPTY;

    for (const auto &it : board.remainingPlayArea) {
        prevState = board.get(it);
        board.set(it, CellState::ENEMY);
        if (board.isPlayerWin(Pos{it.x, it.y}, CellState::ENEMY)) {
            return Pos{it.x, it.y};
        }
        board.set(it, prevState);
    }
    return Pos::max();
}

go::Pos go::MonteCarlo::checkInstantWin(go::BoardManager board)
{
    CellState prevState = CellState::EMPTY;

    for (const auto &it : board.remainingPlayArea) {
        prevState = board.get(it);
        board.set(it, CellState::SELF);
        if (board.isPlayerWin(Pos{it.x, it.y}, CellState::SELF)) {
            return Pos{it.x, it.y};
        }
        board.set(it, prevState);
    }
    return Pos::max();
}

go::Pos go::MonteCarlo::handleCriticalPlay(const go::BoardManager &board)
{
    Pos pos;

    pos = checkInstantWin(board);
    if (pos != Pos::max()) {
        return pos;
    }
    pos = checkCriticalLose(board);
    if (pos != Pos::max()) {
        return pos;
    }
    return Pos::max();
}
