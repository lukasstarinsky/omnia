/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Device.h"
#include "D3D12/DX12Device.h"
#include "Metal/MTLDevice.h"
#include "Vulkan/VkDevice.h"

namespace RHI {

auto Device::create(Configuration const& config) -> std::expected<std::unique_ptr<Device>, std::string>
{
    switch (config.api) {
    case API::Vulkan:
        return VkDevice::create(config);
    case API::D3D12:
        return DX12Device::create();
    case API::Metal:
        return MTLDevice::create();
    }
}

}
