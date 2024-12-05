#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;  // Textura

void main()
{
    FragColor = texture(texture1, TexCoord);
}
