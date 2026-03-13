/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Texture.h"
#include <Common/Noncopyable.h>

#include <expected>
#include <memory>
#include <string>

namespace Graphics {

class MTLTexture final : public Texture {
    OA_MAKE_NONCOPYABLE(MTLTexture);
    OA_MAKE_NONMOVABLE(MTLTexture);

public:
    static auto create(Configuration const& config) -> std::expected<std::unique_ptr<MTLTexture>, std::string>;

    ~MTLTexture() override;

    auto config() const -> Configuration const& override;
private:
    MTLTexture() = default;
private:
    Configuration m_config {};
};

}
