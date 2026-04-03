/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "MTLTexture.h"

namespace RHI {

auto MTLTexture::create(Configuration const& config) -> std::expected<std::unique_ptr<MTLTexture>, std::string>
{
    std::unique_ptr<MTLTexture> texture(new MTLTexture);
    texture->m_config = config;
    return texture;
}

MTLTexture::~MTLTexture()
{
}

auto MTLTexture::config() const -> Configuration const&
{
    return m_config;
}

}
