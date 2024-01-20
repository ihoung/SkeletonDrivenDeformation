#version 410 core

uniform mat4 MVP;

layout (location=0) in vec3 inPos;

void main()
{
	gl_Position = MVP * vec4(inPos, 1);
}