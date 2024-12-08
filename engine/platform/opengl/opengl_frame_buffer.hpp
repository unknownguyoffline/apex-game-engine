#pragma once
#include "renderer/frame_buffer.hpp"
#include <stdint.h>

class OpenglFrameBuffer : public FrameBuffer
{
  public:
    OpenglFrameBuffer(const glm::uvec2 &size);
    ~OpenglFrameBuffer();
    void select() override;
    void deselect() override;
    void resize(const glm::uvec2 &size) override;
    void resizeIfNecessary(const glm::uvec2 &size) override;
    uint32_t getId() const override;
    uint32_t getTextureId() const override;

  private:
    glm::uvec2 m_size = glm::vec2(0);
    uint32_t m_id = 0;
    uint32_t m_textureId = 0;
    uint32_t m_renderBufferId = 0;
};