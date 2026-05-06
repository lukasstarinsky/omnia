/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <functional>

#include <LibAsset/Export.h>
#include <LibAsset/Importer.h>
#include <LibGraphics/TextureTypes.h>

namespace Asset {

using TextureResolver = std::function<std::optional<Graphics::TextureConfiguration>(std::filesystem::path const&)>;

class ASSET_API TextureImporter final {
public:
    static auto import(std::filesystem::path const& path) -> std::expected<Graphics::TextureConfiguration, std::string>;
    static auto supported_extensions() -> std::vector<std::string>;
};

template<>
struct ImporterTrait<Graphics::TextureConfiguration> {
    using type = TextureImporter;
};

}
