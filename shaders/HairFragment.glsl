#version 410 core

layout (location=0) out vec4 fragColor;
in vec3 color;

void main()
{
	fragColor.rgb = color;
}