/*
** EPITECH PROJECT, 2024
** my_cpplib
** File description:
** my_log
*/

#pragma once

#include <string>
#include <source_location>

namespace utils {

void logInfo(const std::string &msg, std::source_location info = std::source_location::current());
void logWarning(const std::string &msg, std::source_location info = std::source_location::current());
void logError(const std::string &msg, std::source_location info = std::source_location::current());

} // namespace utils
