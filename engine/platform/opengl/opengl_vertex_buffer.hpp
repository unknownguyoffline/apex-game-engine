#pragma once
#include "renderer/vertex_buffer.hpp"
#include <vector>

class OpenglVertexBuffer : public VertexBuffer
{
  public:
    OpenglVertexBuffer(size_t size, void *data);
    void setData(size_t size, void *data) override;
    void subData(size_t size, void *data, size_t offset) override;
    void addLayout(VertexLayoutType type) override;
    void select() override;
    void deselect() override;

  private:
    uint32_t m_id = 0;
    size_t m_stride = 0;
    std::vector<VertexLayoutType> m_layouts;
};
