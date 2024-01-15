#version 410 core

layout (location=0) in vec3 inVert;
layout (location=1) in vec3 inNormal;
layout (location=2) in vec2 inUV;

out vec3 worldPos;
out vec3 normal;

layout( std140) uniform TransformUBO
{
  mat4 MVP;
  mat4 normalMatrix;
  mat4 M;
}transforms;

void main()
{
	worldPos = vec3(transforms.M * vec4(inVert, 1.0f));
	normal=normalize(mat3(transforms.normalMatrix)*inNormal);
	gl_Position = transforms.MVP*vec4(inVert,1.0);
}