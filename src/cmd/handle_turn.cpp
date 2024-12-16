/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** handle_turn
*/

#include <exception>
#include <iostream>
#include <string>
#include "GameManager.hpp"
#include "Gomoku.hpp"
#include "IAI.hpp"
#include "Pos.hpp"
#include "SplitString.hpp"

void go::handleTurn(std::string &cmd, GameManager &game)
{
    std::vector<std::string> arg = utils::splitString(cmd, " ,\r\n");
    go::Pos bestPlay;

    try {
        game.board.fillCell(
            go::Pos({static_cast<std::uint8_t>(std::stoi(arg.at(1))), static_cast<std::uint8_t>(std::stoi(arg.at(2)))})
        );
    } catch (const std::exception &) {
        std::cerr << "DEBUG \e[1;93minvalid TURN arg: " << cmd << "\e[0m" << std::endl;
    }
    bestPlay = go::IAI::nextBestPlay(game);

#ifdef GOMOKU_DEBUG
    std::cout << "DEBUG \e[95mPLAYING: " << bestPlay << "\e[0m" << std::endl;
#endif
    std::cout << bestPlay << std::endl;

    game.board.fillCell(bestPlay);
}
