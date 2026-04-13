/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Common/Types.h>
#include <LibAsset/Importer.h>
#include <LibAsset/Export.h>

namespace Asset {

enum class ShaderFormat : u8 {
    SPIRV = 0,
    DXIL,
    MetalIR
};

enum class ShaderStage : u8 {
    Vertex = 0,
    Fragment,
};

struct ShaderVariant {
    ShaderFormat format;
    std::vector<u8> bytecode;
};

struct ShaderData : public ImportedData {
    ShaderStage stage;
    std::vector<ShaderVariant> variants;
};

class ASSET_API ShaderImporter final : public Importer {
public:
    auto import(std::filesystem::path const& path) -> std::expected<std::any, std::string> override;
    auto supported_extensions() const -> std::vector<std::string> override;
};

}
