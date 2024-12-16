/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** handle_end
*/

#include "Gomoku.hpp"

void go::handleEnd(std::string &, GameManager &game)
{
    game.stopGame = true;
}
