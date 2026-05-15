/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <chrono>
#include <coroutine>

#include <LibConcurrency/Scheduler.h>
#include <LibConcurrency/Export.h>

using namespace std::chrono_literals;

namespace Concurrency {

class CONCURRENCY_API Awaitable {
public:
    explicit Awaitable(Scheduler& scheduler);

private:
    struct CONCURRENCY_API NextTickAwaiter {
        Scheduler& scheduler;

        auto await_ready() const noexcept -> bool;
        void await_suspend(std::coroutine_handle<> handle) const noexcept;
        void await_resume() const noexcept { }
    };

    struct CONCURRENCY_API ThreadSwitchAwaiter {
        Scheduler& scheduler;
        ExecutionThread target_context;

        auto await_ready() const noexcept -> bool;
        void await_suspend(std::coroutine_handle<> handle) const noexcept;
        void await_resume() const noexcept { }
    };

    struct CONCURRENCY_API WaitAwaiter {
        Scheduler& scheduler;
        std::chrono::milliseconds duration;

        auto await_ready() const noexcept -> bool;
        void await_suspend(std::coroutine_handle<> handle) const noexcept;
        void await_resume() const noexcept { }
    };
public:
    auto operator()() const -> NextTickAwaiter;
    auto operator()(ExecutionThread target_context) const -> ThreadSwitchAwaiter;
    auto operator()(std::chrono::milliseconds duration) const -> WaitAwaiter;
private:
    Scheduler& m_scheduler;
};

}
