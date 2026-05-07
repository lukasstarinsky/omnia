/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibAsset/Export.h>
#include <LibAsset/Importer.h>

namespace Asset {

struct TextureData {
    u32 width {};
    u32 height {};
    std::vector<u8> data;
};

class ASSET_API TextureImporter final {
public:
    static auto import(std::filesystem::path const& path) -> std::expected<TextureData, std::string>;
    static auto supported_extensions() -> std::vector<std::string>;
};

template<>
struct ImporterTrait<TextureData> {
    using type = TextureImporter;
};

}
