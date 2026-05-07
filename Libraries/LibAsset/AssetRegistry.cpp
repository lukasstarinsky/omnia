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

AssetRegistry::AssetRegistry(std::filesystem::path const& root_directory)
    : m_root_directory(root_directory)
{
}

void AssetRegistry::scan()
{
    if (m_root_directory.empty()) {
        return;
    }

    auto const model_extensions = ModelImporter::supported_extensions();
    auto const shader_extensions = ShaderImporter::supported_extensions();
    auto const texture_extensions = TextureImporter::supported_extensions();

    std::vector<std::string> supported_extensions;
    supported_extensions.reserve(model_extensions.size() + shader_extensions.size() + texture_extensions.size());
    supported_extensions.insert(supported_extensions.end(), model_extensions.begin(), model_extensions.end());
    supported_extensions.insert(supported_extensions.end(), shader_extensions.begin(), shader_extensions.end());
    supported_extensions.insert(supported_extensions.end(), texture_extensions.begin(), texture_extensions.end());

    for (auto const& entry : std::filesystem::recursive_directory_iterator(m_root_directory)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        if (std::ranges::find(supported_extensions.begin(), supported_extensions.end(), entry.path().extension().string()) == supported_extensions.end()) {
            continue;
        }

        AssetEntry const asset_entry {
            .id = Platform::UUID::generate(),
            .key = resolve_key(entry.path()),
            .source_type = AssetSourceType::Loose,
            .source = LooseAssetEntry { .path = entry.path() }
        };
        register_asset(asset_entry);
    }
}

void AssetRegistry::register_asset(AssetEntry const& entry)
{
    if (m_assets_by_key.contains(entry.key)) {
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

auto AssetRegistry::resolve_key(std::filesystem::path path) const -> std::string
{
    path = std::filesystem::weakly_canonical(path);
    path = std::filesystem::relative(path, m_root_directory);
    path.replace_extension("");
    return path.generic_string();
}

}
