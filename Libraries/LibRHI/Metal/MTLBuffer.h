/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Buffer.h"
#include <Common/Noncopyable.h>

#include <expected>
#include <memory>
#include <string>

namespace RHI {

class MTLBuffer final : public Buffer {
    OA_MAKE_NONCOPYABLE(MTLBuffer);
    OA_MAKE_NONMOVABLE(MTLBuffer);

public:
    static auto create(Configuration const& config) -> std::expected<std::unique_ptr<MTLBuffer>, std::string>;

    ~MTLBuffer() override;

    void map() override;
    void unmap() override;
    auto config() const -> Configuration const& override;
private:
    MTLBuffer() = default;
private:
    Configuration m_config;
};

}
