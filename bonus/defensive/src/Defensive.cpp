/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** Defensive
*/

#include "Defensive.hpp"
#include "GameManager.hpp"

go::Pos go::Defensive::nextBestPlay(const go::GameManager &game)
{
    game.board.printBasicContent();
    return game.board.getEmptyCell().back();
}
