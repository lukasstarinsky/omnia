#version 460 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_tex_coords;

layout(location = 0) out vec2 out_tex_coords;

layout(set = 0, binding = 2) uniform PerFrameData
{
    mat4 projection;
    mat4 view;
} u_per_frame_data;

void main()
{
    gl_Position = u_per_frame_data.projection * u_per_frame_data.view * vec4(in_position, 1.0);
    out_tex_coords = in_tex_coords;
}