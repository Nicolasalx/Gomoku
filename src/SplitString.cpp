/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** SplitString
*/

#include "SplitString.hpp"

std::vector<std::string> utils::splitString(const std::string &str, const std::string &delimiter)
{
    std::size_t start = 0;
    std::vector<std::string> dest;

    for (std::size_t i = 0; i <= str.size(); ++i) {
        if (i == str.size() || delimiter.find(str[i]) != std::string::npos) {
            if (i > start) {
                dest.push_back(str.substr(start, i - start));
            }
            start = i + 1;
        }
    }
    return dest;
}
