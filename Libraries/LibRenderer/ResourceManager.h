/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibAsset/AssetManager.h>
#include <LibRHI/Device.h>
#include <LibRenderer/Export.h>
#include <LibRenderer/Model.h>

namespace Renderer {

class RENDERER_API ResourceManager final {
public:
    static auto create(Asset::AssetManager const* asset_manager, RHI::Device* device) -> std::expected<std::unique_ptr<ResourceManager>, std::string>;

    auto resource_layout() const -> RHI::ResourceLayout const*;
    auto load_model(std::string const& asset_name) -> std::expected<std::unique_ptr<Model>, std::string>;
    auto load_model(Asset::AssetID asset_id) -> std::expected<std::unique_ptr<Model>, std::string>;
    auto load_shader(std::string const& asset_name) -> std::expected<std::unique_ptr<RHI::Shader>, std::string>;
    auto load_shader(Asset::AssetID asset_id) -> std::expected<std::unique_ptr<RHI::Shader>, std::string>;
private:
    ResourceManager() = default;

    auto load_texture(Asset::AssetID asset_id) -> std::expected<RHI::Texture const*, std::string>;
private:
    Asset::AssetManager const* m_asset_manager {};
    Asset::AssetID m_default_texture_id { 0 };
    std::unique_ptr<RHI::ResourceLayout> m_material_resource_layout;
    RHI::Device* m_device {};
    std::unordered_map<Asset::AssetID, std::unique_ptr<RHI::Texture>> m_texture_cache;
};

}
