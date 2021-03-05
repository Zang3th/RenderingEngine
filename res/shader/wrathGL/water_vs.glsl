#version 330 core
  
layout(location = 0) in vec3 posIn;
layout(location = 1) in vec2 texCoordsIn;
layout(location = 2) in vec3 colorIn;
layout(location = 3) in vec3 normalIn;

out vec3 toCameraVector;
out vec3 fragPos;
out vec2 texCoords;
out vec4 clipSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;

void main()
{
    vec4 worldPosition = model * vec4(posIn, 1.0f);
    toCameraVector = cameraPosition - worldPosition.xyz;
    fragPos = vec3(worldPosition);

    texCoords = texCoordsIn * 6.0; //Tiled water to increase the level of detail
    clipSpace = projection * view * worldPosition;

    gl_Position = clipSpace;
}