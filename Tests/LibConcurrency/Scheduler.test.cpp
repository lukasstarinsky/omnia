/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <gtest/gtest.h>

#include <LibConcurrency/Awaitable.h>
#include <LibConcurrency/Task.h>
#include <LibConcurrency/Scheduler.h>

auto sleep_task(Concurrency::Awaitable awaitable) -> Concurrency::Task<void>
{
    co_await awaitable(2s);
}

auto worker_thread_task(Concurrency::Awaitable awaitable) -> Concurrency::Task<std::thread::id>
{
    co_await awaitable(Concurrency::ExecutionThread::Worker);
    auto id = std::this_thread::get_id();
    co_await awaitable(Concurrency::ExecutionThread::Main);
    co_return id;
}

TEST(Scheduler, WorkerThreadExecution)
{
    Concurrency::Scheduler scheduler;
    Concurrency::Awaitable awaitable(scheduler);
    auto id_retrieve_task = worker_thread_task(awaitable);
    id_retrieve_task.resume();

    while (!id_retrieve_task.done())
    {
        scheduler.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    EXPECT_NE(id_retrieve_task.result(), std::this_thread::get_id());
}

TEST(Scheduler, DelayedTaskExecution)
{
    Concurrency::Scheduler scheduler;
    Concurrency::Awaitable awaitable(scheduler);
    auto delayed_execution_task = sleep_task(awaitable);
    delayed_execution_task.resume();

    auto start_time = std::chrono::steady_clock::now();
    while (!delayed_execution_task.done())
    {
        scheduler.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    auto end_time = std::chrono::steady_clock::now();
    EXPECT_GE(end_time - start_time, 2s);
}