#version 330 core

in vec2 texCoords;

uniform sampler2D screenTexture;

void main ()
{
	gl_FragColor = vec4(vec3(1.f - texture(screenTexture, texCoords)), 1.f);
}