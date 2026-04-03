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

class DX12Buffer final : public Buffer {
    OA_MAKE_NONCOPYABLE(DX12Buffer);
    OA_MAKE_NONMOVABLE(DX12Buffer);

public:
    static auto create(Configuration const& config) -> std::expected<std::unique_ptr<DX12Buffer>, std::string>;

    ~DX12Buffer() override;

    void map() override;
    void unmap() override;
    auto config() const -> Configuration const& override;
private:
    DX12Buffer() = default;
private:
    Configuration m_config;
};

}
