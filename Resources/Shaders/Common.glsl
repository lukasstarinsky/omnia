struct MaterialParameters
{
    vec4 base_color;
    vec3 emissive_factor;
    float metallic_factor;
    float roughness_factor;
    float normal_scale;
    float occlusion_strength;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 color;
    float intensity;
};

layout(set = 0, binding = 1) uniform PerFrameUniform
{
    mat4 u_projection;
    mat4 u_view;
    DirectionalLight u_directional_light;
};