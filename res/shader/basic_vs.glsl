#version 330 core
  
layout(location = 0) in vec4 Pos_Tex_In;

out vec2 Tex_Coords;

void main()
{
    Tex_Coords = Pos_Tex_In.zw;
    gl_Position = vec4(Pos_Tex_In.xy, 1.0f, 1.0f);
}