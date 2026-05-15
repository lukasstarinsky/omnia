/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <cassert>
#include <chrono>
#include <coroutine>

#include <LibConcurrency/Scheduler.h>

using namespace std::chrono_literals;

namespace Concurrency {

struct SwitchToMainThread {
    auto await_ready() const noexcept -> bool
    {
        return false;
    }

    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
        assert(Scheduler::current() != nullptr && "Awaitable used without a scheduler context.");
        Scheduler::current()->schedule({
            .handle = handle,
            .context = ExecutionContext::Main,
            .ready_time = std::chrono::steady_clock::time_point::min()
        });
    }

    void await_resume() const noexcept { }
};

struct SwitchToWorkerThread {
    auto await_ready() const noexcept -> bool
    {
        return false;
    }

    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
        assert(Scheduler::current() != nullptr && "Awaitable used without a scheduler context.");
        Scheduler::current()->schedule({
            .handle = handle,
            .context = ExecutionContext::Worker,
            .ready_time = std::chrono::steady_clock::time_point::min()
        });
    }

    void await_resume() const noexcept { }
};

struct Yield {
    auto await_ready() const noexcept -> bool
    {
        return false;
    }

    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
        assert(Scheduler::current() != nullptr && "Awaitable used without a scheduler context.");
        Scheduler::current()->schedule({
            .handle = handle,
            .context = ExecutionContext::Main,
            .ready_time = std::chrono::steady_clock::now()
        });
    }

    void await_resume() const noexcept { }
};

struct WaitFor {
    std::chrono::milliseconds duration;

    auto await_ready() const noexcept -> bool
    {
        return duration.count() <= 0;
    }

    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
        assert(Scheduler::current() != nullptr && "Awaitable used without a scheduler context.");
        Scheduler::current()->schedule({
            .handle = handle,
            .context = ExecutionContext::Main,
            .ready_time = std::chrono::steady_clock::now() + duration
        });
    }

    void await_resume() const noexcept { }
};

}
