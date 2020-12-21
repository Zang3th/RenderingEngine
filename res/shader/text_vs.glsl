#version 330 core

layout (location = 0) in vec4 vertex;
layout (location = 1) in float textureIndex;

out vec2 TexCoords;
out float TexIndex;

uniform mat4 projection;

void main()
{
    TexCoords = vec2(vertex.zw);
    TexIndex = textureIndex;
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);    
} 