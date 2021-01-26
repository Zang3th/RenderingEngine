#version 330 core
  
layout(location = 0) in vec3 posIn;
layout(location = 1) in vec2 texCoordsIn;
layout(location = 2) in vec3 colorIn;

out vec2 texCoords;
smooth out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    color = colorIn;
    texCoords = texCoordsIn;
    gl_Position = projection * view * model * vec4(posIn, 1.0f);
}