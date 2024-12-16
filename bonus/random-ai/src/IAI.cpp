/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** IAI
*/

#include "IAI.hpp"
#include <random>

go::Pos go::IAI::nextBestPlay(const go::GameManager &game)
{
    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<std::size_t> distr(0, game.board.getEmptyCell().size() - 1);

    return game.board.getEmptyCell().at(distr(mt));
}
