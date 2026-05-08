#define PI 3.14159265359

struct MaterialParameters
{
    vec4 base_color;
    vec4 emissive_factor;
    float metallic_factor;
    float roughness_factor;
    float normal_scale;
    float occlusion_strength;
};

struct DirectionalLight
{
    vec4 direction;
    vec4 color;
};

layout(set = 0, binding = 1) uniform PerFrameUniform
{
    mat4 u_projection;
    mat4 u_view;
    vec4 u_camera_position;
    DirectionalLight u_directional_light;
};