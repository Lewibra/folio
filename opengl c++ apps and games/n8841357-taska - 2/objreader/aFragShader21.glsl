#version 330

uniform sampler2D tex;
uniform vec2 tex_size;

layout(location = 0) out vec4 out_colour;

void main()
{
    vec4 in_color = texture(tex, gl_FragCoord.xy / tex_size);
    out_color = //do whatever you want with in_color;
}