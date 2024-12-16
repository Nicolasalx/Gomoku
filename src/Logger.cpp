/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** log
*/

#include "Logger.hpp"
#include <format>
#include <iostream>
#include <source_location>

void utils::logInfo(const std::string &msg, std::source_location info)
{
    std::cerr << std::format(
        "\033[2m{}:\033[96m{}\033[0;2m: "
        "\033[96minfo: \033[0m{}\n",
        std::string(info.file_name()).substr(std::string(info.file_name()).find_last_of('/') + 1),
        info.line(),
        msg
    );
}

void utils::logWarning(const std::string &msg, std::source_location info)
{
    std::cerr << std::format(
        "\033[1m{}:\033[96m{}\033[0;1m: "
        "\033[95mwarning: \033[0m{}\n",
        info.file_name(),
        info.line(),
        msg
    );
}

void utils::logError(const std::string &msg, std::source_location info)
{
    std::cerr << std::format(
        "\033[1m{}:\033[96m{}\033[0;1m: "
        "\033[91merror: \033[0m{}\n",
        info.file_name(),
        info.line(),
        msg
    );
}
