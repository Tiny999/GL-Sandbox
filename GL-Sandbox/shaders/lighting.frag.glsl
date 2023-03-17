#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light 
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 normal;
in vec3 fragPos;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	float ambientStrenght = .1f;
	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);


	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 res = ambient + diffuse + specular;

	gl_FragColor = vec4(res, 1.f);
} 