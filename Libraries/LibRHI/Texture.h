/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Common/Noncopyable.h>
#include <LibGraphics/TextureTypes.h>
#include <LibMath/Vec3.h>

namespace RHI {

class Texture {
    OA_MAKE_NONCOPYABLE(Texture);
    OA_MAKE_DEFAULT_MOVABLE(Texture);

public:
    using Configuration = Graphics::TextureConfiguration;

    virtual ~Texture() = default;

    virtual auto config() const -> Configuration const& = 0;
protected:
    Texture() = default;
};

}
