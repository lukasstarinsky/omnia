/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <vector>

#include <LibGraphics/ShaderTypes.h>
#include <Common/Noncopyable.h>
#include <Common/Types.h>

namespace RHI {

class Shader {
    OA_MAKE_NONCOPYABLE(Shader);
    OA_MAKE_DEFAULT_MOVABLE(Shader);

public:
    using Configuration = ::Shader::Configuration;

    virtual ~Shader() = default;

    virtual auto config() const -> Configuration const& = 0;
protected:
    Shader() = default;
};

}
