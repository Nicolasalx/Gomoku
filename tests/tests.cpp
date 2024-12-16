/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-thibaud.cathala
** File description:
** tests
*/

#include <criterion/criterion.h>
#include "GameManager.hpp"
#include "Pos.hpp"

Test(Test_BoardManager, EmptyBoard)
{
    go::BoardManager board;
    // board.resize(7);

    //   0 1 2 3 4 5 6
    // 0 @ @ @ @ @ @ @
    // 1 @ @ @ @ @ @ @
    // 2 @ @ @ @ @ @ @
    // 3 @ @ @ @ @ @ @
    // 4 @ @ @ @ @ @ @
    // 5 @ @ @ @ @ @ @
    // 6 @ @ @ @ @ @ @

    cr_assert(board.isGameFinish() == false);
}

Test(Test_BoardManager2, EdgeWin)
{
    go::BoardManager board;
    // board.resize(7);

    //   0 1 2 3 4 5 6
    // 0 @ @ @ @ @ @ @
    // 1 @ @ @ @ @ X @
    // 2 @ @ @ @ @ @ @
    // 3 @ @ @ X @ @ @
    // 4 @ @ ^ @ @ @ @
    // 5 @ X @ @ @ @ @
    // 6 @ @ @ @ @ @ @

    board.set(go::Pos{5, 1}, go::CellState::SELF);
    board.set(go::Pos{3, 3}, go::CellState::SELF);
    board.set(go::Pos{1, 5}, go::CellState::SELF);
    for (std::uint8_t y = 0; y < go::BoardManager::BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < go::BoardManager::BOARD_SIZE; ++x) {
            cr_expect(board.isPlayerWin(go::Pos{x, y}, go::CellState::SELF) == false);
        }
    }

    board.set(go::Pos{2, 4}, go::CellState::SELF);
    for (std::uint8_t y = 0; y < go::BoardManager::BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < go::BoardManager::BOARD_SIZE; ++x) {
            cr_expect(board.isPlayerWin(go::Pos{x, y}, go::CellState::SELF) == false);
        }
    }

    board.set(go::Pos{4, 2}, go::CellState::SELF);
    for (std::uint8_t y = 0; y < go::BoardManager::BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < go::BoardManager::BOARD_SIZE; ++x) {
            if ((y == 1 && x == 5) || (y == 3 && x == 3) || (y == 5 && x == 1) || (y == 4 && x == 2) ||
                (y == 2 && x == 4)) {
                cr_expect(board.isPlayerWin(go::Pos{x, y}, go::CellState::SELF) == true);
            } else {
                cr_expect(board.isPlayerWin(go::Pos{x, y}, go::CellState::SELF) == false);
            }
        }
    }
}

Test(Test_BoardManager3, EdgeEnemyWin)
{
    go::BoardManager board;
    // board.resize(7);

    //   0 1 2 3 4 5 6
    // 0 @ @ @ @ @ @ @
    // 1 @ @ @ @ @ X @
    // 2 @ @ @ @ @ @ ^
    // 3 @ @ @ X @ @ O
    // 4 @ @ @ @ @ @ O
    // 5 @ X @ @ @ @ O
    // 6 @ @ @ @ @ @ O

    board.set(go::Pos{5, 1}, go::CellState::SELF);
    board.set(go::Pos{3, 3}, go::CellState::SELF);
    board.set(go::Pos{1, 5}, go::CellState::SELF);

    board.set(go::Pos{6, 6}, go::CellState::ENEMY);
    board.set(go::Pos{6, 5}, go::CellState::ENEMY);
    board.set(go::Pos{6, 4}, go::CellState::ENEMY);
    board.set(go::Pos{6, 3}, go::CellState::ENEMY);
    for (std::uint8_t y = 0; y < go::BoardManager::BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < go::BoardManager::BOARD_SIZE; ++x) {
            cr_expect(board.isPlayerWin(go::Pos{x, y}, go::CellState::SELF) == false);
            cr_expect(board.isPlayerWin(go::Pos{x, y}, go::CellState::ENEMY) == false);
        }
    }

    board.set(go::Pos{6, 2}, go::CellState::ENEMY);
    for (std::uint8_t y = 0; y < go::BoardManager::BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < go::BoardManager::BOARD_SIZE; ++x) {
            cr_expect(board.isPlayerWin(go::Pos{x, y}, go::CellState::SELF) == false);
        }
    }
    for (std::uint8_t y = 0; y < go::BoardManager::BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < go::BoardManager::BOARD_SIZE; ++x) {
            if ((y == 6 && x == 6) || (y == 5 && x == 6) || (y == 4 && x == 6) || (y == 3 && x == 6) ||
                (y == 2 && x == 6)) {
                cr_expect(board.isPlayerWin(go::Pos{x, y}, go::CellState::ENEMY) == true);
            } else {
                cr_expect(board.isPlayerWin(go::Pos{x, y}, go::CellState::ENEMY) == false);
            }
        }
    }
}

Test(Test_BoardManager4, GameStatus)
{
    go::BoardManager board;
    // board.resize(7);

    board.setSelfBegin();

    // cr_expect(board.isPlayerWin(go::Pos{x, y}, go::CellState::ENEMY) == true);
}
