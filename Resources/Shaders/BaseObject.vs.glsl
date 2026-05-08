#version 460 core

#include <Common.glsl>

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_tex_coord;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec4 in_tangent;

layout(location = 0) out vec2 out_tex_coord;
layout(location = 1) out vec3 out_normal;
layout(location = 2) out vec4 out_tangent;
layout(location = 3) out vec3 out_world_pos;

layout(push_constant) uniform PerObjectUniform
{
    mat4 u_model;
};

void main()
{
    out_tex_coord = in_tex_coord;
    out_world_pos = vec3(u_model * vec4(in_position, 1.0));
    gl_Position = u_projection * u_view * vec4(out_world_pos, 1.0);

    mat3 normal_matrix = transpose(inverse(mat3(u_model)));
    out_normal = normal_matrix * in_normal;
    out_tangent = vec4(normal_matrix * in_tangent.xyz, in_tangent.w);
}