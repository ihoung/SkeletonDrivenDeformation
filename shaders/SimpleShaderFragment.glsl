#version 410 core

layout (location=0) out vec4 fragColor;

uniform vec3 baseColor;

void main()
{
	fragColor.rgb = baseColor;
}