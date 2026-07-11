#version 330 core

in vec2 fTexCoord;

out vec4 FragColor;

uniform sampler2D TestTexture;

void main()
{
    FragColor = texture(TestTexture, fTexCoord);
}