/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <unordered_map>

#include <Common/File.h>
#include <LibAsset/ImportManager.h>
#include <LibAsset/ModelImporter.h>

namespace Asset {

ModelImporter::ModelImporter(Asset::ImportManager const* import_manager)
    : m_import_manager(import_manager)
{
}

auto ModelImporter::import(std::filesystem::path const& path) -> std::expected<std::any, std::string>
{
    if (!std::filesystem::exists(path)) {
        return std::unexpected(std::format("Model file '{}' does not exist", path.string()));
    }

    auto extension = path.extension().string();
    auto supported_extensions = this->supported_extensions();
    if (std::ranges::find(supported_extensions.begin(), supported_extensions.end(), extension) == supported_extensions.end()) {
        return std::unexpected(std::format("Unsupported model file extension '{}'", extension));
    }

    if (extension == ".obj") {
        return import_obj(path);
    }

    return {};
}

auto ModelImporter::supported_extensions() const -> std::vector<std::string>
{
    return { ".obj" };
}

auto ModelImporter::import_obj(std::filesystem::path const& path) const -> std::expected<std::any, std::string>
{
    auto lines = File::read_lines(path);
    if (!lines) {
        return std::unexpected(std::move(lines.error()));
    }

    Graphics::ModelConfiguration model_configuration;

    std::unordered_map<std::string, u32> vertex_cache;
    std::vector<Math::Vec3f> positions;
    std::vector<Math::Vec2f> tex_coords;
    std::vector<Math::Vec3f> normals;

    Graphics::SubMeshConfiguration* current_submesh = nullptr;

    bool current_material_changed = false;
    u64 current_material_index = 0;

    for (auto const& line : lines.value()) {
        std::istringstream line_stream(line);
        std::string token;
        line_stream >> token;

        if (token == "mtllib") {
            std::filesystem::path mtl_path;
            line_stream >> mtl_path;
            mtl_path = path.parent_path() / mtl_path;
            auto materials_result = import_mtl(mtl_path);
            if (!materials_result) {
                return std::unexpected(std::move(materials_result).error());
            }
            model_configuration.materials = std::move(materials_result).value();
        } else if (token == "usemtl") {
            std::string material_name;
            line_stream >> material_name;

            for (std::size_t i = 0; i < model_configuration.materials.size(); ++i) {
                if (model_configuration.materials[i].name == material_name) {
                    current_material_index = i;
                    current_material_changed = true;
                    break;
                }
            }
        } else if (token == "o" || token == "g") {
        } else if (token == "v") {
            auto& position = positions.emplace_back();
            line_stream >> position.x >> position.y >> position.z;
        } else if (token == "vt") {
            auto& tex_coord = tex_coords.emplace_back();
            line_stream >> tex_coord.x >> tex_coord.y;
            tex_coord.y = 1.0F - tex_coord.y;
        } else if (token == "vn") {
            auto& normal = normals.emplace_back();
            line_stream >> normal.x >> normal.y >> normal.z;
        } else if (token == "f") {
            if (current_submesh == nullptr || current_material_changed) {
                model_configuration.sub_meshes.emplace_back();
                current_submesh = &model_configuration.sub_meshes.back();
                current_submesh->material_index = current_material_index;
                current_material_changed = false;
            }

            std::vector<std::string> face_tokens;
            std::string face_token;
            while (line_stream >> face_token) {
                face_tokens.push_back(std::move(face_token));
            }

            for (std::size_t i = 1; i + 1 < face_tokens.size(); ++i) {
                for (std::size_t const j : { 0ULL, i, i + 1 }) {
                    auto& vertex_token = face_tokens[j];

                    if (auto it = vertex_cache.find(vertex_token); it != vertex_cache.end()) {
                        current_submesh->indices.push_back(it->second);
                        continue;
                    }

                    std::istringstream vertex_stream(vertex_token);

                    Graphics::Vertex vertex {};
                    std::string vertex_index;
                    u32 index_count = 0;

                    while (std::getline(vertex_stream, vertex_index, '/')) {
                        if (!vertex_index.empty()) {
                            auto index_value = std::stoul(vertex_index) - 1;

                            if (index_count == 0 && index_value < positions.size()) {
                                vertex.position = positions[index_value];
                            } else if (index_count == 1 && index_value < tex_coords.size()) {
                                vertex.tex_coord = tex_coords[index_value];
                            } else if (index_count == 2 && index_value < normals.size()) {
                                vertex.normal = normals[index_value];
                            }
                        }
                        ++index_count;
                    }

                    auto index = static_cast<Graphics::Index>(current_submesh->vertices.size());
                    current_submesh->vertices.push_back(vertex);
                    current_submesh->indices.push_back(index);
                    vertex_cache[vertex_token] = index;
                }
            }
        }
    }

    return model_configuration;
}

auto ModelImporter::import_mtl(std::filesystem::path const& path) const -> std::expected<std::vector<Graphics::MaterialConfiguration>, std::string>
{
    auto lines = File::read_lines(path);
    if (!lines) {
        return std::unexpected(std::move(lines).error());
    }

    std::vector<Graphics::MaterialConfiguration> material_configurations;
    Graphics::MaterialConfiguration* current_material = nullptr;

    for (auto const& line : lines.value()) {
        std::istringstream line_stream(line);
        std::string token;
        line_stream >> token;

        if (token == "newmtl") {
            material_configurations.emplace_back();
            current_material = &material_configurations.back();
            line_stream >> current_material->name;
        } else if (current_material != nullptr) {
            if (token == "map_Kd") {
                std::filesystem::path texture_path;
                line_stream >> texture_path;

                auto import_result = m_import_manager->import<Graphics::TextureConfiguration>(path.parent_path() / texture_path);
                if (!import_result) {
                    return std::unexpected(std::move(import_result).error());
                }
                current_material->albedo_texture_configuration = std::move(import_result).value();
            }
        }
    }

    return material_configurations;
}

}
