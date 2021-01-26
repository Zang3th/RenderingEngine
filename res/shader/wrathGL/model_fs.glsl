#version 330 core 

in vec2 texCoords;
smooth in vec3 color;

out vec4 fragColor;

uniform sampler2D image;

void main()
{
    fragColor = vec4(color, 1.0f) * texture(image, texCoords);
} 