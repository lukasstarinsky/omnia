/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibConcurrency/Awaitable.h>

namespace Concurrency {

Awaitable::Awaitable(Scheduler& scheduler)
    : m_scheduler(scheduler)
{
}

auto Awaitable::NextTickAwaiter::await_ready() const noexcept -> bool
{
    return false;
}

void Awaitable::NextTickAwaiter::await_suspend(std::coroutine_handle<> handle) const noexcept
{
    Scheduler::ScheduledTask task {
        .handle = handle,
        .thread = ExecutionThread::Main,
        .ready_time = std::chrono::steady_clock::now()
    };
    scheduler.schedule(task);
}

auto Awaitable::ThreadSwitchAwaiter::await_ready() const noexcept -> bool
{
    return false;
}

void Awaitable::ThreadSwitchAwaiter::await_suspend(std::coroutine_handle<> handle) const noexcept
{
    Scheduler::ScheduledTask task {
        .handle = handle,
        .thread = target_context,
        .ready_time = std::chrono::steady_clock::now()
    };
    scheduler.schedule(task);
}

auto Awaitable::WaitAwaiter::await_ready() const noexcept -> bool
{
    return duration.count() <= 0;
}

void Awaitable::WaitAwaiter::await_suspend(std::coroutine_handle<> handle) const noexcept
{
    Scheduler::ScheduledTask task {
        .handle = handle,
        .thread = ExecutionThread::Main,
        .ready_time = std::chrono::steady_clock::now() + duration
    };
    scheduler.schedule(task);
}

auto Awaitable::operator()() const -> NextTickAwaiter
{
    return NextTickAwaiter { m_scheduler };
}

auto Awaitable::operator()(ExecutionThread target_context) const -> ThreadSwitchAwaiter
{
    return ThreadSwitchAwaiter { m_scheduler, target_context };
}

auto Awaitable::operator()(std::chrono::milliseconds duration) const -> WaitAwaiter
{
    return WaitAwaiter { m_scheduler, duration };
}

}
