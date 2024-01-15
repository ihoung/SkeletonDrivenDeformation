#version 410 core

layout (location=0) out vec4 fragColor;

in vec3 worldPos;
in vec3 normal;

void main()
{
	vec3 color = vec3(1.0);

    fragColor = vec4(color, 1.0);
}