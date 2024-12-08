#version 450
precision mediump float;
out vec4 fragColor;
in vec2 uv;
in vec4 color;
void main()
{
    vec2 center = vec2(0.5, 0.5);
    float dis = distance(uv, center);
    if(dis < 0.5)
        fragColor = color;
    else
        fragColor = vec4(0);

}