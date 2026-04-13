/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibAsset/ShaderCompiler.h>
#include <LibAsset/ShaderImporter.h>
#include <LibCore/Utilities.h>

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
    ShaderStage shader_stage {};
    if (shader_stage_string == "vs") {
        shader_stage = ShaderStage::Vertex;
    } else if (shader_stage_string == "fs") {
        shader_stage = ShaderStage::Fragment;
    } else {
        return std::unexpected(std::format("Unsupported shader stage '{}'", shader_stage_string));
    }

    using namespace Core::Utilities;

    ShaderData shader_data;
    shader_data.name = file_name;
    shader_data.source_path = path;
    shader_data.stage = shader_stage;
    shader_data.variants.reserve(3);

    auto file_content = read_file_to_string(path);
    if (!file_content) {
        return std::unexpected(file_content.error());
    }

    // Compile SPIR-V variant
    {
        ShaderVariant spirv_variant;
        spirv_variant.format = ShaderFormat::SPIRV;

        auto compiled_spirv = ShaderCompiler::compile_spirv(file_content.value(), shader_stage);
        if (!compiled_spirv) {
            return std::unexpected(compiled_spirv.error());
        }

        spirv_variant.bytecode = std::move(compiled_spirv.value());
        shader_data.variants.push_back(spirv_variant);
    }

    // Compile DXIL variant
    {
        ShaderVariant dxil_variant;
        dxil_variant.format = ShaderFormat::DXIL;
    }

    // Compile MetalIR variant
    {
        ShaderVariant metal_ir_variant;
        metal_ir_variant.format = ShaderFormat::MetalIR;
    }

    return shader_data;
}

auto ShaderImporter::supported_extensions() const -> std::vector<std::string>
{
    return { ".glsl" };
}

}
