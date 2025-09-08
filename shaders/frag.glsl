#version 330 core
out vec4 FragColor;
in vec3 kulay;
in vec2 textura;
uniform sampler2D tex0;

void main()
{
    /* FragColor = vec4(kulay, 1.0f); */
    FragColor = texture(tex0, textura);
};
