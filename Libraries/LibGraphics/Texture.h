/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Common/Noncopyable.h>

namespace Graphics {

class Texture {
    OA_MAKE_NONCOPYABLE(Texture);
    OA_MAKE_NONMOVABLE(Texture);

public:
    struct Configuration {

    };

    virtual ~Texture() = default;

    virtual auto config() const -> Configuration const& = 0;
protected:
    Texture() = default;
};

}
