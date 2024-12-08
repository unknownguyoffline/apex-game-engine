#version 450
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec2 aUv;
out vec2 uv;
uniform mat4 model;
uniform mat4 wholeModel;
uniform mat4 view;
uniform mat4 proj;
void main()
{
	uv = aUv;
	gl_Position = proj * view * wholeModel * (model * vec4(aPos, 1.0));
}
