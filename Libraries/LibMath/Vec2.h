/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <cmath>

#include <Common/Types.h>

namespace Math {

template<typename T = f32>
class Vec2 {
public:
    T x {};
    T y {};

    constexpr Vec2() = default;

    constexpr Vec2(T x, T y)
        : x(x)
        , y(y)
    {
    }

    constexpr auto operator+(Vec2<T> const& other) const -> Vec2<T>
    {
        return Vec2 {
            x + other.x,
            y + other.y
        };
    }

    constexpr auto operator-(Vec2<T> const& other) const -> Vec2<T>
    {
        return Vec2 {
            x - other.x,
            y - other.y
        };
    }

    constexpr auto operator-() const -> Vec2<T>
    {
        return Vec2<T> {
            -x,
            -y
        };
    }

    constexpr auto operator*(T scalar) const -> Vec2<T>
    {
        return Vec2<T> {
            x * scalar,
            y * scalar
        };
    }

    constexpr auto operator/(T scalar) const -> Vec2<T>
    {
        return Vec2<T> {
            x / scalar,
            y / scalar
        };
    }

    constexpr auto operator+=(Vec2<T> const& other) -> Vec2<T>&
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr auto operator-=(Vec2<T> const& other) -> Vec2<T>&
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    constexpr auto operator*=(T scalar) -> Vec2<T>&
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr auto operator/=(T scalar) -> Vec2<T>&
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    constexpr auto length() const -> T
    {
        return std::sqrt((x * x) + (y * y));
    }

    constexpr void normalize()
    {
        auto length = this->length();

        if (length != 0) {
            x /= length;
            y /= length;
        }
    }

    constexpr auto normalized() const -> Vec2<T>
    {
        auto length = this->length();

        if (length != 0) {
            return Vec2<T> {
                x / length,
                y / length,
            };
        }

        return *this;
    }
};

template<typename T>
constexpr auto cross(Vec2<T> const& a, Vec2<T> const& b) -> T
{
    return (a.x * b.y) - (a.y * b.x);
}

template<typename T>
constexpr auto dot(Vec2<T> const& a, Vec2<T> const& b) -> T
{
    return (a.x * b.x) + (a.y * b.y);
}

using Vec2f = Vec2<f32>;
using Vec2d = Vec2<f64>;
using Vec2i = Vec2<i32>;
using Vec2l = Vec2<i64>;
using Vec2u = Vec2<u32>;
using Vec2ul = Vec2<u64>;

}
