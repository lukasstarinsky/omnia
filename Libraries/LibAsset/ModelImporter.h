/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibAsset/AssetRegistry.h>
#include <LibAsset/Export.h>
#include <LibAsset/Importer.h>
#include <LibAsset/TextureImporter.h>
#include <LibGraphics/ModelTypes.h>

namespace Asset {

class ASSET_API ModelImporter final {
public:
    static auto import(std::filesystem::path const& path, TextureResolver const& texture_resolver) -> std::expected<Graphics::ModelConfiguration, std::string>;
    static auto supported_extensions() -> std::vector<std::string>;
private:
    static auto import_obj(std::filesystem::path const& path, TextureResolver const& texture_resolver) -> std::expected<Graphics::ModelConfiguration, std::string>;
    static auto import_mtl(std::filesystem::path const& path, TextureResolver const& texture_resolver) -> std::expected<std::vector<Graphics::MaterialConfiguration>, std::string>;
};

template<>
struct ImporterTrait<Graphics::ModelConfiguration> {
    using type = ModelImporter;
};

}
