/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Common/Noncopyable.h>

namespace RHI {

class Swapchain {
    OA_MAKE_NONCOPYABLE(Swapchain);
    OA_MAKE_NONMOVABLE(Swapchain);

public:
    struct Configuration {

    };

    virtual ~Swapchain() = default;

    virtual void present() = 0;
    virtual auto config() const -> const Configuration& = 0;
protected:
    Swapchain() = default;
};

}
