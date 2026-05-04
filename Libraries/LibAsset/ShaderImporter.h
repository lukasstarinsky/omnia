/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibAsset/Export.h>
#include <LibAsset/Importer.h>
#include <LibGraphics/ShaderTypes.h>

namespace Asset {

class ASSET_API ShaderImporter final {
public:
    static auto import(std::filesystem::path const& path) -> std::expected<Graphics::ShaderConfiguration, std::string>;
    static auto supported_extensions() -> std::vector<std::string>;
};

template<>
struct ImporterTrait<Graphics::ShaderConfiguration> {
    using type = ShaderImporter;
};

}
