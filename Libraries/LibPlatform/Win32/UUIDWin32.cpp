/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <rpc.h>

#include <LibPlatform/UUID.h>

namespace Platform {

auto UUID::generate() -> UUID
{
    Platform::UUID platform_uuid;
    ::UUID uuid;
    ::UuidCreate(&uuid);
    std::memcpy(platform_uuid.m_data, &uuid, sizeof(uuid));
    return platform_uuid;
}

auto UUID::from_string(std::string const& string) -> std::optional<UUID>
{
    Platform::UUID uuid;
    auto result = UuidFromString(reinterpret_cast<RPC_CSTR>(const_cast<char*>(string.c_str())), reinterpret_cast<::UUID*>(uuid.m_data));
    if (result != RPC_S_OK) {
        return std::nullopt;
    }
    return uuid;
}

auto UUID::operator==(Platform::UUID const& other) const -> bool
{
    return std::memcmp(m_data, other.m_data, sizeof(m_data)) == 0;
}

auto UUID::hash() const -> std::size_t
{
    RPC_STATUS status;
    auto hash = UuidHash(reinterpret_cast<::UUID*>(m_data), &status);
    if (status != RPC_S_OK) {
        return 0;
    }
    return hash;
}

auto UUID::to_string() const -> std::optional<std::string>
{
    RPC_CSTR string;
    auto result = UuidToString(reinterpret_cast<::UUID*>(m_data), &string);
    if (result != RPC_S_OK) {
        return std::nullopt;
    }
    std::string str(reinterpret_cast<char*>(string));
    RpcStringFree(&string);
    return str;
}

}
