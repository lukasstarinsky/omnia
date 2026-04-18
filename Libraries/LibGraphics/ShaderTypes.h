#pragma once

#include <vector>

#include <Common/Types.h>

namespace RHI {

enum class ShaderFormat : u8 {
    SPIRV = 0,
    DXIL,
    MetalIR
};

enum class ShaderStage : u8 {
    Vertex = 0,
    Fragment,
};

struct ShaderVariant {
    ShaderFormat format;
    std::vector<u8> bytecode;
};

struct ShaderConfiguration {
    ShaderStage stage;
    std::vector<ShaderVariant> variants;
};

}