/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <vector>

#include <Common/Types.h>

namespace Graphics {

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
