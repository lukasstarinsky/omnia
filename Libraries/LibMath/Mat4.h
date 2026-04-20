/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <array>
#include <cassert>

#include <Common/Types.h>

namespace Math {

template<typename T = f32>
class Mat4 {
public:
    constexpr Mat4() = default;

    constexpr Mat4(T diagonal)
    {
        m_elements[0] = diagonal;
        m_elements[5] = diagonal;
        m_elements[10] = diagonal;
        m_elements[15] = diagonal;
    }

    constexpr Mat4(std::array<T, 16> elements)
        : m_elements(elements)
    {
    }

    constexpr auto operator[](size_t index) -> T&
    {
        assert(index > 0 && index < m_elements.size());
        return m_elements[index];
    }

    constexpr auto operator[](size_t index) const -> T const&
    {
        assert(index > 0 && index < m_elements.size());
        return m_elements[index];
    }

    static constexpr auto identity() -> Mat4
    {
        return Mat4(1);
    }
private:
    std::array<T, 16> m_elements {};
};

using Mat4f = Mat4<f32>;
using Mat4d = Mat4<f64>;
using Mat4i = Mat4<i32>;
using Mat4l = Mat4<i64>;
using Mat4u = Mat4<u32>;
using Mat4ul = Mat4<u64>;

}
