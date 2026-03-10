/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Common/Types.h>

namespace Math {

template<typename T = f32>
class Vec3 {
public:
    T x {};
    T y {};
    T z {};

    Vec3() = default;

    Vec3(T x, T y, T z)
        : x(x)
        , y(y)
        , z(z)
    {
    }
};

using Vec3f = Vec3<f32>;
using Vec3d = Vec3<f64>;
using Vec3i = Vec3<i32>;
using Vec3l = Vec3<i64>;
using Vec3u = Vec3<u32>;
using Vec3ul = Vec3<u64>;

}
