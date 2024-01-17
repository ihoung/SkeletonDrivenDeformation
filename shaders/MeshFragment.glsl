#version 410 core

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 baseColor;

layout (location=0) out vec4 fragColor;

in vec3 worldPos;
in vec3 normal;

void main()
{
	float blend = dot(normalize(lightDirection), normal);
	vec3 color = baseColor * lightColor * clamp(blend, 0f, 1f);

    fragColor = vec4(color, 1.0);
}