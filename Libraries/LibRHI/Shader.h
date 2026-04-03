/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Common/Noncopyable.h>

namespace RHI {

class Shader {
    OA_MAKE_NONCOPYABLE(Shader);
    OA_MAKE_NONMOVABLE(Shader);

public:
    struct Configuration {

    };

    virtual ~Shader() = default;

    virtual auto config() const -> Configuration const& = 0;
protected:
    Shader() = default;
};

}
