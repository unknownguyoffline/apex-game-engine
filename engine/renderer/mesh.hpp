#pragma once
#include "index_buffer.hpp"
#include "types.hpp"
#include "vertex_buffer.hpp"
#include <memory>
#include <vector>

class Mesh
{
  public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    void update();
    void draw();
    std::shared_ptr<VertexBuffer> getVertexBuffer()
    {
        return m_vertexBuffer;
    }
    std::shared_ptr<IndexBuffer> getIndexBuffer()
    {
        return m_indexBuffer;
    }

  private:
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
};
