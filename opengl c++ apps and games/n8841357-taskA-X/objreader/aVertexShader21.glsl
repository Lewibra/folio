#version 330
layout(location = 0) in vec4 in_position;

void main(void)
{
       gl_Position = ftransform();


}