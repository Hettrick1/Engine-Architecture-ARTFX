#version 450 core

out vec4 FragColor;

uniform samplerCube uTexture;

void main()
{
   FragColor = vec4(0.588, 0.294, 0.0, 1.0);
}
