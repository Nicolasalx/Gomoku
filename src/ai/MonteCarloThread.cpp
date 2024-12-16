/*
** EPITECH PROJECT, 2024
** B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
** File description:
** MonteCarloThread
*/

#include "MonteCarloThread.hpp"

void go::MonteCarloThread::_runTask()
{
    while (_run) {
        _task();
    }
}

void go::MonteCarloThread::registerTask(const std::function<void()> &task)
{
    _task = task;
}

void go::MonteCarloThread::launchThread(std::size_t nbThread)
{
    for (std::size_t i = 0; i < nbThread; ++i) {
        _thread.emplace_back([this]() { _runTask(); });
    }
}

void go::MonteCarloThread::stopThread()
{
    _run = false;
}

void go::MonteCarloThread::waitThread()
{
    for (auto &thread : _thread) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}
