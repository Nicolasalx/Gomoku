/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** Gomoku
*/

#pragma once

#include <array>
#include <string>
#include "GameManager.hpp"

namespace go {

void handleStart(std::string &cmd, GameManager &game);
void handleTurn(std::string &cmd, GameManager &game);
void handleBegin(std::string &cmd, GameManager &game);
void handleBoard(std::string &cmd, GameManager &game);
void handleInfo(std::string &cmd, GameManager &game);
void handleEnd(std::string &cmd, GameManager &game);
void handleAbout(std::string &cmd, GameManager &game);

constexpr std::array<std::pair<std::string_view, void (*)(std::string &, GameManager &game)>, 7> CMD_FUNC = {
    {{"START", handleStart},
     {"TURN", handleTurn},
     {"BEGIN", handleBegin},
     {"BOARD", handleBoard},
     {"INFO", handleInfo},
     {"END", handleEnd},
     {"ABOUT", handleAbout}}
};

void executeCmd(std::string &line, go::GameManager &game);

} // namespace go
