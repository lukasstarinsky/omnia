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

    RHI::ResourceLayout::Configuration material_resource_layout_config {
        .bindings = {
            {
                .binding = 0,
                .type = RHI::ResourceType::UniformBuffer,
                .stage = Graphics::ShaderStage::Fragment
            },
        }
    };

    u32 const texture_count = 5U;
    for (u32 i = 1; i <= texture_count; i++) {
        material_resource_layout_config.bindings.push_back({
            .binding = i,
            .type = RHI::ResourceType::Texture,
            .stage = Graphics::ShaderStage::Fragment
        });
    }

    auto material_resource_layout_result = device->create_resource_layout(material_resource_layout_config);
    if (!material_resource_layout_result.has_value()) {
        return std::unexpected(std::move(material_resource_layout_result).error());
    }
    resource_manager->m_material_resource_layout = std::move(material_resource_layout_result).value();

    if (auto result = resource_manager->initialize_default_resources(); !result.has_value()) {
        return std::unexpected(std::move(result).error());
    }
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

    auto resolve_texture = [&](std::optional<Asset::AssetID> const& texture_id, Asset::AssetID default_id) -> RHI::Texture const* {
        assert(m_texture_cache.contains(default_id));

        if (!texture_id.has_value()) {
            return m_texture_cache[default_id].get();
        }
        RHI::TextureFormat format = RHI::TextureFormat::R8G8B8A8_UNORM;
        if (default_id == DefaultResource::albedo_texture_id) {
            format = RHI::TextureFormat::R8G8B8A8_SRGB;
        }
        auto const texture_result = load_texture(texture_id.value(), format);
        if (!texture_result) {
            return m_texture_cache[default_id].get();
        }
        return texture_result.value();
    };

    Model::Configuration model_config {
        .sub_meshes = model_data->sub_meshes,
        .materials = {}
    };
    model_config.materials.reserve(model_data->materials.size());
    for (auto const& material_data : model_data->materials) {
        Material::Configuration material_config {
            .name = material_data.name,
            .albedo_texture = resolve_texture(material_data.albedo_texture_id, DefaultResource::albedo_texture_id),
            .metallic_roughness_texture = resolve_texture(material_data.metallic_roughness_texture_id, DefaultResource::metallic_roughness_texture_id),
            .normal_texture = resolve_texture(material_data.normal_texture_id, DefaultResource::normal_texture_id),
            .occlusion_texture = resolve_texture(material_data.occlusion_texture_id, DefaultResource::occlusion_texture_id),
            .emissive_texture = resolve_texture(material_data.emissive_texture_id, DefaultResource::emissive_texture_id),
            .resource_layout = m_material_resource_layout.get(),
            .parameters = material_data.parameters
        };
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

auto ResourceManager::load_texture(Asset::AssetID asset_id, RHI::TextureFormat format) -> std::expected<RHI::Texture const*, std::string>
{
    if (auto const it = m_texture_cache.find(asset_id); it != m_texture_cache.end()) {
        return it->second.get();
    }

    auto const texture_data = m_asset_manager->import<Asset::TextureData>(asset_id);
    if (!texture_data) {
        return std::unexpected(std::move(texture_data).error());
    }

    RHI::Texture::Configuration const texture_config {
        .width = texture_data->width,
        .height = texture_data->height,
        .format = format,
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

auto ResourceManager::initialize_default_resources() -> std::expected<void, std::string>
{
    RHI::Texture::Configuration const default_texture_config {
        .width = 1,
        .height = 1,
        .format = RHI::TextureFormat::R8G8B8A8_SRGB,
        .usage = RHI::TextureUsage::Sampled,
        .data = { 255, 255, 255, 255 }
    };
    RHI::Texture::Configuration const default_normal_texture_config {
        .width = 1,
        .height = 1,
        .format = RHI::TextureFormat::R8G8B8A8_UNORM,
        .usage = RHI::TextureUsage::Sampled,
        .data = { 128, 128, 255, 255 }
    };
    RHI::Texture::Configuration const default_metallic_roughness_texture_config {
        .width = 1,
        .height = 1,
        .format = RHI::TextureFormat::R8G8B8A8_UNORM,
        .usage = RHI::TextureUsage::Sampled,
        .data = { 255, 255, 0, 255 }
    };
    RHI::Texture::Configuration const default_occlusion_texture_config {
        .width = 1,
        .height = 1,
        .format = RHI::TextureFormat::R8G8B8A8_UNORM,
        .usage = RHI::TextureUsage::Sampled,
        .data = { 255, 255, 255, 255 }
    };
    RHI::Texture::Configuration const default_emissive_texture_config {
        .width = 1,
        .height = 1,
        .format = RHI::TextureFormat::R8G8B8A8_UNORM,
        .usage = RHI::TextureUsage::Sampled,
        .data = { 0, 0, 0, 255 }
    };

    std::unordered_map<Asset::AssetID, RHI::Texture::Configuration> const default_textures = {
        { DefaultResource::albedo_texture_id, default_texture_config },
        { DefaultResource::normal_texture_id, default_normal_texture_config },
        { DefaultResource::metallic_roughness_texture_id, default_metallic_roughness_texture_config },
        { DefaultResource::occlusion_texture_id, default_occlusion_texture_config },
        { DefaultResource::emissive_texture_id, default_emissive_texture_config }
    };

    for (auto const& [asset_id, texture_config] : default_textures) {
        if (auto const it = m_texture_cache.find(asset_id); it != m_texture_cache.end()) {
            continue;
        }

        auto texture_create_result = m_device->create_texture(texture_config);
        if (!texture_create_result) {
            return std::unexpected(std::move(texture_create_result).error());
        }

        m_texture_cache[asset_id] = std::move(texture_create_result).value();
    }
    return {};
}

}
