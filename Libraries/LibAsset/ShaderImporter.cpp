/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Common/File.h>
#include <LibAsset/ShaderCompiler.h>
#include <LibAsset/ShaderImporter.h>

namespace Asset {

auto ShaderImporter::import(std::filesystem::path const& path) -> std::expected<std::any, std::string>
{
    if (!std::filesystem::exists(path)) {
        return std::unexpected(std::format("Shader file '{}' does not exist", path.string()));
    }

    auto extension = path.extension().string();
    auto supported_extensions = this->supported_extensions();
    if (std::ranges::find(supported_extensions.begin(), supported_extensions.end(), extension) == supported_extensions.end()) {
        return std::unexpected(std::format("Unsupported shader file extension '{}'", extension));
    }

    auto file_name = path.stem().string();
    auto shader_stage_string = std::string_view(file_name).substr(file_name.find_last_of('.') + 1);
    RHI::ShaderStage shader_stage {};
    if (shader_stage_string == "vs") {
        shader_stage = RHI::ShaderStage::Vertex;
    } else if (shader_stage_string == "fs") {
        shader_stage = RHI::ShaderStage::Fragment;
    } else {
        return std::unexpected(std::format("Unsupported shader stage '{}'", shader_stage_string));
    }

    RHI::ShaderConfiguration shader_config;
    shader_config.stage = shader_stage;
    shader_config.variants.reserve(3);

    auto file_content = File::read_all(path);
    if (!file_content) {
        return std::unexpected(file_content.error());
    }

    // Compile SPIR-V variant
    {
        RHI::ShaderVariant spirv_variant;
        spirv_variant.format = RHI::ShaderFormat::SPIRV;

        auto compiled_spirv = ShaderCompiler::compile_spirv(file_content.value(), shader_stage);
        if (!compiled_spirv) {
            return std::unexpected(compiled_spirv.error());
        }

        spirv_variant.bytecode = std::move(compiled_spirv.value());
        shader_config.variants.push_back(spirv_variant);
    }

    // Compile DXIL variant
    {
        RHI::ShaderVariant dxil_variant;
        dxil_variant.format = RHI::ShaderFormat::DXIL;
    }

    // Compile MetalIR variant
    {
        RHI::ShaderVariant metal_ir_variant;
        metal_ir_variant.format = RHI::ShaderFormat::MetalIR;
    }

    return shader_config;
}

auto ShaderImporter::supported_extensions() const -> std::vector<std::string>
{
    return { ".glsl" };
}

}
