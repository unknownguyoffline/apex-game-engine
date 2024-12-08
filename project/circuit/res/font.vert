#version 450
layout(location)in vec4 aPos;
layout(location)in vec2 aUv;
out vec2 uv;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
void main()
{
	uv = aUv;
	gl_Position = proj * view * model * vec4(aPos, 0.0, 1.0);
}
