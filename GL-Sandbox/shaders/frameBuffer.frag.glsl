#version 330 core

in vec2 texCoords;

uniform sampler2D screenShader;

void main ()
{
	gl_FragColor = texture(screenShader, texCoords);
}