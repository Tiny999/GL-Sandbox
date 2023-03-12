#version 330 core

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	float ambientStrenght = .1f;
	vec3 ambient = ambientStrenght * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(norm, lightDir), 0.f);
	vec3 diffuse = diff * lightColor;

	float specularStrength = .5f;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 res = (ambient + diffuse + specular) * objectColor;

	gl_FragColor = vec4(res, 1.f);
} 