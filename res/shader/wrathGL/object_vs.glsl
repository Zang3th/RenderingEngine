#version 330 core
  
layout(location = 0) in vec4 vertex;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    texCoords = vec2(vertex.zw);
    gl_Position = projection * view * model * vec4(vertex.xy, 0.0f, 1.0f);
}