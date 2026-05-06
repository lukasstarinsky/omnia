#version 460 core

layout(location = 0) in vec2 in_tex_coord;
layout(location = 1) in vec3 in_normal;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform sampler u_sampler;

layout(set = 1, binding = 0) uniform texture2D u_texture;
layout(set = 1, binding = 1) uniform Material
{
    vec4 base_color;
} u_material;

void main()
{
    vec4 texture_color = texture(sampler2D(u_texture, u_sampler), in_tex_coord);
    out_color = texture_color * u_material.base_color;
}