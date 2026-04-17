#pragma once

#include <vector>

#include <Common/Types.h>

namespace Shader {

enum class Format : u8 {
    SPIRV = 0,
    DXIL,
    MetalIR
};

enum class Stage : u8 {
    Vertex = 0,
    Fragment,
};

struct Variant {
    Format format;
    std::vector<u8> bytecode;
};

struct Configuration {
    Stage stage;
    std::vector<Variant> variants;
};

}