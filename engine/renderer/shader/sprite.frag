#version 450
precision mediump float;
out vec4 fragColor;
in vec4 color;
in vec2 uv;
uniform sampler2D tex0;
void main()
{
	fragColor = texture(tex0, uv);
	fragColor = vec4(fragColor.r);
	if(fragColor.r < 0.1)
		discard;
}
