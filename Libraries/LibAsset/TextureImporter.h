/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibAsset/Importer.h>

namespace Asset {

struct TextureData : public ImportedData {
};

class TextureImporter final : public Importer {
public:
    auto import(std::filesystem::path const& path) -> std::expected<ImportedData, std::string> override;
    auto supported_extensions() const -> std::vector<std::string> override;
};

}
