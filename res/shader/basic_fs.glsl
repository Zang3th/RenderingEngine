#version 330 core

out vec4 FragColor;
  
in vec2 Tex_Coords;

uniform sampler2D tex;
uniform vec3 color;

void main()
{
    FragColor = vec4(color, 1.0f);
} 