/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibAsset/ModelImporter.h>

namespace Asset {

auto ModelImporter::import(std::filesystem::path const& path) -> std::expected<ImportedData, std::string>
{
    (void)path;
    return {};
}

auto ModelImporter::supported_extensions() const -> std::vector<std::string>
{
    return { "obj", "fbx", "gltf" };
}

}
