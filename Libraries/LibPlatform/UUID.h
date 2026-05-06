/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <format>
#include <optional>
#include <string>
#include <utility>

#include <Common/Types.h>
#include <LibPlatform/Export.h>

namespace Platform {

class PLATFORM_API UUID final {
public:
    constexpr UUID() = default;
    constexpr UUID(u64 n)
    {
        for (std::size_t i = 0; i < 8; ++i) {
            m_data[i] = std::byte((n >> (i * 8)) & 0xFF);
        }
    }

    static auto generate() -> UUID;
    static auto from_string(std::string const& string) -> std::optional<UUID>;

    auto operator==(UUID const& other) const -> bool;
    auto hash() const -> std::size_t;
    auto to_string() const -> std::optional<std::string>;
private:
    mutable std::byte m_data[16] {};

    friend struct std::hash<UUID>;
    friend struct std::formatter<UUID>;
};

}

template<>
struct std::hash<Platform::UUID> {
    auto operator()(Platform::UUID const& uuid) const -> std::size_t
    {
        return uuid.hash();
    }
};

template<>
struct std::formatter<Platform::UUID> : std::formatter<std::string> {
    auto format(Platform::UUID const& uuid, std::format_context& context) const -> std::format_context::iterator
    {
        auto str = uuid.to_string();
        if (!str) {
            str = "Invalid UUID";
        }
        return std::format_to(context.out(), "{}", str.value());
    }
};
