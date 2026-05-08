#version 460 core

#include <Common.glsl>

layout(location = 0) in vec2 in_tex_coord;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec4 in_tangent;
layout(location = 3) in vec3 in_world_pos;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform sampler u_sampler;

layout(set = 1, binding = 0) uniform PerMaterialUniform {
    MaterialParameters u_material_parameters;
};
layout(set = 1, binding = 1) uniform texture2D u_albedo_texture;
layout(set = 1, binding = 2) uniform texture2D u_normal_texture;
layout(set = 1, binding = 3) uniform texture2D u_metallic_roughness_texture;
layout(set = 1, binding = 4) uniform texture2D u_occlusion_texture;
layout(set = 1, binding = 5) uniform texture2D u_emissive_texture;

vec3 calculate_directional_light(DirectionalLight light, vec3 normal)
{
    vec3 light_dir = normalize(-light.direction);
    float diff = max(dot(normal, light_dir), 0.0);
    return light.color * light.intensity * diff;
}

void main()
{
    vec3 T = normalize(in_tangent.xyz);
    vec3 B = normalize(cross(in_normal, T) * in_tangent.w);
    mat3 TBN = mat3(T, B, in_normal);

    vec3 directional_light = calculate_directional_light(u_directional_light, in_normal);

    vec4 texture_color = texture(sampler2D(u_albedo_texture, u_sampler), in_tex_coord);
    vec3 albedo = texture_color.rgb * u_material_parameters.base_color.rgb;
    vec3 ambient = vec3(0.1) * albedo;

    out_color = vec4(albedo * directional_light + ambient, texture_color.a);
}