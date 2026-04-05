/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibRHI/Vulkan/VkTexture.h>

namespace RHI {

auto VkTexture::create(Configuration const& config) -> std::expected<std::unique_ptr<VkTexture>, std::string>
{
    std::unique_ptr<VkTexture> texture(new VkTexture);
    texture->m_config = config;
    return texture;
}

VkTexture::~VkTexture()
{
}

auto VkTexture::config() const -> Configuration const&
{
    return m_config;
}

}
