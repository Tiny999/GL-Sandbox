#version 330 core

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;

void main()
{
	float ambientStrenght = .1f;
	vec3 ambient = ambientStrenght * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(norm, lightDir), 0.f);
	vec3 diffuse = diff * lightColor;

	vec3 res = (ambient + diffuse) * objectColor;

	gl_FragColor = vec4(res, 1.f);
} 