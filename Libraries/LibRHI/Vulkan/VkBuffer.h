/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <expected>
#include <memory>
#include <string>

#include <Common/Noncopyable.h>
#include <LibRHI/Buffer.h>

namespace RHI {

class VkBuffer final : public Buffer {
    OA_MAKE_NONCOPYABLE(VkBuffer);
    OA_MAKE_NONMOVABLE(VkBuffer);

public:
    static auto create(Configuration const& config) -> std::expected<std::unique_ptr<VkBuffer>, std::string>;

    ~VkBuffer() override;

    void map() override;
    void unmap() override;
    auto config() const -> Configuration const& override;
private:
    VkBuffer() = default;
private:
    Configuration m_config;
};

}
