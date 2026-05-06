/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibAsset/AssetManager.h>

namespace Asset {

AssetManager::AssetManager(std::filesystem::path const& root_directory)
    : m_asset_registry(root_directory)
{
    m_texture_resolver = [this](std::filesystem::path const& texture_path) -> std::optional<Graphics::TextureConfiguration> {
        auto key = m_asset_registry.resolve_key(texture_path);
        auto result = import<Graphics::TextureConfiguration>(key);
        if (!result.has_value()) {
            return std::nullopt;
        }
        return result.value();
    };
}

void AssetManager::load_loose_assets()
{
    m_asset_registry.scan();
}

void AssetManager::load_packed_assets()
{
}

}
