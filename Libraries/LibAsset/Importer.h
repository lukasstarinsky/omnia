/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <any>
#include <expected>
#include <filesystem>

namespace Asset {

struct ImportedData {
    std::string name;
    std::filesystem::path source_path;
};

class Importer {
public:
    virtual ~Importer() = default;

    virtual auto import(std::filesystem::path const& path) -> std::expected<std::any, std::string> = 0;
    virtual auto supported_extensions() const -> std::vector<std::string> = 0;
};

}
