/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibAsset/AssetRegistry.h>
#include <LibAsset/ModelImporter.h>
#include <LibAsset/ShaderImporter.h>
#include <LibAsset/TextureImporter.h>

namespace Asset {

void AssetRegistry::scan(std::filesystem::path const& root_directory)
{
    auto const model_extensions = ModelImporter::supported_extensions();
    auto const models_root = root_directory / "Models";

    auto const shader_extensions = ShaderImporter::supported_extensions();
    auto const shaders_root = root_directory / "Shaders";

    auto const texture_extensions = TextureImporter::supported_extensions();
    auto const textures_root = root_directory / "Textures";

    scan(models_root, model_extensions);
    scan(shaders_root, shader_extensions);
    scan(textures_root, texture_extensions);
}

void AssetRegistry::scan(std::filesystem::path const& directory, std::vector<std::string> const& extensions)
{
    for (auto const& entry : std::filesystem::recursive_directory_iterator(directory)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        if (std::ranges::find(extensions.begin(), extensions.end(), entry.path().extension()) == extensions.end()) {
            continue;
        }

        auto const& path = entry.path();
        auto key = path.lexically_relative(directory).replace_extension().string();
        std::ranges::replace(key, '\\', ':');

        AssetEntry asset_entry {
            .id = std::hash<std::string> {}(key),
            .key = key,
            .source_type = AssetSourceType::Loose,
            .source = LooseAssetEntry { .path = path }
        };
        register_asset(asset_entry);
    }
}

void AssetRegistry::register_asset(AssetEntry const& entry)
{
    if (m_keys_by_id.contains(entry.id)) {
        return;
    }
    m_assets_by_key[entry.key] = entry;
    m_keys_by_id[entry.id] = entry.key;
}

auto AssetRegistry::key_to_id(std::string const& key) const -> std::optional<AssetID>
{
    if (!m_assets_by_key.contains(key)) {
        return std::nullopt;
    }
    return m_assets_by_key.at(key).id;
}

auto AssetRegistry::resolve(AssetID id) const -> std::expected<AssetEntry, std::string>
{
    auto key_it = m_keys_by_id.find(id);
    if (key_it == m_keys_by_id.end()) {
        return std::unexpected(std::format("Asset with ID {} not found in asset registry.", id));
    }

    auto asset_it = m_assets_by_key.find(key_it->second);
    if (asset_it == m_assets_by_key.end()) {
        return std::unexpected(std::format("Asset with ID {} not found in asset registry.", id));
    }

    return asset_it->second;
}

}
