/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <expected>
#include <filesystem>
#include <unordered_map>
#include <variant>

#include <Common/Noncopyable.h>
#include <Common/Types.h>
#include <LibAsset/Export.h>
#include <LibPlatform/UUID.h>

namespace Asset {

using AssetID = Platform::UUID;

enum class AssetSourceType {
    Loose = 0,
    Packed
};

struct LooseAssetEntry {
    std::filesystem::path path;
};

struct PackedAssetEntry {
    u64 offset;
    u64 size;
};

struct AssetEntry {
    AssetID id;
    std::string key;
    AssetSourceType source_type;
    std::variant<LooseAssetEntry, PackedAssetEntry> source;
};

class ASSET_API AssetRegistry final {
    OA_MAKE_DEFAULT_CONSTRUCTIBLE(AssetRegistry);

public:
    AssetRegistry(std::filesystem::path const& root_directory);

    void scan();
    void register_asset(AssetEntry const& entry);
    auto key_to_id(std::string const& key) const -> std::optional<AssetID>;
    auto resolve(AssetID id) const -> std::expected<AssetEntry, std::string>;
    auto resolve_key(std::filesystem::path path) const -> std::string;
private:
    std::filesystem::path m_root_directory;
    std::unordered_map<std::string, AssetEntry> m_assets_by_key;
    std::unordered_map<AssetID, std::string> m_keys_by_id;
};

}
