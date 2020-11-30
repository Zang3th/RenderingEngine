#version 330 core
  
out vec4 vertexColor;

void main()
{
    gl_Position = vec4(1.0);
    vertexColor = vec4(0.5, 0.0, 0.5, 1.0);
}