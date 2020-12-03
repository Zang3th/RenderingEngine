#version 330 core
  
in vec2 Tex_Coords;

out vec4 FragColor;

uniform sampler2D image;
uniform vec3 color;

void main()
{
    //FragColor = vec4(color, 1.0f) * texture(image, Tex_Coords);
    FragColor = vec4(vec3(Tex_Coords, 0.3f), 1.0f);
} 