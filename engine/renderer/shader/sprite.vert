#version 450
layout(location = 0)in vec4 aPos;
layout(location = 1)in vec2 aUv;
layout(location = 2)in vec4 aColor;
out vec4 color;
out vec2 uv;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
void main()
{
    color = aColor;
    uv = aUv;
	gl_Position = proj * view * model * aPos;
}