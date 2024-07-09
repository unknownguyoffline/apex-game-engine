#include "renderer.hpp"
#include "command.hpp"
#include "renderer/camera.hpp"
#include "utility/macro.hpp"
#include "vertex_buffer.hpp"
#include <glm/ext/matrix_transform.hpp>

Vertex boxVertices[4];
uint32_t boxIndices[6];
Vertex circleVertices[4];
uint32_t circleIndices[6];
Vertex spriteVertices[4];
uint32_t spriteIndices[6];

void Renderer2D::initialize()
{
    renderCommand = RenderCommand::create();
    renderCommand->init();

    boxData.vertexBuffer.reset(VertexBuffer::create(sizeof(Vertex) * 4 * 1000, nullptr));
    boxData.indexBuffer.reset(IndexBuffer::create(sizeof(uint32_t) * 6 * 1000, nullptr));
    boxData.shader.reset(Shader::create(
        loadShaderSource("../../engine/renderer/shader/box.vert", "../../engine/renderer/shader/box.frag")));

    boxData.vertexBuffer->addLayout(FLOAT4);
    boxData.vertexBuffer->addLayout(FLOAT2);
    boxData.vertexBuffer->addLayout(FLOAT4);
    boxData.vertexBuffer->addLayout(INT);

    circleData.vertexBuffer.reset(VertexBuffer::create(sizeof(Vertex) * 4 * 1000, nullptr));
    circleData.indexBuffer.reset(IndexBuffer::create(sizeof(uint32_t) * 6 * 1000, nullptr));
    circleData.shader.reset(Shader::create(
        loadShaderSource("../../engine/renderer/shader/circle.vert", "../../engine/renderer/shader/circle.frag")));

    circleData.vertexBuffer->addLayout(FLOAT4);
    circleData.vertexBuffer->addLayout(FLOAT2);
    circleData.vertexBuffer->addLayout(FLOAT4);
    circleData.vertexBuffer->addLayout(INT);

    spriteVertices[0] = {glm::vec4(0.5, 0.5, 0.0, 1.0), glm::vec2(1, 0), glm::vec4(1, 0, 1, 1), -1};
    spriteVertices[1] = {glm::vec4(0.5, -0.5, 0.0, 1.0), glm::vec2(1, 1), glm::vec4(1, 0, 1, 1), -1};
    spriteVertices[2] = {glm::vec4(-0.5, -0.5, 0.0, 1.0), glm::vec2(0, 1), glm::vec4(1, 0, 1, 1), -1};
    spriteVertices[3] = {glm::vec4(-0.5, 0.5, 0.0, 1.0), glm::vec2(0, 0), glm::vec4(1, 0, 1, 1), -1};

    spriteIndices[0] = 2;
    spriteIndices[1] = 1;
    spriteIndices[2] = 0;
    spriteIndices[3] = 0;
    spriteIndices[4] = 3;
    spriteIndices[5] = 2;

    spriteData.vertexBuffer.reset(VertexBuffer::create(sizeof(Vertex) * 4 * 1000, spriteVertices));
    spriteData.indexBuffer.reset(IndexBuffer::create(sizeof(uint32_t) * 6 * 1000, spriteIndices));
    spriteData.shader.reset(Shader::create(
        loadShaderSource("../../engine/renderer/shader/sprite.vert", "../../engine/renderer/shader/sprite.frag")));

    spriteData.vertexBuffer->addLayout(FLOAT4);
    spriteData.vertexBuffer->addLayout(FLOAT2);
    spriteData.vertexBuffer->addLayout(FLOAT4);
    spriteData.vertexBuffer->addLayout(INT);
}
void Renderer2D::startFrame(const glm::vec4 &color, glm::ivec2 size)
{

    ARG_CHECK(size.x == 0, );
    ARG_CHECK(size.y == 0, );

    renderCommand->clearScreen(color);
    renderCommand->setViewport(glm::ivec2(0), size);
}
void Renderer2D::endFrame()
{
    renderBox();
    renderCircle();
}
void Renderer2D::terminate()
{
    delete renderCommand;
}
void Renderer2D::draw(std::shared_ptr<VertexBuffer> vbo, int count)
{
    ARG_CHECK(count < 3, );
    ARG_CHECK(vbo.get() == nullptr, );
    renderCommand->drawArray(count);
}
void Renderer2D::draw(std::shared_ptr<VertexBuffer> vbo, std::shared_ptr<IndexBuffer> ibo, int count)
{
    ARG_CHECK(count < 3, );
    ARG_CHECK(vbo.get() == nullptr, );
    ARG_CHECK(ibo.get() == nullptr, );

    vbo->select();
    ibo->select();
    renderCommand->drawIndexed(count);
}

void Renderer2D::drawBox(const Transform &transform, const glm::vec4 &color)
{
    glm::mat4 model = getTransformMatrix(transform);

    boxVertices[0] = {model * glm::vec4(0.5, 0.5, 0.0, 1.0), glm::vec2(1, 0), color, -1};
    boxVertices[1] = {model * glm::vec4(0.5, -0.5, 0.0, 1.0), glm::vec2(1, 1), color, -1};
    boxVertices[2] = {model * glm::vec4(-0.5, -0.5, 0.0, 1.0), glm::vec2(0, 1), color, -1};
    boxVertices[3] = {model * glm::vec4(-0.5, 0.5, 0.0, 1.0), glm::vec2(0, 0), color, -1};

    boxIndices[0] = 2 + (4 * boxCount);
    boxIndices[1] = 1 + (4 * boxCount);
    boxIndices[2] = 0 + (4 * boxCount);
    boxIndices[3] = 0 + (4 * boxCount);
    boxIndices[4] = 3 + (4 * boxCount);
    boxIndices[5] = 2 + (4 * boxCount);

    boxData.vertexBuffer->select();
    boxData.vertexBuffer->subData(sizeof(Vertex) * 4, boxVertices, sizeof(Vertex) * 4 * boxCount);
    boxData.indexBuffer->select();
    boxData.indexBuffer->subData(sizeof(uint32_t) * 6, boxIndices, sizeof(uint32_t) * 6 * boxCount);

    boxCount++;
    if (boxCount > 1000)
        renderBox();
}

void Renderer2D::drawCircle(const Transform &transform, const glm::vec4 &color)
{
    glm::mat4 model = getTransformMatrix(transform);

    circleVertices[0] = {model * glm::vec4(0.5, 0.5, 0.0, 1.0), glm::vec2(1, 0), color, -1};
    circleVertices[1] = {model * glm::vec4(0.5, -0.5, 0.0, 1.0), glm::vec2(1, 1), color, -1};
    circleVertices[2] = {model * glm::vec4(-0.5, -0.5, 0.0, 1.0), glm::vec2(0, 1), color, -1};
    circleVertices[3] = {model * glm::vec4(-0.5, 0.5, 0.0, 1.0), glm::vec2(0, 0), color, -1};

    circleIndices[0] = 2 + (4 * circleCount);
    circleIndices[1] = 1 + (4 * circleCount);
    circleIndices[2] = 0 + (4 * circleCount);
    circleIndices[3] = 0 + (4 * circleCount);
    circleIndices[4] = 3 + (4 * circleCount);
    circleIndices[5] = 2 + (4 * circleCount);

    circleData.vertexBuffer->select();
    circleData.vertexBuffer->subData(sizeof(Vertex) * 4, circleVertices, sizeof(Vertex) * 4 * circleCount);
    circleData.indexBuffer->select();
    circleData.indexBuffer->subData(sizeof(uint32_t) * 6, circleIndices, sizeof(uint32_t) * 6 * circleCount);

    circleCount++;
    if (circleCount > 1000)
        renderCircle();
}
void Renderer2D::drawSprite(const Transform &transform, const Sprite &sprite)
{
    glm::vec2 pixelsPerSprite = 1.f / glm::vec2(sprite.count);

    spriteVertices[0] = {glm::vec4(0.5, 0.5, 0.0, 1.0),
                         glm::vec2(pixelsPerSprite.x * (sprite.index.x + 1), pixelsPerSprite.y * (sprite.index.y)),
                         glm::vec4(1, 0, 1, 1), -1};
    spriteVertices[1] = {glm::vec4(0.5, -0.5, 0.0, 1.0),
                         glm::vec2(pixelsPerSprite.x * (sprite.index.x + 1), pixelsPerSprite.y * (sprite.index.y + 1)),
                         glm::vec4(1, 0, 1, 1), -1};
    spriteVertices[2] = {glm::vec4(-0.5, -0.5, 0.0, 1.0),
                         glm::vec2(pixelsPerSprite.x * (sprite.index.x), pixelsPerSprite.y * (sprite.index.y + 1)),
                         glm::vec4(1, 0, 1, 1), -1};
    spriteVertices[3] = {glm::vec4(-0.5, 0.5, 0.0, 1.0),
                         glm::vec2(pixelsPerSprite.x * (sprite.index.x), pixelsPerSprite.y * (sprite.index.y)),
                         glm::vec4(1, 0, 1, 1), -1};

    glm::mat4 model = getTransformMatrix(transform);
    glm::mat4 view = camera.getView();
    glm::mat4 proj = camera.getProj();

    sprite.texture->select(0);

    spriteData.vertexBuffer->setData(sizeof(Vertex) * 4, spriteVertices);

    spriteData.shader->select();
    spriteData.shader->sentMat4("model", model);
    spriteData.shader->sentMat4("view", view);
    spriteData.shader->sentMat4("proj", proj);
    spriteData.shader->sentInt("tex0", 0);

    draw(spriteData.vertexBuffer, spriteData.indexBuffer, 6);
}
void Renderer2D::renderBox()
{
    if (boxCount == 0)
        return;
    glm::mat4 view = camera.getView();
    glm::mat4 proj = camera.getProj();

    boxData.shader->select();
    boxData.shader->sentMat4("view", view);
    boxData.shader->sentMat4("proj", proj);

    Renderer2D::draw(boxData.vertexBuffer, boxData.indexBuffer, boxCount * 6);
    boxCount = 0;
}

void Renderer2D::renderCircle()
{
    if (circleCount == 0)
        return;

    glm::mat4 view = camera.getView();
    glm::mat4 proj = camera.getProj();

    circleData.shader->select();
    circleData.shader->sentMat4("view", view);
    circleData.shader->sentMat4("proj", proj);

    Renderer2D::draw(circleData.vertexBuffer, circleData.indexBuffer, circleCount * 6);

    circleCount = 0;
}
