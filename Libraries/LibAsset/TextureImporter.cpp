/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibAsset/TextureImporter.h>

namespace Asset {

auto TextureImporter::import(std::filesystem::path const& path) -> std::expected<std::any, std::string>
{
    (void)path;
    return {};
}

auto TextureImporter::supported_extensions() const -> std::vector<std::string>
{
    return { "png", "jpg", "jpeg", "bmp", "tga" };
}

}
