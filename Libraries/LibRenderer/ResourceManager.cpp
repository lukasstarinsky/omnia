/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibRenderer/ResourceManager.h>

namespace Renderer {

auto ResourceManager::create(Asset::AssetManager const* asset_manager, RHI::Device* device) -> std::expected<std::unique_ptr<ResourceManager>, std::string>
{
    assert(asset_manager != nullptr);
    assert(device != nullptr);

    std::unique_ptr<ResourceManager> resource_manager(new ResourceManager);
    resource_manager->m_asset_manager = asset_manager;
    resource_manager->m_device = device;

    RHI::Texture::Configuration const default_texture_config {
        .width = 1,
        .height = 1,
        .format = RHI::TextureFormat::R8G8B8A8_SRGB,
        .usage = RHI::TextureUsage::Sampled,
        .data = { 255, 255, 255, 255 }
    };
    auto default_texture_create_result = device->create_texture(default_texture_config);
    if (!default_texture_create_result.has_value()) {
        return std::unexpected(std::move(default_texture_create_result).error());
    }
    resource_manager->m_texture_cache[resource_manager->m_default_texture_id] = std::move(default_texture_create_result).value();

    RHI::ResourceLayout::Configuration const material_resource_layout_config {
        .bindings = {
            { .binding = 0,
                .type = RHI::ResourceType::Texture,
                .stage = Graphics::ShaderStage::Fragment },
            { .binding = 1,
                .type = RHI::ResourceType::UniformBuffer,
                .stage = Graphics::ShaderStage::Fragment } }
    };
    auto material_resource_layout_result = device->create_resource_layout(material_resource_layout_config);
    if (!material_resource_layout_result.has_value()) {
        return std::unexpected(std::move(material_resource_layout_result).error());
    }
    resource_manager->m_material_resource_layout = std::move(material_resource_layout_result).value();

    return resource_manager;
}

auto ResourceManager::resource_layout() const -> RHI::ResourceLayout const*
{
    return m_material_resource_layout.get();
}

auto ResourceManager::load_model(std::string const& asset_name) -> std::expected<std::unique_ptr<Model>, std::string>
{
    auto asset_id_result = m_asset_manager->registry().key_to_id(asset_name);
    if (!asset_id_result.has_value()) {
        return std::unexpected(std::format("Failed to find asset with name '{}'.", asset_name));
    }
    return load_model(asset_id_result.value());
}

auto ResourceManager::load_model(Asset::AssetID asset_id) -> std::expected<std::unique_ptr<Model>, std::string>
{
    auto const model_data = m_asset_manager->import <Asset::ModelData>(asset_id);
    if (!model_data) {
        return std::unexpected(std::move(model_data).error());
    }

    Model::Configuration model_config {
        .sub_meshes = model_data->sub_meshes,
        .materials = {}
    };
    model_config.materials.reserve(model_data->materials.size());
    for (auto const& material_data : model_data->materials) {
        Material::Configuration material_config {
            .name = material_data.name,
            .albedo_texture = m_texture_cache[m_default_texture_id].get(),
            .resource_layout = m_material_resource_layout.get()
        };
        if (material_data.albedo_texture_id.has_value()) {
            auto const albedo_texture_result = load_texture(material_data.albedo_texture_id.value());
            if (!albedo_texture_result) {
                return std::unexpected(std::move(albedo_texture_result).error());
            }
            material_config.albedo_texture = albedo_texture_result.value();
        }
        model_config.materials.push_back(std::move(material_config));
    }

    auto model_create_result = Model::create(model_config, m_device);
    if (!model_create_result) {
        return std::unexpected(std::move(model_create_result).error());
    }
    return std::move(model_create_result).value();
}

auto ResourceManager::load_shader(std::string const& asset_name) -> std::expected<std::unique_ptr<RHI::Shader>, std::string>
{
    auto asset_id_result = m_asset_manager->registry().key_to_id(asset_name);
    if (!asset_id_result.has_value()) {
        return std::unexpected(std::format("Failed to find asset with name '{}'.", asset_name));
    }
    return load_shader(asset_id_result.value());
}

auto ResourceManager::load_shader(Asset::AssetID asset_id) -> std::expected<std::unique_ptr<RHI::Shader>, std::string>
{
    auto const shader_data = m_asset_manager->import <RHI::Shader::Configuration>(asset_id);
    if (!shader_data) {
        return std::unexpected(std::move(shader_data).error());
    }

    auto shader_create_result = m_device->create_shader(shader_data.value());
    if (!shader_create_result) {
        return std::unexpected(std::move(shader_create_result).error());
    }

    return std::move(shader_create_result).value();
}

auto ResourceManager::load_texture(Asset::AssetID asset_id) -> std::expected<RHI::Texture const*, std::string>
{
    if (auto const it = m_texture_cache.find(asset_id); it != m_texture_cache.end()) {
        return it->second.get();
    }

    auto const texture_data = m_asset_manager->import <Asset::TextureData>(asset_id);
    if (!texture_data) {
        return std::unexpected(std::move(texture_data).error());
    }

    RHI::Texture::Configuration const texture_config {
        .width = texture_data->width,
        .height = texture_data->height,
        .format = RHI::TextureFormat::R8G8B8A8_SRGB,
        .usage = RHI::TextureUsage::Sampled,
        .data = texture_data->data
    };

    auto texture_create_result = m_device->create_texture(texture_config);
    if (!texture_create_result) {
        return std::unexpected(std::move(texture_create_result).error());
    }

    m_texture_cache[asset_id] = std::move(texture_create_result).value();
    return m_texture_cache[asset_id].get();
}

}
