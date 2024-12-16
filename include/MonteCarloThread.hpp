/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** MonteCarloThread
*/

#pragma once

#include <atomic>
#include <functional>
#include <thread>

namespace go {

class MonteCarloThread {
    private:
    std::vector<std::thread> _thread;
    std::function<void()> _task;
    std::atomic<bool> _run{true};

    void _runTask();

    public:
    MonteCarloThread() = default;

    void registerTask(const std::function<void()> &task);
    void launchThread(std::size_t nbThread);
    void stopThread();
    void waitThread();
};

} // namespace go
