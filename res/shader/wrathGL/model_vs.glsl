#version 330 core
  
layout(location = 0) in vec3 posIn;
layout(location = 1) in vec2 texCoordsIn;
layout(location = 2) in vec3 colorIn;
layout(location = 3) in vec3 normalIn;

out vec2 texCoords;
out vec3 color;
out vec3 fragPos;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    color = colorIn;
    texCoords = texCoordsIn;
    fragPos = vec3(model * vec4(posIn, 1.0f));
    normal = mat3(transpose(inverse(model))) * normalIn;

    gl_Position = projection * view * vec4(fragPos, 1.0f);
}