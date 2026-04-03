/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "MTLShader.h"

namespace RHI {

auto MTLShader::create(Configuration const& config) -> std::expected<std::unique_ptr<MTLShader>, std::string>
{
    std::unique_ptr<MTLShader> shader(new MTLShader);
    shader->m_config = config;
    return shader;
}

MTLShader::~MTLShader()
{
}

auto MTLShader::config() const -> Configuration const&
{
    return m_config;
}

}
