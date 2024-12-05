#version 330 core
layout(location = 0) in vec2 position;    // Posición de los vértices
layout(location = 1) in vec2 texCoord;    // Coordenadas de la textura

out vec2 TexCoord;  // Pasar las coordenadas de la textura al fragment shader

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    TexCoord = texCoord;
}
