#version 440
layout (location = 0) in vec3 verPos;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 proj;

void main()
{
    gl_Position = proj*view*model*vec4(verPos, 1.0);
}