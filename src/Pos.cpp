/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** Pos
*/

#include "Pos.hpp"

std::ostream &go::operator << (std::ostream &os, go::Pos pos)
{
    os << static_cast<int>(pos.x) << ',' << static_cast<int>(pos.y);
    return os;
}
