/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibAsset/ImportManager.h>

namespace Asset {

void ImportManager::register_importer(std::shared_ptr<Importer> importer)
{
    for (auto const& extension : importer->supported_extensions()) {
        m_importers[extension] = importer;
    }
}

auto ImportManager::import(std::filesystem::path const& path) -> std::expected<ImportedData, std::string>
{
    auto extension = path.extension().string();
    auto it = m_importers.find(extension);
    if (it == m_importers.end()) {
        return std::unexpected(std::format("No importer registered for extension '{}'", extension));
    }

    return it->second->import(path);
}

}
