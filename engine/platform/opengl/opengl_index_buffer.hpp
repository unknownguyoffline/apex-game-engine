#pragma once
#include "renderer/index_buffer.hpp"

class OpenglIndexBuffer : public IndexBuffer
{
  public:
    OpenglIndexBuffer(size_t size, void *data);
    void setData(size_t size, void *data) override;
    void subData(size_t size, void *data, size_t offset) override;
    void select() override;
    void deselect() override;

  private:
    uint32_t m_id = 0;
};
