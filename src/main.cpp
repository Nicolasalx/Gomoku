/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-thibaud.cathala
** File description:
** main
*/

#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include "Gomoku.hpp"

void go::executeCmd(std::string &line, go::GameManager &game)
{
    for (const auto &it : go::CMD_FUNC) {
        if (line.starts_with(it.first)) {
            it.second(line, game);
            return;
        }
    }
    std::cout << "UNKNOWN" << std::endl;
}

int main()
{
    std::string line;
    go::GameManager game;

    while (!game.stopGame && std::getline(std::cin, line)) {
        go::executeCmd(line, game);
    }
    return 0;
}
