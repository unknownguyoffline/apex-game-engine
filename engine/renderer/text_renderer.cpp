#include "text_renderer.hpp"
#include "types.hpp"
#include <string.h>

ShaderSource textShaderSource = {R"(
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
)",
                                 R"(
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
)"};

void TextRenderer::initialize(bool initializeGpuCommand)
{
    float vertices[] = {
        0.5, 0.5, 0.0, 1, 0, 0.5, -0.5, 0.0, 1, 1, -0.5, -0.5, 0.0, 0, 1, -0.5, 0.5, 0.0, 0, 0,
    };

    uint32_t indices[] = {0, 1, 2, 2, 3, 0};
    if (initializeGpuCommand)
    {
        command.reset(RenderCommand::create());
    }
    shader.reset(Shader::create(textShaderSource));
    vertexBuffer.reset(VertexBuffer::create(sizeof(vertices), vertices));
    vertexBuffer->addLayout(FLOAT3);
    vertexBuffer->addLayout(FLOAT2);
    indexBuffer.reset(IndexBuffer::create(sizeof(indices), indices));
}
void TextRenderer::drawText(const Transform &t, const char *string, const glm::vec4 &color)
{
    size_t size = strlen(string);
    std::vector<Transform> transforms;
    std::vector<std::shared_ptr<Texture>> textures;

    uint32_t advance = 0;
    for (size_t i = 0; i < size; i++)
    {
        Glyph glyph = font.glyphs[string[i]];
        Transform transform;
        std::shared_ptr<Texture> texture;

        texture = glyph.texture;
        transform.scale = glm::vec3(glyph.size, 1.f);
        transform.position = glm::vec3(glyph.bearing.x + (glyph.size.x / 2) + (advance >> 6), glyph.bearing.y - (glyph.size.y / 2.f), 0.f);

        transforms.push_back(transform);
        textures.push_back(texture);
        advance += glyph.advance;
    }
    for (size_t i = 0; i < transforms.size(); i++)
    {
        Transform transform = transforms[i];
        std::shared_ptr<Texture> texture = textures[i];

        glm::mat4 model = getTransformMatrix(transform);
        texture->select(0);
        shader->select();
        shader->sentMat4("model", model);
        shader->sentMat4("wholeModel", getTransformMatrix(t));
        shader->sentMat4("view", camera.getView());
        shader->sentMat4("proj", camera.getProj());
        shader->sentFloat4("color", color);

        vertexBuffer->select();
        indexBuffer->select();

        command->drawIndexed(6);
    }
}
Camera &TextRenderer::getCamera()
{
    return camera;
}
Font &TextRenderer::getFont()
{
    return font;
}
