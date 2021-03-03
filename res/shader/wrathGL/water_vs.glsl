#version 330 core
  
layout(location = 0) in vec3 posIn;
layout(location = 1) in vec2 texCoordsIn;
layout(location = 2) in vec3 colorIn;
layout(location = 3) in vec3 normalIn;

out vec4 clipSpace;
out vec2 texCoordsOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    texCoordsOut = texCoordsIn * 6.0; //Tiled water to increase the level of detail
    clipSpace = projection * view * model * vec4(posIn, 1.0f);
    gl_Position = clipSpace;
}