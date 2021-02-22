#version 330 core
  
layout(location = 0) in vec3 posIn;
layout(location = 1) in vec2 texCoordsIn;
layout(location = 2) in vec3 colorIn;
layout(location = 3) in vec3 normalIn;
layout(location = 4) in float texIndexIn;

flat out vec3 color;
out vec2 texCoords;
flat out float texIndex;
out vec3 fragPos;
flat out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 clippingPlane;

void main()
{
    color = colorIn;
    texCoords = texCoordsIn;
    texIndex = texIndexIn;
    vec4 fragPos_vec4 = model * vec4(posIn, 1.0f);
    fragPos = vec3(fragPos_vec4);
    normal = mat3(transpose(inverse(model))) * normalIn;

    gl_ClipDistance[0] = dot(fragPos_vec4, clippingPlane);    
    gl_Position = projection * view * vec4(fragPos, 1.0f);
}