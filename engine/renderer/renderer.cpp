#include "renderer.hpp"
#include "command.hpp"
#include "renderer/camera.hpp"
#include "utility/macro.hpp"
#include "vertex_buffer.hpp"
#include <glm/ext/matrix_transform.hpp>

ShaderSource boxShaderSource = {
    R"(
#version 450
layout(location = 0) in vec3 aPos;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.f);
}
)",
    R"(
#version 450
precision mediump float;
out vec4 fragColor;
uniform vec4 color;
void main()
{
	fragColor = color;
})"};

ShaderSource circleShaderSource = {
    R"(
#version 450
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec2 aUv;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
out vec2 uv;
void main()
{
    uv = aUv;
	gl_Position = proj * view * model * vec4(aPos, 1.f);
}
)",
    R"(
#version 450
precision mediump float;
out vec4 fragColor;
in vec2 uv;
uniform vec4 color;
void main()
{
    vec2 center = vec2(0.5, 0.5);
    float dis = distance(uv, center);
    if(dis < 0.5)
        fragColor = color;
    else
        fragColor = vec4(0);

}
)"};

ShaderSource spriteShaderSource = {
    R"(
#version 450
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec2 aUv;
out vec2 uv;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
void main()
{
    uv = aUv;
	gl_Position = proj * view * model * vec4(aPos, 1.f);
}
)",
    R"(
#version 450
precision mediump float;
out vec4 fragColor;
in vec2 uv;
uniform sampler2D tex0;
void main()
{
    fragColor = texture(tex0, uv);
}
)"};
void sentModelViewProjection(std::shared_ptr<Shader> shader, const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection)
{
    shader->select();
    shader->sentMat4("model", model);
    shader->sentMat4("view", view);
    shader->sentMat4("proj", projection);
}
void setDefaultVertexBufferLayout(std::shared_ptr<VertexBuffer> vertexBuffer)
{
    vertexBuffer->addLayout(FLOAT3);
    vertexBuffer->addLayout(FLOAT2);
    vertexBuffer->addLayout(FLOAT4);
    vertexBuffer->addLayout(FLOAT3);
    vertexBuffer->addLayout(INT);
}

void Renderer::initialize()
{
    m_command.reset(RenderCommand::create());
    m_command->init();

    m_textRenderer.initialize(false);
    m_textRenderer.command = m_command;

    Vertex vertices[4];
    uint32_t indices[] = {0, 1, 2, 2, 3, 0};
    vertices[0] = {glm::vec3(0.5, 0.5, 0.0), glm::vec2(1, 0), glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec3(0), -1};
    vertices[1] = {glm::vec3(0.5, -0.5, 0.0), glm::vec2(1, 1), glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec3(0), -1};
    vertices[2] = {glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0, 1), glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec3(0), -1};
    vertices[3] = {glm::vec3(-0.5, 0.5, 0.0), glm::vec2(0, 0), glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec3(0), -1};

    m_boxData.vertexBuffer.reset(VertexBuffer::create(sizeof(Vertex) * 4, vertices));
    m_circleData.vertexBuffer.reset(VertexBuffer::create(sizeof(Vertex) * 4, vertices));
    m_spriteData.vertexBuffer.reset(VertexBuffer::create(sizeof(Vertex) * 4, vertices));

    m_boxData.indexBuffer.reset(IndexBuffer::create(sizeof(uint32_t) * 6, indices));
    m_circleData.indexBuffer.reset(IndexBuffer::create(sizeof(uint32_t) * 6, indices));
    m_spriteData.indexBuffer.reset(IndexBuffer::create(sizeof(uint32_t) * 6, indices));

    m_boxData.shader.reset(Shader::create(boxShaderSource));
    m_circleData.shader.reset(Shader::create(circleShaderSource));
    m_spriteData.shader.reset(Shader::create(spriteShaderSource));

    setDefaultVertexBufferLayout(m_boxData.vertexBuffer);
    setDefaultVertexBufferLayout(m_circleData.vertexBuffer);
    setDefaultVertexBufferLayout(m_spriteData.vertexBuffer);
}
void Renderer::endFrame()
{
}
void Renderer::terminate()
{
}
void Renderer::draw(std::shared_ptr<VertexBuffer> vbo, int count)
{
    ARG_CHECK(count < 3, );
    ARG_CHECK(vbo.get() == nullptr, );
    m_command->drawArray(count);
}
void Renderer::draw(std::shared_ptr<VertexBuffer> vbo, std::shared_ptr<IndexBuffer> ibo, int count)
{
    ARG_CHECK(count < 3, );
    ARG_CHECK(vbo.get() == nullptr, );
    ARG_CHECK(ibo.get() == nullptr, );

    vbo->select();
    ibo->select();
    m_command->drawIndexed(count);
}

void Renderer::drawBox(const Transform &transform, const glm::vec4 &color)
{
    glm::mat4 model = getTransformMatrix(transform);

    sentModelViewProjection(m_boxData.shader, model, m_camera.getView(), m_camera.getProj());
    m_boxData.shader->sentFloat4("color", color);
    draw(m_boxData.vertexBuffer, m_boxData.indexBuffer, 6);
}

void Renderer::drawCircle(const Transform &transform, const glm::vec4 &color)
{

    glm::mat4 model = getTransformMatrix(transform);
    sentModelViewProjection(m_circleData.shader, model, m_camera.getView(), m_camera.getProj());
    m_circleData.shader->sentFloat4("color", color);
    draw(m_circleData.vertexBuffer, m_circleData.indexBuffer, 6);
}
void Renderer::drawSprite(const Transform &transform, const Sprite &sprite)
{
    glm::vec2 pixelsPerSprite = 1.f / glm::vec2(sprite.count);
    Vertex vertices[4];

    vertices[0] = {glm::vec3(0.5, 0.5, 0.0), glm::vec2(pixelsPerSprite.x * (sprite.index.x + 1), pixelsPerSprite.y * (sprite.index.y + 1)), glm::vec4(1, 0, 1, 1), glm::vec3(0.f), -1};
    vertices[1] = {glm::vec3(0.5, -0.5, 0.0), glm::vec2(pixelsPerSprite.x * (sprite.index.x + 1), pixelsPerSprite.y * (sprite.index.y)), glm::vec4(1, 0, 1, 1), glm::vec3(0.f), -1};
    vertices[2] = {glm::vec3(-0.5, -0.5, 0.0), glm::vec2(pixelsPerSprite.x * (sprite.index.x), pixelsPerSprite.y * (sprite.index.y)), glm::vec4(1, 0, 1, 1), glm::vec3(0.f), -1};
    vertices[3] = {glm::vec3(-0.5, 0.5, 0.0), glm::vec2(pixelsPerSprite.x * (sprite.index.x), pixelsPerSprite.y * (sprite.index.y + 1)), glm::vec4(1, 0, 1, 1), glm::vec3(0.f), -1};

    glm::mat4 model = getTransformMatrix(transform);
    glm::mat4 view = m_camera.getView();
    glm::mat4 proj = m_camera.getProj();

    m_textureLibrary.getTexture(sprite.name)->select(0);

    m_spriteData.vertexBuffer->setData(sizeof(vertices), vertices);

    sentModelViewProjection(m_spriteData.shader, model, m_camera.getView(), m_camera.getProj());
    m_spriteData.shader->sentInt("tex0", 0);

    draw(m_spriteData.vertexBuffer, m_spriteData.indexBuffer, 6);
}

void Renderer::drawText(const Transform &transform, const char *string, const glm::vec4 &color, const char *fontName)
{
    m_textRenderer.getCamera() = m_camera;
    m_textRenderer.getFont() = m_fontLibrary.getFont(fontName);
    m_textRenderer.drawText(transform, string, color);
}
void Renderer::loadTexture(const char *path)
{
    m_textureLibrary.loadTexture(path);
}
void Renderer::loadFont(const char *path)
{
    m_fontLibrary.loadFont(path);
}
void Renderer::startFrame(const glm::vec4 &color, glm::ivec2 size)
{
    m_command->clearScreen(color);
    m_command->clearDepthbuffer();
    m_command->setViewport({0, 0}, size);
}
