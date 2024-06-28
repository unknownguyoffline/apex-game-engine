#include "renderer.hpp"
#include "command.hpp"
#include "vertex_buffer.hpp"

RenderCommand *Renderer::renderCommand = nullptr;

void Renderer::init()
{
    renderCommand = RenderCommand::create();
    renderCommand->init();
}
void Renderer::newFrame(const glm::vec4 &color, glm::ivec2 size)
{
    renderCommand->clearScreen(color);
    renderCommand->setViewport(glm::ivec2(0), size);
}
void Renderer::terminate() { delete renderCommand; }
void Renderer::draw(VertexBuffer *vbo, int count)
{
    vbo->select();
    renderCommand->drawArray(count);
}
void Renderer::draw(VertexBuffer *vbo, IndexBuffer *ibo, int count)
{
    vbo->select();
    ibo->select();
    renderCommand->drawIndexed(count);
}
