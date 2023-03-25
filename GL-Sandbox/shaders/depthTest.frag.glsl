#version 330 core

in vec2 texCoords;

uniform sampler2D texture1;

void main()
{
	vec4 texColor = texture(texture1, texCoords);
	if(texColor.a < 0.1f)
		discard;

	gl_FragColor = texColor;
}