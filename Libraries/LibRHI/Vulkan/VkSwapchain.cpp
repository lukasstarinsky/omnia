/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "VkSwapchain.h"

namespace RHI {

auto VkSwapchain::create(Configuration const& config) -> std::expected<std::unique_ptr<VkSwapchain>, std::string>
{
    (void)config;
    std::unique_ptr<VkSwapchain> swapchain(new VkSwapchain);
    return swapchain;
}

VkSwapchain::~VkSwapchain()
{
}

void VkSwapchain::present()
{
}

auto VkSwapchain::config() const -> Configuration const&
{
    return m_config;
}

}
