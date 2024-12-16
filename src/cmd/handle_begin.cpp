/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** handle_begin
*/

#include <iostream>
#include "GameManager.hpp"
#include "Gomoku.hpp"
#include "IAI.hpp"
#include "Pos.hpp"

void go::handleBegin(std::string &, GameManager &game)
{
    go::Pos bestPlay;

    game.board.setSelfBegin();

    bestPlay = go::IAI::nextBestPlay(game);
    game.board.resetContent();

#ifdef GOMOKU_DEBUG
    std::cout << "DEBUG \e[95mPLAYING: " << bestPlay << "\e[0m" << std::endl;
#endif
    std::cout << bestPlay << std::endl;

    game.board.fillCell(bestPlay);
}
