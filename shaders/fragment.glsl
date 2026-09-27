#version 330 core

out vec4 color;
in vec3 Normal;

void main()
{
    vec3 N = normalize(Normal);

    color = vec4(
        N.z,
        N.z,
        N.z,
        1.0
    );
}