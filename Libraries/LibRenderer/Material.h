/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibGraphics/ModelTypes.h>
#include <LibRHI/Device.h>
#include <LibRenderer/Export.h>

namespace Renderer {

class RENDERER_API Material final {
    OA_MAKE_NONCOPYABLE(Material);
    OA_MAKE_DEFAULT_MOVABLE(Material);
    OA_MAKE_DEFAULT_DESTRUCTIBLE(Material);

public:
    struct BaseData {
        Math::Vec4f base_color { 1.0F, 1.0F, 1.0F, 1.0F };
    };

    struct Configuration : public BaseData {
        std::string name;
        RHI::Texture const* albedo_texture = nullptr;
        RHI::ResourceLayout const* resource_layout = nullptr;
    };

    static auto create(Configuration const& configuration, RHI::Device* device) -> std::expected<Material, std::string>;

    auto resource_set() const -> RHI::ResourceSet const*;
private:
    Material() = default;
private:
    BaseData m_base_data;
    std::unique_ptr<RHI::Buffer> m_uniform_buffer;
    std::unique_ptr<RHI::ResourceSet> m_resource_set;
};

}
