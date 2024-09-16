#version 330 core
out vec4 frag_color;

in vec4 o_color;
in vec2 o_uv;
in float o_texture_index;

uniform sampler2D u_textures[30];

void main()
{
    frag_color = texture(u_textures[int(o_texture_index)], o_uv) * o_color;
}
