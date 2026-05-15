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

enum class ExecutionThread : u8 {
    Main = 0,
    Worker
};

class CONCURRENCY_API Scheduler {
public:
    struct ScheduledTask {
        std::coroutine_handle<> handle;
        ExecutionThread thread {};
        std::chrono::steady_clock::time_point ready_time;

        auto operator>(ScheduledTask const& other) const -> bool
        {
            return ready_time > other.ready_time;
        }
    };

    Scheduler() = default;

    void schedule(ScheduledTask const& task);
    void update();
private:
    ThreadPool m_thread_pool;

    Queue<ScheduledTask> m_ready_tasks;
    PriorityQueue<ScheduledTask, std::greater<ScheduledTask>> m_delayed_tasks;
};

}
