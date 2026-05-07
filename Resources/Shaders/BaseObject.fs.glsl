#version 460 core

layout(location = 0) in vec2 in_tex_coord;
layout(location = 1) in vec3 in_normal;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform sampler u_sampler;

layout(set = 1, binding = 0) uniform Material
{
    vec4 base_color;
    vec3 emissive_factor;
    float metallic_factor;
    float roughness_factor;
    float normal_scale;
    float occlusion_strength;
} u_material_parameters;

layout(set = 1, binding = 1) uniform texture2D u_albedo_texture;
layout(set = 1, binding = 2) uniform texture2D u_normal_texture;
layout(set = 1, binding = 3) uniform texture2D u_metallic_roughness_texture;
layout(set = 1, binding = 4) uniform texture2D u_occlusion_texture;
layout(set = 1, binding = 5) uniform texture2D u_emissive_texture;

void main()
{
    vec4 texture_color = texture(sampler2D(u_albedo_texture, u_sampler), in_tex_coord);
    out_color = texture_color * u_material_parameters.base_color;
}