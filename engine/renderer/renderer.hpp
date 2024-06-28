#pragma once
#include "command.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include <glm/glm.hpp>

class Renderer
{
  public:
    static void init();
    static void newFrame(const glm::vec4 &color, glm::ivec2 size);
    static void terminate();
    static void draw(VertexBuffer *vbo, int count);
    static void draw(VertexBuffer *vbo, IndexBuffer *ibo, int count);

  private:
    static RenderCommand *renderCommand;
};
