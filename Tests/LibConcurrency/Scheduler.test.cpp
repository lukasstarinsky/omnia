/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <gtest/gtest.h>

#include <LibConcurrency/Awaitable.h>
#include <LibConcurrency/Task.h>
#include <LibConcurrency/Scheduler.h>

auto sleep_task() -> Concurrency::Task<void>
{
    co_await Concurrency::WaitFor(2s);
}

auto worker_thread_task() -> Concurrency::Task<std::thread::id>
{
    co_await Concurrency::SwitchToWorkerThread {};
    auto id = std::this_thread::get_id();
    co_await Concurrency::SwitchToMainThread {};
    co_return id;
}

TEST(Scheduler, WorkerThreadExecution)
{
    Concurrency::Scheduler scheduler;
    auto worker_thread_task_ = worker_thread_task();
    worker_thread_task_.resume();

    while (!worker_thread_task_.done())
    {
        scheduler.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    EXPECT_NE(worker_thread_task_.result(), std::this_thread::get_id());
}

TEST(Scheduler, DelayedTaskExecution)
{
    Concurrency::Scheduler scheduler;
    auto sleep_task_ = sleep_task();
    sleep_task_.resume();

    auto start_time = std::chrono::steady_clock::now();
    while (!sleep_task_.done())
    {
        scheduler.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    auto end_time = std::chrono::steady_clock::now();
    EXPECT_GE(end_time - start_time, 2s);
}