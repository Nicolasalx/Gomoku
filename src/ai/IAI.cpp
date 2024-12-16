/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** IAI
*/

#include "IAI.hpp"
#include "MonteCarlo.hpp"

go::Pos go::IAI::nextBestPlay(const GameManager &game)
{
    return go::MonteCarlo::nextBestPlay(game);
}
