#version 330 core

in vec2 texCoords;

uniform sampler2D screenTexture;

void main ()
{
	vec4 FragColor = texture(screenTexture, texCoords);
	 float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
	gl_FragColor = vec4(average, average, average, 1.f);
}