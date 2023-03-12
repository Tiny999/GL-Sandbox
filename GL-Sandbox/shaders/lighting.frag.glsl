#version 330 core

in vec2 texCoord;

//uniform sampler2D containerTex;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	gl_FragColor = vec4(objectColor * lightColor, 1.f);
} 