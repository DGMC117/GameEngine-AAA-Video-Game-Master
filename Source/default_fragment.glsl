#version 440
out vec4 FragColor;

in vec2 uv0;

layout (binding=5) uniform sampler2D mytexture;

void main()
{
    FragColor = texture2D(mytexture, uv0);
}