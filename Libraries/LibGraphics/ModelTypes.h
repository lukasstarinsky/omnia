/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <optional>
#include <string>
#include <vector>

#include <LibGraphics/TextureTypes.h>
#include <LibMath/Math.h>

namespace Graphics {

struct Vertex {
    Math::Vec3f position;
    Math::Vec2f tex_coord;
    Math::Vec3f normal;
};

using Index = u32;

struct MaterialConfiguration {
    std::string name;
    std::optional<TextureConfiguration> albedo_texture_configuration = std::nullopt;
    Math::Vec4f base_color { 1.0f, 0.0f, 1.0f, 1.0f };
};

struct SubMeshConfiguration {
    std::vector<Vertex> vertices;
    std::vector<Index> indices;
    u64 material_index;
};

struct ModelConfiguration {
    std::vector<SubMeshConfiguration> sub_meshes;
    std::vector<MaterialConfiguration> materials;
};

}
