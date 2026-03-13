/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Texture.h"
#include <Common/Noncopyable.h>

#include <expected>
#include <memory>
#include <string>

namespace Graphics {

class DX12Texture final : public Texture {
    OA_MAKE_NONCOPYABLE(DX12Texture);
    OA_MAKE_NONMOVABLE(DX12Texture);

public:
    static auto create(Configuration const& config) -> std::expected<std::unique_ptr<DX12Texture>, std::string>;

    ~DX12Texture() override;

    auto config() const -> Configuration const& override;
private:
    DX12Texture() = default;
private:
    Configuration m_config {};
};

}
