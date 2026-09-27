#version 330 core

out vec4 color;
in vec3 Normal;
in vec3 FragPos;
flat in float IsRed;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    vec3 N = normalize(Normal);
    vec3 L = normalize(lightPos - FragPos);

    float ambient = 0.2;
    float diffuse = max(dot(N, L), 0.0);

    vec3 baseColor = IsRed > 0.5 ? vec3(1.0, 0.15, 0.15) : vec3(0.7, 0.75, 0.8);
    vec3 result = baseColor * (ambient + diffuse);

    color = vec4(result, 1.0);
}