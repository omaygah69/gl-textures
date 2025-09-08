#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
out vec3 kulay;
out vec2 textura;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    kulay = aColor;
    textura = aTex;
};
