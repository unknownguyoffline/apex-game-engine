#version 450
layout(location = 0)in vec4 aPos;
layout(location = 1)in vec2 aUv;
layout(location = 2)in vec4 aColor;
uniform mat4 view;
uniform mat4 proj;
out vec2 uv;
out vec4 color;
void main()
{
    uv = aUv;
    color = aColor;
	gl_Position = proj * view * aPos;
}