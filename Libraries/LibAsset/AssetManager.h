/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <functional>

#include <LibAsset/AssetRegistry.h>
#include <LibAsset/Export.h>
#include <LibAsset/ModelImporter.h>
#include <LibAsset/ShaderImporter.h>
#include <LibAsset/TextureImporter.h>

namespace Asset {

class ASSET_API AssetManager final {
    OA_MAKE_DEFAULT_CONSTRUCTIBLE(AssetManager);
    OA_MAKE_NONCOPYABLE(AssetManager);
    OA_MAKE_NONMOVABLE(AssetManager);

public:
    AssetManager(std::filesystem::path const& root_directory);

    void load_loose_assets();
    void load_packed_assets();

    template<typename T>
    auto import(std::string const& key) const -> std::expected<T, std::string>
    {
        auto id = m_asset_registry.key_to_id(key);
        if (!id) {
            return std::unexpected(std::format("Asset with key '{}' not found.", key));
        }
        return import<T>(id.value());
    }

    template<typename T>
    auto import(AssetID id) const -> std::expected<T, std::string>
    {
        auto entry = m_asset_registry.resolve(id);
        if (!entry) {
            return std::unexpected(std::move(entry).error());
        }

        auto const& asset_entry = entry.value();

        if (asset_entry.source_type == AssetSourceType::Packed) {
            return std::unexpected("Packed assets are not supported yet");
        }

        auto const& asset_source = std::get<LooseAssetEntry>(asset_entry.source);
        if constexpr (std::same_as<T, Graphics::ModelConfiguration>) {
            return ModelImporter::import(asset_source.path, m_texture_resolver);
        } else {
            return ImporterTrait<T>::type::import(asset_source.path);
        }
    }
private:
    AssetRegistry m_asset_registry;
    TextureResolver m_texture_resolver;
};

}
