#version 330 core

in vec2 TexCoords;
in float TexIndex;

out vec4 FragColor;

uniform sampler2D text;
uniform sampler2D textArray[32];
uniform vec3 textColor;

void main()
{    
    int index = int(TexIndex);
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(textArray[index], TexCoords).r);
    FragColor = vec4(textColor, 1.0) * sampled;
}  