#version 450
out vec4 outputColor;
in vec2 uv;
uniform sampler2D tex0;
void main()
{
	outputColor = texture(tex0, uv);
}
