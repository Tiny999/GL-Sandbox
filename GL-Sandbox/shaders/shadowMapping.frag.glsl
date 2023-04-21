#version 330 core

in VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
} fsIn;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir) {
	
	// perform perspective-divide
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	projCoords = projCoords * 0.5f + 0.5f;
	
	float closestDepth = texture(shadowMap, projCoords.xy).r;

	float currentDepth = projCoords.z;

	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); 

	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

	if(projCoords.z > 1.0f)
		shadow = 0.0f;

	return shadow;
}

void main(){
	vec3 color = texture(diffuseTexture, fsIn.TexCoords).rgb;
	vec3 normal = normalize(fsIn.Normal);
	vec3 lightColor = vec3(.4f);

	// ambient
	vec3 ambient = 0.3f * lightColor;

	// diffusec
	vec3 lightDir = normalize(lightPos - fsIn.FragPos);
	float diff = max(dot(lightDir, normal), 0.f);
	vec3 diffuse = diff * lightColor;

	// specular 
	vec3 viewDir = normalize(viewPos - fsIn.FragPos);
	float spec = 0.f;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.f),64.f);
	vec3 specular = spec * lightColor;

	float shadow = ShadowCalculation(fsIn.FragPosLightSpace, normal, lightDir);

    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    

	gl_FragColor = vec4(lighting, 1.f);
}