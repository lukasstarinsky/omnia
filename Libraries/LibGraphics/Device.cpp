/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Device.h"

#include "D3D12/DX12Device.h"
#include "Metal/MTLDevice.h"
#include "Vulkan/VkDevice.h"

#include <format>

namespace Graphics {

auto Device::create(Renderer::API api) -> std::expected<std::unique_ptr<Device>, std::string>
{
    switch (api) {
    case Renderer::API::Vulkan:
        return VkDevice::create();
    case Renderer::API::D3D12:
        return DX12Device::create();
    case Renderer::API::Metal:
        return MTLDevice::create();
    default:
        return std::unexpected(std::format("Unsupported graphics API '{}'", Renderer::api_to_string(api)));
    }
}

}
