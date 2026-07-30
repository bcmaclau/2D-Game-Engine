#version 330 core

in vec2 fTexCoord;
in float fTexIndex;

out vec4 FragColor;

uniform sampler2DArray texture_array;

void main()
{
    FragColor = texture(texture_array, vec3(fTexCoord, fTexIndex));
}