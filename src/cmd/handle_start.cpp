/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** handle_start
*/

#include <exception>
#include <iostream>
#include <string>
#include "GameManager.hpp"
#include "Gomoku.hpp"
#include "SplitString.hpp"

void go::handleStart(std::string &cmd, GameManager &game)
{
    std::vector<std::string> arg = utils::splitString(cmd, " \r\n");
    int boardSize = 0;

    if (arg.size() != 2) {
        std::cout << "ERROR unsupported board size" << std::endl;
        return;
    }
    try {
        boardSize = std::stoi(arg.at(1));
        if (boardSize != go::BoardManager::BOARD_SIZE) {
            std::cout << "ERROR unsupported board size" << std::endl;
        } else {
            game.board.content.fill(0);
            std::cout << "OK" << std::endl;
        }
    } catch (const std::exception &) {
        std::cout << "ERROR unsupported board size" << std::endl;
    }
}
