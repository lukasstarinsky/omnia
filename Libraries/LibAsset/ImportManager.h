/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <memory>
#include <unordered_map>

#include <LibAsset/Importer.h>
#include <LibAsset/ModelImporter.h>

namespace Asset {

class ImportManager {
public:
    ImportManager() = default;

    void register_importer(std::shared_ptr<Importer> importer);
    auto import(std::filesystem::path const& path) -> std::expected<ImportedData, std::string>;
private:
    std::unordered_map<std::string, std::shared_ptr<Importer>> m_importers;
};

}
