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
}

auto AssetManager::registry() const -> AssetRegistry const&
{
    return m_asset_registry;
}

void AssetManager::load_loose_assets()
{
    m_asset_registry.scan();
}

void AssetManager::load_packed_assets()
{
}

}
