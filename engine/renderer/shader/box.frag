#version 450
precision mediump float;
out vec4 fragColor;
in vec4 color;
in vec2 uv;
void main()
{
	fragColor = color;
}