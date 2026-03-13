/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Renderer.h"

namespace Graphics {

auto Renderer::api_to_string(API api) -> std::string_view
{
    switch (api) {
    case API::Vulkan:
        return "Vulkan";
    case API::D3D12:
        return "D3D12";
    case API::Metal:
        return "Metal";
    default:
        return "Unknown";
    }
}

Renderer::Renderer(Device* device, Swapchain* swapchain)
    : m_device(device)
    , m_swapchain(swapchain)
{
}

void Renderer::begin_frame()
{
    (void)m_device;
    (void)m_swapchain;
}

void Renderer::end_frame()
{
}

}
