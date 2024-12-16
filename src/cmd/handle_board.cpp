/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** handle_board
*/

#include <exception>
#include <iostream>
#include <string>
#include "GameManager.hpp"
#include "Gomoku.hpp"
#include "IAI.hpp"
#include "SplitString.hpp"

void go::handleBoard(std::string &, GameManager &game)
{
    std::string line;
    std::vector<std::string> arg;
    CellState cellState = CellState::EMPTY;

    while (std::getline(std::cin, line)) {
        if (line.starts_with("DONE")) {
            break;
        }
        try {
            arg = utils::splitString(line, ", \r\n");
            switch (std::stoi(arg.at(2))) {
                case 1:
                    cellState = CellState::SELF;
                    break;
                case 2:
                    cellState = CellState::ENEMY;
                    break;
                case 3:
                    cellState = CellState::EMPTY;
                    break;
            }
            game.board.set(
                Pos{static_cast<std::uint8_t>(std::stoi(arg.at(0))), static_cast<std::uint8_t>(std::stoi(arg.at(1)))},
                cellState
            );
        } catch (const std::exception &) {
            std::cerr << "DEBUG \e[1;93minvalid BOARD arg:\e[0m \"" << line << "\"" << std::endl;
        }
    }
    game.board.status = GameStatus::SELF_PLAY;
    game.board.lastPlayerTurn = CellState::ENEMY;
    for (std::uint8_t y = 0; y < go::BoardManager::BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < go::BoardManager::BOARD_SIZE; ++x) {
            if (game.board.get(Pos{x, y}) == CellState::PLAY_AREA) {
                game.board.set(Pos{x, y}, CellState::EMPTY);
            }
        }
    }
    for (std::uint8_t y = 0; y < go::BoardManager::BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < go::BoardManager::BOARD_SIZE; ++x) {
            if (game.board.get(Pos{x, y}) != CellState::EMPTY && game.board.get(Pos{x, y}) != CellState::PLAY_AREA) {
                game.board.applyPlayArea(Pos{x, y}, go::BoardManager::PLAY_AREA_RADIUS);
            }
        }
    }

    Pos bestPlay = go::IAI::nextBestPlay(game);

#ifdef GOMOKU_DEBUG
    std::cout << "DEBUG \e[95mPLAYING: " << bestPlay << "\e[0m" << std::endl;
#endif
    std::cout << bestPlay << std::endl;

    game.board.fillCell(bestPlay);
}
