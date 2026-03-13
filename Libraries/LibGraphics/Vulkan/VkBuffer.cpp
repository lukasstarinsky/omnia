/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "VkBuffer.h"

namespace Graphics {

auto VkBuffer::create(Configuration const& config) -> std::expected<std::unique_ptr<VkBuffer>, std::string>
{
    std::unique_ptr<VkBuffer> buffer(new VkBuffer);
    buffer->m_config = config;
    return buffer;
}

VkBuffer::~VkBuffer()
{
}

void VkBuffer::map()
{
}

void VkBuffer::unmap()
{
}

auto VkBuffer::config() const -> Configuration const&
{
    return m_config;
}

}
