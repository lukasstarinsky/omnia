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

namespace Asset {

// TODO: Use UUID, start from UUID = 0 for default resources
using AssetID = u64;

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
    void scan(std::filesystem::path const& root_directory);
    void register_asset(AssetEntry const& entry);
    auto key_to_id(std::string const& key) const -> std::optional<AssetID>;
    auto resolve(AssetID id) const -> std::expected<AssetEntry, std::string>;
private:
    void scan(std::filesystem::path const& directory, std::vector<std::string> const& extensions);
private:
    std::unordered_map<std::string, AssetEntry> m_assets_by_key;
    std::unordered_map<AssetID, std::string> m_keys_by_id;
};

}
