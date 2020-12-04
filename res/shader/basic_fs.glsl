#version 330 core
  
in vec2 Tex_Coords;

out vec4 FragColor;

uniform sampler2D image;
uniform vec3 color;

void main()
{
    FragColor = vec4(color, 1.0f) * texture(image, Tex_Coords);
} 