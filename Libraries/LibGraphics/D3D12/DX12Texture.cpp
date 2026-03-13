/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "DX12Texture.h"

namespace Graphics {

auto DX12Texture::create(Configuration const& config) -> std::expected<std::unique_ptr<DX12Texture>, std::string>
{
    std::unique_ptr<DX12Texture> texture(new DX12Texture);
    texture->m_config = config;
    return texture;
}

DX12Texture::~DX12Texture()
{
}

auto DX12Texture::config() const -> Configuration const&
{
    return m_config;
}

}
