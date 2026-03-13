/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Forward.h"
#include <Common/Types.h>
#include <LibGraphics/Export.h>

#include <string_view>

namespace Graphics {

class GRAPHICS_API Renderer final {
public:
    enum class API : u8 {
        Vulkan = 0,
        D3D12,
        Metal
    };

    static auto api_to_string(API api) -> std::string_view;

    Renderer(Device* device, Swapchain* swapchain);

    void begin_frame();
    void end_frame();
private:
    Device* m_device {};
    Swapchain* m_swapchain {};
};

}
