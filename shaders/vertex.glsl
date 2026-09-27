#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in float isRed;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

out vec3 Normal;
out vec3 FragPos;
flat out float IsRed;

void main()
{
    vec4 worldPos = model * vec4(position, 1.0);
    gl_Position = perspective * view * worldPos;
    FragPos = worldPos.xyz;
    Normal = mat3(model) * normal;
    IsRed = isRed;
}