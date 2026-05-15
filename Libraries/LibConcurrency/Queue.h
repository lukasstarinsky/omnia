/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <atomic>
#include <mutex>
#include <optional>
#include <queue>

#include <Common/Types.h>

namespace Concurrency {

template<typename T>
concept QueueHasFront = requires(T a) {
    { a.front() };
};

template<typename T>
concept QueueHasTop = requires(T a) {
    { a.top() };
};

template<typename T, typename Q>
class BaseQueue {
public:
    auto pop() -> std::optional<T>
    requires(QueueHasFront<Q>)
    {
        std::unique_lock lock(m_mutex);
        if (m_queue.empty()) {
            return std::nullopt;
        }
        auto value = std::move(m_queue.front());
        m_queue.pop();
        return value;
    }

    auto pop() -> std::optional<T>
    requires(QueueHasTop<Q>)
    {
        std::unique_lock lock(m_mutex);
        if (m_queue.empty()) {
            return std::nullopt;
        }
        auto value = std::move(m_queue.top());
        m_queue.pop();
        return value;
    }

    void push(T&& value)
    {
        std::unique_lock lock(m_mutex);
        m_queue.push(std::move(value));
    }

    void push(T const& value)
    {
        std::unique_lock lock(m_mutex);
        m_queue.push(value);
    }

    auto empty() -> bool
    {
        std::unique_lock lock(m_mutex);
        return m_queue.empty();
    }

    auto peek() -> std::optional<T>
    requires(QueueHasFront<Q>)
    {
        std::unique_lock lock(m_mutex);
        if (m_queue.empty()) {
            return std::nullopt;
        }
        return m_queue.front();
    }

    auto peek() -> std::optional<T>
    requires(QueueHasTop<Q>)
    {
        std::unique_lock lock(m_mutex);
        if (m_queue.empty()) {
            return std::nullopt;
        }
        return m_queue.top();
    }

    auto collect() -> Q
    {
        Q collected_queue;
        {
            std::unique_lock lock(m_mutex);
            std::ranges::swap(m_queue, collected_queue);
        }
        return collected_queue;
    }
private:
    Q m_queue;
    std::mutex m_mutex;
};

template<typename T>
using Queue = BaseQueue<T, std::queue<T>>;

template<typename T, typename Compare = std::less<T>>
using PriorityQueue = BaseQueue<T, std::priority_queue<T, std::vector<T>, Compare>>;

}
