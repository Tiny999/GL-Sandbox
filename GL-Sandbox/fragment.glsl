#version 330 core

in vec3 oCol;

void main ()
{
	gl_FragColor = vec4(oCol, 1.0f);
}