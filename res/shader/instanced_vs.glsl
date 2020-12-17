#version 330 core
  
layout(location = 0) in vec4 vertex;
layout(location = 1) in mat4 model;

out vec2 Tex_Coords;

uniform mat4 projection;

void main()
{
    Tex_Coords = vec2(vertex.zw);
    gl_Position = projection * model * vec4(vertex.xy, 0.0f, 1.0f);
}