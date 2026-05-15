/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <coroutine>

#include <LibConcurrency/ThreadPool.h>
#include <LibConcurrency/Queue.h>
#include <LibConcurrency/Export.h>

namespace Concurrency {

enum class ExecutionContext {
    Main = 0,
    Worker
};

struct ScheduledTask {
    std::coroutine_handle<> handle;
    ExecutionContext context;
    std::chrono::steady_clock::time_point ready_time;

    auto operator>(ScheduledTask const& other) const -> bool
    {
        return ready_time > other.ready_time;
    }
};

class CONCURRENCY_API Scheduler {
public:
    Scheduler();

    void schedule(ScheduledTask const& task);
    void update();

    static auto current() -> Scheduler*&;
private:
    ThreadPool m_thread_pool;

    Queue<ScheduledTask> m_ready_tasks;
    PriorityQueue<ScheduledTask, std::greater<ScheduledTask>> m_delayed_tasks;
};

}
