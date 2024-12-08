#version 450
precision mediump float;
out vec4 outputColor;
in vec2 uv;
uniform sampler2D tex0;
uniform vec4 color;
void main()
{
	outputColor = vec4(texture(tex0, uv).r);
	if(outputColor.r < 0.01)
		discard;
	outputColor *= color;
}
