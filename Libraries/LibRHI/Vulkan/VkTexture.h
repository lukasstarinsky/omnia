/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <expected>
#include <memory>
#include <string>

#include <Common/Noncopyable.h>
#include <LibRHI/Texture.h>

namespace RHI {

class VkTexture final : public Texture {
    OA_MAKE_NONCOPYABLE(VkTexture);
    OA_MAKE_NONMOVABLE(VkTexture);

public:
    static auto create(Configuration const& config) -> std::expected<std::unique_ptr<VkTexture>, std::string>;

    ~VkTexture() override;

    auto config() const -> Configuration const& override;
private:
    VkTexture() = default;
private:
    Configuration m_config {};
};

}
