/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibConcurrency/Scheduler.h>

namespace Concurrency {

void Scheduler::schedule(ScheduledTask const& task)
{
    if (task.ready_time <= std::chrono::steady_clock::now()) {
        m_ready_tasks.push(task);
    } else {
        m_delayed_tasks.push(task);
    }
}

void Scheduler::update()
{
    auto now = std::chrono::steady_clock::now();

    while (auto task = m_delayed_tasks.peek()) {
        if (task->ready_time > now) {
            break;
        }
        m_ready_tasks.push(task.value());
        m_delayed_tasks.pop();
    }

    auto tasks = m_ready_tasks.collect();
    while (!tasks.empty()) {
        auto& task = tasks.front();
        if (task.thread == ExecutionThread::Main) {
            task.handle.resume();
        } else {
            m_thread_pool.submit([handle = task.handle] {
                handle.resume();
            });
        }
        tasks.pop();
    }
}

}
