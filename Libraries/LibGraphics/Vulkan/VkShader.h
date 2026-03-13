/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Shader.h"
#include <Common/Noncopyable.h>

#include <expected>
#include <memory>
#include <string>

namespace Graphics {

class VkShader final : public Shader {
    OA_MAKE_NONCOPYABLE(VkShader);
    OA_MAKE_NONMOVABLE(VkShader);

public:
    static auto create(Configuration const& config) -> std::expected<std::unique_ptr<VkShader>, std::string>;

    ~VkShader() override;

    auto config() const -> Configuration const& override;
private:
    VkShader() = default;
private:
    Configuration m_config;
};

}
