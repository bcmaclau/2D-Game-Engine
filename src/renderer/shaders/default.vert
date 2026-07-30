#version 330 core

layout (location = 0) in vec2 inNormCoord;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in float inTexIndex;

out vec2 fTexCoord;
out float fTexIndex;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(inNormCoord, 0.0, 1.0);
    fTexCoord = inTexCoord;
    fTexIndex = inTexIndex;
}