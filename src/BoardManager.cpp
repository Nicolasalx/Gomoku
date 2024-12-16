/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** GameManager
*/

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>
#include "GameManager.hpp"
#include "Pos.hpp"

std::ostream &go::operator<<(std::ostream &os, CellState state)
{
    switch (state) {
        case CellState::EMPTY:
            os << "EMPTY";
            break;
        case CellState::PLAY_AREA:
            os << "PLAY_AREA";
            break;
        case CellState::ENEMY:
            os << "ENEMY";
            break;
        case CellState::SELF:
            os << "SELF";
            break;
    }
    return os;
}

std::ostream &go::operator<<(std::ostream &os, GameStatus status)
{
    switch (status) {
        case GameStatus::SELF_PLAY:
            os << "SELF_PLAY";
            break;
        case GameStatus::ENEMY_PLAY:
            os << "ENEMY_PLAY";
            break;
        case GameStatus::SELF_WIN:
            os << "SELF_WIN";
            break;
        case GameStatus::ENEMY_WIN:
            os << "ENEMY_WIN";
            break;
        case GameStatus::TIE:
            os << "TIE";
            break;
    }
    return os;
}

void go::BoardManager::set(Pos pos, CellState state)
{
    std::uint16_t index = pos.y * BOARD_SIZE + pos.x;
    std::uint16_t byteIndex = index >> 2;
    std::uint8_t bitOffset = (index & 0b11) << 1;

    content[byteIndex] &= ~(0b11 << bitOffset);
    content[byteIndex] |= (static_cast<std::uint8_t>(state) << bitOffset);
}

go::CellState go::BoardManager::get(Pos pos) const
{
    std::uint16_t index = pos.y * BOARD_SIZE + pos.x;
    std::uint16_t byteIndex = index >> 2;
    std::uint8_t bitOffset = (index & 0b11) << 1;

    return static_cast<CellState>((content[byteIndex] >> bitOffset) & 0b11);
}

void go::BoardManager::printContent() const
{
    std::cout << "DEBUG NB REMAINING PLAY AREA: " << remainingPlayArea.size() << std::endl;
    std::cout << "DEBUG | # ";
    for (std::uint8_t i = 0; i < BOARD_SIZE; ++i) {
        std::cout << static_cast<int>(i) << " ";
    }
    std::cout << std::endl;
    for (std::uint8_t y = 0; y < BOARD_SIZE; ++y) {
        std::cout << "DEBUG |" << std::setw(2) << y << " ";
        for (std::uint8_t x = 0; x < BOARD_SIZE; ++x) {
            switch (get(Pos{x, y})) {
                case go::CellState::EMPTY:
                    std::cout << "@ ";
                    break;
                case go::CellState::PLAY_AREA:
                    std::cout << "\e[2m=\e[0m ";
                    break;
                case go::CellState::SELF:
                    std::cout << "\e[94mO\e[0m ";
                    break;
                case go::CellState::ENEMY:
                    std::cout << "\e[91mX\e[0m ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void go::BoardManager::hellOptimizedFillCell(go::Pos pos, std::size_t posIndex)
{
    CellState player = CellState::EMPTY;

    if (status == GameStatus::SELF_PLAY) {
        player = CellState::SELF;
        lastPlayerTurn = CellState::SELF;
    } else if (status == GameStatus::ENEMY_PLAY) {
        player = CellState::ENEMY;
        lastPlayerTurn = CellState::ENEMY;
    }
    set(pos, player);
    remainingPlayArea[posIndex] = remainingPlayArea.back();
    remainingPlayArea.pop_back();
    if (isPlayerWin(pos, player)) {
        if (status == GameStatus::SELF_PLAY) {
            status = GameStatus::SELF_WIN;
        } else if (status == GameStatus::ENEMY_PLAY) {
            status = GameStatus::ENEMY_WIN;
        }
    } else {
        if (status == GameStatus::SELF_PLAY) {
            status = GameStatus::ENEMY_PLAY;
        } else if (status == GameStatus::ENEMY_PLAY) {
            status = GameStatus::SELF_PLAY;
        }
    }
    if (remainingPlayArea.empty()) {
        status = GameStatus::TIE;
    }

}

void go::BoardManager::fillCell(go::Pos pos, bool playAreaExpension)
{
    CellState player = CellState::EMPTY;

    if (status == GameStatus::SELF_PLAY) {
        player = CellState::SELF;
        lastPlayerTurn = CellState::SELF;
    } else if (status == GameStatus::ENEMY_PLAY) {
        player = CellState::ENEMY;
        lastPlayerTurn = CellState::ENEMY;
    }
    set(pos, player);
    for (std::size_t i = 0; i < remainingPlayArea.size(); ++i) {
        if (pos.x == remainingPlayArea[i].x && pos.y == remainingPlayArea[i].y) {
            remainingPlayArea[i] = remainingPlayArea.back();
            remainingPlayArea.pop_back();
            break;
        }
    }
    if (playAreaExpension) {
        applyPlayArea(pos, PLAY_AREA_RADIUS);
    }
    if (isPlayerWin(pos, player)) {
        if (status == GameStatus::SELF_PLAY) {
            status = GameStatus::SELF_WIN;
        } else if (status == GameStatus::ENEMY_PLAY) {
            status = GameStatus::ENEMY_WIN;
        }
    } else {
        if (status == GameStatus::SELF_PLAY) {
            status = GameStatus::ENEMY_PLAY;
        } else if (status == GameStatus::ENEMY_PLAY) {
            status = GameStatus::SELF_PLAY;
        }
    }
    if (remainingPlayArea.empty()) {
        status = GameStatus::TIE;
    }
}

bool go::BoardManager::isGameFinish() const
{
    return status == GameStatus::SELF_WIN || status == GameStatus::ENEMY_WIN || status == GameStatus::TIE;
}

void go::BoardManager::setSelfBegin()
{
    status = GameStatus::SELF_PLAY;
    applyPlayArea(Pos(BOARD_SIZE / 2, BOARD_SIZE / 2), START_PLAY_AREA_RADIUS);
    applyPlayArea(Pos((BOARD_SIZE / 2) - 1, BOARD_SIZE / 2), START_PLAY_AREA_RADIUS);
    applyPlayArea(Pos(BOARD_SIZE / 2, (BOARD_SIZE / 2) - 1), START_PLAY_AREA_RADIUS);
    applyPlayArea(Pos((BOARD_SIZE / 2) - 1, (BOARD_SIZE / 2) - 1), START_PLAY_AREA_RADIUS);
}

void go::BoardManager::applyPlayArea(Pos pos, std::uint8_t radius)
{
    int destX = 0;
    int destY = 0;

    if (get(pos) == CellState::EMPTY) {
        set(pos, CellState::PLAY_AREA);
        remainingPlayArea.push_back(pos);
    }
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            destX = pos.x + x;
            destY = pos.y + y;
            if (destX >= 0 && destX < BOARD_SIZE && destY >= 0 && destY < BOARD_SIZE &&
                get(Pos{destX, destY}) == CellState::EMPTY) {
                set(Pos{destX, destY}, CellState::PLAY_AREA);
                remainingPlayArea.emplace_back(destX, destY);
            }
        }
    }
}

std::vector<go::Pos> go::BoardManager::getEmptyCell() const
{
    std::vector<go::Pos> emptyCell;

    for (std::uint8_t y = 0; y < BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < BOARD_SIZE; ++x) {
            if (get(Pos{x, y}) == CellState::EMPTY || get(Pos{x, y}) == CellState::PLAY_AREA) {
                emptyCell.emplace_back(x, y);
            }
        }
    }
    return emptyCell;
}

void go::BoardManager::resetContent()
{
    while (!remainingPlayArea.empty()) {
        remainingPlayArea.pop_back();
    }
    for (std::uint8_t y = 0; y < BOARD_SIZE; ++y) {
        for (std::uint8_t x = 0; x < BOARD_SIZE; ++x) {
            set(Pos{x, y}, CellState::EMPTY);
        }
    }
}

bool go::BoardManager::_isHorizontalWin(Pos pos, CellState player) const
{
    int nbAligned = 1;

    for (int i = 1; i < 5; ++i) {
        int newX = pos.x - i;
        if (newX < 0 || get(Pos{newX, pos.y}) != player) {
            break;
        }
        ++nbAligned;
    }

    for (int i = 1; i < 5; ++i) {
        int newX = pos.x + i;
        if (newX >= BOARD_SIZE || get(Pos{newX, pos.y}) != player) {
            break;
        }
        ++nbAligned;
    }

    return nbAligned >= 5;
}

bool go::BoardManager::_isVerticalWin(Pos pos, CellState player) const
{
    int nbAligned = 1;

    for (int i = 1; i < 5; ++i) {
        int newY = pos.y - i;
        if (newY < 0 || get(Pos{pos.x, newY}) != player) {
            break;
        }
        ++nbAligned;
    }

    for (int i = 1; i < 5; ++i) {
        int newY = pos.y + i;
        if (newY >= BOARD_SIZE || get(Pos{pos.x, newY}) != player) {
            break;
        }
        ++nbAligned;
    }

    return nbAligned >= 5;
}

bool go::BoardManager::_isLeftDiagonalWin(Pos pos, CellState player) const
{
    int nbAligned = 1;

    for (int i = 1; i < 5; ++i) {
        int newX = pos.x - i;
        int newY = pos.y - i;
        if (newX < 0 || newY < 0 || get(Pos{newX, newY}) != player) {
            break;
        }
        ++nbAligned;
    }

    for (int i = 1; i < 5; ++i) {
        int newX = pos.x + i;
        int newY = pos.y + i;
        if (newX >= BOARD_SIZE || newY >= BOARD_SIZE || get(Pos{newX, newY}) != player) {
            break;
        }
        ++nbAligned;
    }

    return nbAligned >= 5;
}

bool go::BoardManager::_isRightDiagonalWin(Pos pos, CellState player) const
{
    int nbAligned = 1;

    for (int i = 1; i < 5; ++i) {
        int newX = pos.x + i;
        int newY = pos.y - i;
        if (newX >= BOARD_SIZE || newY < 0 || get(Pos{newX, newY}) != player) {
            break;
        }
        ++nbAligned;
    }

    for (int i = 1; i < 5; ++i) {
        int newX = pos.x - i;
        int newY = pos.y + i;
        if (newX < 0 || newY >= BOARD_SIZE || get(Pos{newX, newY}) != player) {
            break;
        }
        ++nbAligned;
    }

    return nbAligned >= 5;
}

bool go::BoardManager::isPlayerWin(go::Pos pos, CellState player) const
{
    if (get(pos) != player) {
        return false;
    }
    return _isHorizontalWin(pos, player) || _isVerticalWin(pos, player) || _isLeftDiagonalWin(pos, player) ||
        _isRightDiagonalWin(pos, player);
}
