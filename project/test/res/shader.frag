#version 300 es
precision mediump float;
out vec4 fragColor;
in vec2 uv;
uniform sampler2D tex0;
void main()
{
	fragColor = texture(tex0, uv);
}
