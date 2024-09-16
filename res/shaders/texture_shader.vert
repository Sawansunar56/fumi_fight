#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in float texture_index;

out vec4 o_color;
out vec2 o_uv;
out float o_texture_index;

uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * vec4(position, 1.0);
    o_color = color;
    o_uv = uv;
    o_texture_index = texture_index;
}
