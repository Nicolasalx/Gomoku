/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** IAI
*/

#pragma once

#include "GameManager.hpp"
#include "Pos.hpp"

namespace go {

    class IAI {
        public:
        static go::Pos nextBestPlay(const GameManager &game);
    };

}
