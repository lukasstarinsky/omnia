/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <expected>
#include <string>
#include <vector>

#include <Common/Types.h>
#include <LibAsset/ShaderImporter.h>

namespace Asset::ShaderCompiler {

auto compile_spirv(std::string_view glsl_source, Shader::Stage stage) -> std::expected<std::vector<u8>, std::string>;

}