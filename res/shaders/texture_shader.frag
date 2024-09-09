#version 330 core
out vec4 frag_color;

in vec4 o_color;
in vec2 o_uv;

uniform sampler2D text1;

void main()
{
    frag_color = texture(text1, o_uv) * o_color;
}
