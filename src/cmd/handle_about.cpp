/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** handle_about
*/

#include <iostream>
#include "Gomoku.hpp"

void go::handleAbout(std::string &, GameManager &)
{
    std::cout << R"(name="Gomoku", version="1.0", author="Nicolas & Thibaud", country="FR")" << std::endl;
}
