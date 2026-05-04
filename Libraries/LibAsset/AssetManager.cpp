/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibAsset/AssetManager.h>

namespace Asset {

AssetManager::AssetManager()
{
    m_default_texture_configuration = {
        .width = 1,
        .height = 1,
        .format = Graphics::TextureFormat::R8G8B8A8_UNORM,
        .usage = Graphics::TextureUsage::Sampled,
        .data = std::vector<u8>{ 255, 0, 255, 255 }
    };
    m_texture_resolver = [this](std::string const& texture_id) -> Graphics::TextureConfiguration {
        auto result = import<Graphics::TextureConfiguration>(texture_id);
        if (!result.has_value()) {
            return m_default_texture_configuration;
        }
        return result.value();
    };
}

void AssetManager::load_loose_assets(std::filesystem::path const& root_directory)
{
    m_asset_registry.scan(root_directory);
}

void AssetManager::load_packed_assets(std::filesystem::path const& packed_file_path)
{
    (void)packed_file_path;
}

}
