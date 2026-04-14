/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <expected>
#include <filesystem>
#include <fstream>
#include <string>

#include <Common/Platform.h>
#include <Common/Types.h>

namespace File {

auto ALWAYS_INLINE read_all(std::filesystem::path const& path) -> std::expected<std::string, std::string>
{
    if (!std::filesystem::exists(path)) {
        return std::unexpected(std::format("File does not exist: {}", path.string()));
    }

    if (!std::filesystem::is_regular_file(path)) {
        return std::unexpected(std::format("Path is not a regular file: {}", path.string()));
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        return std::unexpected(std::format("Failed to open file: {}", path.string()));
    }

    return std::string(std::istreambuf_iterator<char>(file), {});
}

auto ALWAYS_INLINE read_lines(std::filesystem::path const& path) -> std::expected<std::vector<std::string>, std::string>
{
    if (!std::filesystem::exists(path)) {
        return std::unexpected(std::format("File does not exist: {}", path.string()));
    }

    if (!std::filesystem::is_regular_file(path)) {
        return std::unexpected(std::format("Path is not a regular file: {}", path.string()));
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        return std::unexpected(std::format("Failed to open file: {}", path.string()));
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

template<typename T = std::byte>
auto ALWAYS_INLINE read_binary(std::filesystem::path const& path) -> std::expected<std::vector<T>, std::string>
{
    if (!std::filesystem::exists(path)) {
        return std::unexpected(std::format("File does not exist: {}", path.string()));
    }

    if (!std::filesystem::is_regular_file(path)) {
        return std::unexpected(std::format("Path is not a regular file: {}", path.string()));
    }

    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return std::unexpected(std::format("Failed to open file: {}", path.string()));
    }

    auto file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<T> data(file_size / sizeof(T));
    if (!file.read(reinterpret_cast<char*>(data.data()), file_size)) {
        return std::unexpected(std::format("Failed to read file: {}", path.string()));
    }

    return data;
}

}
