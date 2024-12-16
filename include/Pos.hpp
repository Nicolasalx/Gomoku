/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** Pos
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <ostream>

namespace go {

struct Pos {
    std::uint8_t x = 0;
    std::uint8_t y = 0;

    constexpr Pos() = default;
    constexpr Pos(std::uint8_t x, std::uint8_t y) : x(x), y(y) {}
    constexpr Pos(int x, std::uint8_t y) : x(x), y(y) {}
    constexpr Pos(std::uint8_t x, int y) : x(x), y(y) {}
    constexpr Pos(int x, int y) : x(x), y(y) {}

    static constexpr Pos max()
    {
        return {std::numeric_limits<std::uint8_t>::max(), std::numeric_limits<std::uint8_t>::max()};
    }

    bool operator==(const Pos &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Pos &other) const
    {
        return x != other.x || y != other.y;
    }
};

std::ostream &operator<<(std::ostream &os, Pos pos);

struct Direction {
    int x = 0;
    int y = 0;
};

} // namespace go

namespace std {

template <>
struct hash<go::Pos> {
    std::size_t operator()(const go::Pos &pos) const noexcept
    {
        return (static_cast<std::size_t>(pos.x) << 8) ^ static_cast<std::size_t>(pos.y);
    }
};
} // namespace std
