/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Shader.h"
#include <Common/Noncopyable.h>

#include <expected>
#include <memory>
#include <string>

namespace Graphics {

class MTLShader final : public Shader {
    OA_MAKE_NONCOPYABLE(MTLShader);
    OA_MAKE_NONMOVABLE(MTLShader);

public:
    static auto create(Configuration const& config) -> std::expected<std::unique_ptr<MTLShader>, std::string>;

    ~MTLShader() override;

    auto config() const -> Configuration const& override;
private:
    MTLShader() = default;
private:
    Configuration m_config;
};

}
