#version 330 core

in vec2 texCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
	gl_FragColor = texture(texture_diffuse1, texCoords);
}