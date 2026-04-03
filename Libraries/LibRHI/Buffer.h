/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Common/Noncopyable.h>

namespace RHI {

class Buffer {
    OA_MAKE_NONCOPYABLE(Buffer);
    OA_MAKE_NONMOVABLE(Buffer);

public:
    struct Configuration {

    };

    virtual ~Buffer() = default;

    virtual void map() = 0;
    virtual void unmap() = 0;
    virtual auto config() const -> Configuration const& = 0;
protected:
    Buffer() = default;
};

}
