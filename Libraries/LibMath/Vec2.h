/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Common/Types.h>

namespace Math {

template<typename T = f32>
class Vec2 {
public:
    T x {};
    T y {};

    Vec2() = default;

    Vec2(T x, T y)
        : x(x)
        , y(y)
    {
    }
};

using Vec2f = Vec2<f32>;
using Vec2d = Vec2<f64>;
using Vec2i = Vec2<i32>;
using Vec2l = Vec2<i64>;
using Vec2u = Vec2<u32>;
using Vec2ul = Vec2<u64>;

}
