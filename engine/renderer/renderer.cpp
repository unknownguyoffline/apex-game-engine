#include "renderer.hpp"
#include "command.hpp"
#include "renderer/camera.hpp"
#include "utility/macro.hpp"
#include "vertex_buffer.hpp"
#include <glm/ext/matrix_transform.hpp>

RenderCommand *Renderer::renderCommand = nullptr;
Camera Renderer::camera;
uint32_t Renderer::boxCount = 0;
uint32_t Renderer::circleCount = 0;
RenderResource Renderer::boxRenderResource;
RenderResource Renderer::circleRenderResource;

const char *circleVertexShaderCode = R"(#version 450
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
)";
const char *circleFragmentShaderCode = R"(#version 450
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

})";

const char *batchVertexCode = R"(#version 450
layout(location = 0)in vec4 aPos;
layout(location = 1)in vec2 aUv;
layout(location = 2)in vec4 aColor;
out vec4 color;
out vec2 uv;
uniform mat4 view;
uniform mat4 proj;
void main()
{
    color = aColor;
    uv = aUv;
	gl_Position = proj * view * aPos;
}
)";
const char *batchFragmentCode = R"(#version 450
precision mediump float;
out vec4 fragColor;
in vec4 color;
in vec2 uv;
void main()
{
	fragColor = color;
})";
Vertex2 batchVertices[4];
uint32_t batchIndices[6];

void Renderer::initialize()
{
    renderCommand = RenderCommand::create();
    renderCommand->init();

    boxRenderResource.vertexBuffer.reset(VertexBuffer::create(sizeof(Vertex2) * 4 * 1000, nullptr));
    boxRenderResource.indexBuffer.reset(IndexBuffer::create(sizeof(uint32_t) * 6 * 1000, nullptr));
    boxRenderResource.shader.reset(Shader::create({batchVertexCode, batchFragmentCode}));

    boxRenderResource.vertexBuffer->addLayout(FLOAT4);
    boxRenderResource.vertexBuffer->addLayout(FLOAT2);
    boxRenderResource.vertexBuffer->addLayout(FLOAT4);

    circleRenderResource.vertexBuffer.reset(VertexBuffer::create(sizeof(Vertex2) * 4 * 1000, nullptr));
    circleRenderResource.indexBuffer.reset(IndexBuffer::create(sizeof(uint32_t) * 6 * 1000, nullptr));
    circleRenderResource.shader.reset(Shader::create({circleVertexShaderCode, circleFragmentShaderCode}));

    circleRenderResource.vertexBuffer->addLayout(FLOAT4);
    circleRenderResource.vertexBuffer->addLayout(FLOAT2);
    circleRenderResource.vertexBuffer->addLayout(FLOAT4);
}
void Renderer::newFrame(const glm::vec4 &color, glm::ivec2 size)
{

    ARG_CHECK(size.x == 0, );
    ARG_CHECK(size.y == 0, );

    renderCommand->clearScreen(color);
    renderCommand->setViewport(glm::ivec2(0), size);
}
void Renderer::terminate()
{
    delete renderCommand;
}
void Renderer::draw(std::shared_ptr<VertexBuffer> vbo, int count)
{
    ARG_CHECK(count < 3, );
    ARG_CHECK(vbo.get() == nullptr, );
    renderCommand->drawArray(count);
}
void Renderer::draw(std::shared_ptr<VertexBuffer> vbo, std::shared_ptr<IndexBuffer> ibo, int count)
{
    ARG_CHECK(count < 3, );
    ARG_CHECK(vbo.get() == nullptr, );
    ARG_CHECK(ibo.get() == nullptr, );

    vbo->select();
    ibo->select();
    renderCommand->drawIndexed(count);
}

// void Renderer::drawBox(const Transform &transform, const glm::vec4 &color)
// {
//     if (color.a == 0.f)
//     {
//         WARN("Renderer::drawBox color.a = 0");
//     }
//     glm::mat4 model = glm::mat4(1.f);
//     model = glm::translate(model, transform.position);
//     model = glm::rotate(model, transform.rotation.x, glm::vec3(1, 0, 0));
//     model = glm::rotate(model, transform.rotation.y, glm::vec3(0, 1, 0));
//     model = glm::rotate(model, transform.rotation.z, glm::vec3(0, 0, 1));
//     model = glm::scale(model, transform.scale);

//     boxShader->select();
//     boxShader->sentMat4("model", model);
//     boxShader->sentMat4("view", camera.getView());
//     boxShader->sentMat4("proj", camera.getProj());
//     boxShader->sentFloat4("color", color);

//     mesh.draw();
// }

void Renderer::drawBox(const Transform &transform, const glm::vec4 &color)
{
    glm::mat4 model = glm::mat4(1.0);

    model = glm::translate(model, transform.position);
    model = glm::rotate(model, transform.rotation.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, transform.rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, transform.rotation.z, glm::vec3(0, 0, 1));
    model = glm::scale(model, transform.scale);

    batchVertices[0] = {model * glm::vec4(0.5, 0.5, 0.0, 1.0), glm::vec2(1, 0), color};
    batchVertices[1] = {model * glm::vec4(0.5, -0.5, 0.0, 1.0), glm::vec2(1, 1), color};
    batchVertices[2] = {model * glm::vec4(-0.5, -0.5, 0.0, 1.0), glm::vec2(0, 1), color};
    batchVertices[3] = {model * glm::vec4(-0.5, 0.5, 0.0, 1.0), glm::vec2(0, 0), color};

    batchIndices[0] = 2 + (4 * boxCount);
    batchIndices[1] = 1 + (4 * boxCount);
    batchIndices[2] = 0 + (4 * boxCount);
    batchIndices[3] = 0 + (4 * boxCount);
    batchIndices[4] = 3 + (4 * boxCount);
    batchIndices[5] = 2 + (4 * boxCount);

    boxRenderResource.vertexBuffer->subData(sizeof(Vertex2) * 4, batchVertices, sizeof(Vertex2) * 4 * boxCount);
    boxRenderResource.indexBuffer->subData(sizeof(uint32_t) * 6, batchIndices, sizeof(uint32_t) * 6 * boxCount);

    if (boxCount > 1000)
        renderBox();
    boxCount++;
}

void Renderer::drawCircle(const Transform &transform, const glm::vec4 &color)
{
    glm::mat4 model = glm::mat4(1.0);

    model = glm::translate(model, transform.position);
    model = glm::rotate(model, transform.rotation.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, transform.rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, transform.rotation.z, glm::vec3(0, 0, 1));
    model = glm::scale(model, transform.scale);

    batchVertices[0] = {model * glm::vec4(0.5, 0.5, 0.0, 1.0), glm::vec2(1, 0), color};
    batchVertices[1] = {model * glm::vec4(0.5, -0.5, 0.0, 1.0), glm::vec2(1, 1), color};
    batchVertices[2] = {model * glm::vec4(-0.5, -0.5, 0.0, 1.0), glm::vec2(0, 1), color};
    batchVertices[3] = {model * glm::vec4(-0.5, 0.5, 0.0, 1.0), glm::vec2(0, 0), color};

    batchIndices[0] = 2 + (4 * circleCount);
    batchIndices[1] = 1 + (4 * circleCount);
    batchIndices[2] = 0 + (4 * circleCount);
    batchIndices[3] = 0 + (4 * circleCount);
    batchIndices[4] = 3 + (4 * circleCount);
    batchIndices[5] = 2 + (4 * circleCount);

    circleRenderResource.vertexBuffer->subData(sizeof(Vertex2) * 4, batchVertices, sizeof(Vertex2) * 4 * circleCount);
    circleRenderResource.indexBuffer->subData(sizeof(uint32_t) * 6, batchIndices, sizeof(uint32_t) * 6 * circleCount);

    if (circleCount > 1000)
        renderCircle();
    circleCount++;
}
void Renderer::renderBox()
{
    glm::mat4 view = camera.getView();
    glm::mat4 proj = camera.getProj();

    boxRenderResource.vertexBuffer->select();
    boxRenderResource.indexBuffer->select();
    boxRenderResource.shader->select();
    boxRenderResource.shader->sentMat4("view", view);
    boxRenderResource.shader->sentMat4("proj", proj);

    renderCommand->drawIndexed(boxCount * 6);

    boxCount = 0;
}

void Renderer::renderCircle()
{

    glm::mat4 view = camera.getView();
    glm::mat4 proj = camera.getProj();

    circleRenderResource.vertexBuffer->select();
    circleRenderResource.indexBuffer->select();
    circleRenderResource.shader->select();
    circleRenderResource.shader->sentMat4("view", view);
    circleRenderResource.shader->sentMat4("proj", proj);

    renderCommand->drawIndexed(circleCount * 6);

    circleCount = 0;
}
