/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "VkShader.h"

namespace RHI {

auto VkShader::create(Configuration const& config) -> std::expected<std::unique_ptr<VkShader>, std::string>
{
    std::unique_ptr<VkShader> shader(new VkShader);
    shader->m_config = config;
    return shader;
}

VkShader::~VkShader()
{
}

auto VkShader::config() const -> Configuration const&
{
    return m_config;
}

}
