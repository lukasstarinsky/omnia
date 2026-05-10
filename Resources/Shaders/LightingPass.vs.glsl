#version 460 core

layout(location = 0) out vec2 out_tex_coord;

void main()
{
    out_tex_coord = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
    gl_Position = vec4(out_tex_coord * 2.0 - 1.0, 0.0, 1.0);
}