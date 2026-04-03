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

namespace RHI {

auto Device::create(API api) -> std::expected<std::unique_ptr<Device>, std::string>
{
    switch (api) {
    case API::Vulkan:
        return VkDevice::create();
    case API::D3D12:
        return DX12Device::create();
    case API::Metal:
        return MTLDevice::create();
    }
}

}
