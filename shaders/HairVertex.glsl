#version 410 core

uniform mat4 MVP;

layout (location=0) in vec3 inPos;
out vec3 color;

void main()
{
	color = vec3(0);
	gl_Position = MVP * vec4(inPos, 1);
}