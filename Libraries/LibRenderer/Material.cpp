/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibRenderer/Material.h>

namespace Renderer {

auto Material::create(Configuration const& configuration, RHI::Device* device) -> std::expected<Material, std::string>
{
    assert(configuration.resource_layout != nullptr);
    assert(configuration.albedo_texture != nullptr);

    Material material;
    material.m_base_data = {
        .base_color = configuration.base_color
    };

    auto resource_set_configuration = RHI::ResourceSet::Configuration {
        .layout = configuration.resource_layout,
    };
    auto resource_set_result = device->create_resource_set(resource_set_configuration);
    if (!resource_set_result.has_value()) {
        return std::unexpected(std::move(resource_set_result).error());
    }
    material.m_resource_set = std::move(resource_set_result).value();

    auto uniform_buffer_configuration = RHI::Buffer::Configuration {
        .size = sizeof(BaseData),
        .usage = RHI::BufferUsage::Uniform,
        .data = &material.m_base_data
    };
    auto uniform_buffer_result = device->create_buffer(uniform_buffer_configuration);
    if (!uniform_buffer_result.has_value()) {
        return std::unexpected(std::move(uniform_buffer_result).error());
    }
    material.m_uniform_buffer = std::move(uniform_buffer_result).value();

    material.m_resource_set->set_texture(0, configuration.albedo_texture);
    material.m_resource_set->set_uniform_buffer(1, material.m_uniform_buffer.get());

    return material;
}

auto Material::resource_set() const -> RHI::ResourceSet const*
{
    return m_resource_set.get();
}

}
