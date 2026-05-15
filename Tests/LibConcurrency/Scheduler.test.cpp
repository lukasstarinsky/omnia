/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <print>
#include <gtest/gtest.h>

#include <LibConcurrency/Awaitable.h>
#include <LibConcurrency/Task.h>
#include <LibConcurrency/Scheduler.h>

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

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    scheduler.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    scheduler.update();
    EXPECT_NE(worker_thread_task_.result(), std::this_thread::get_id());
}