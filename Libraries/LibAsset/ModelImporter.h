/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibAsset/Importer.h>
#include <LibGraphics/ModelTypes.h>

namespace Asset {

class ImportManager;

class ModelImporter final : public Importer {
public:
    ModelImporter(ImportManager const* import_manager);

    auto import(std::filesystem::path const& path) -> std::expected<std::any, std::string> override;
    auto supported_extensions() const -> std::vector<std::string> override;
private:
    auto import_obj(std::filesystem::path const& path) const -> std::expected<std::any, std::string>;
    auto import_mtl(std::filesystem::path const& path) const -> std::expected<std::vector<Graphics::MaterialConfiguration>, std::string>;
private:
    ImportManager const* m_import_manager {};
};

}
