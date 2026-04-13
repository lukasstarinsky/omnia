/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <shaderc/shaderc.hpp>

#include <LibAsset/ShaderCompiler.h>

namespace Asset::ShaderCompiler {

static auto shader_stage_to_shaderc(ShaderStage stage) -> shaderc_shader_kind
{
    switch (stage) {
    case ShaderStage::Vertex:
        return shaderc_vertex_shader;
    case ShaderStage::Fragment:
        return shaderc_fragment_shader;
    }
}

auto compile_spirv(std::string_view glsl_source, ShaderStage stage) -> std::expected<std::vector<u8>, std::string>
{
    shaderc::Compiler const compiler;
    shaderc::CompileOptions options;
    options.SetOptimizationLevel(shaderc_optimization_level_performance);

    auto const result = compiler.CompileGlslToSpv(glsl_source.data(), glsl_source.size(), shader_stage_to_shaderc(stage), "Shader", options);
    if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
        return std::unexpected(std::format("Failed to compile SPIR-V: {}", result.GetErrorMessage()));
    }

    return std::vector<u8>(result.cbegin(), result.cend());
}

}
