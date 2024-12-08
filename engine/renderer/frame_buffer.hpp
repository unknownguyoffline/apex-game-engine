#pragma once
#include <glm/glm.hpp>

class FrameBuffer
{
  public:
    virtual void select() = 0;
    virtual void deselect() = 0;
    virtual uint32_t getId() const = 0;
    virtual uint32_t getTextureId() const = 0;
    virtual void resize(const glm::uvec2 &size) = 0;
    virtual void resizeIfNecessary(const glm::uvec2 &size) = 0;
    virtual ~FrameBuffer(){};

    static FrameBuffer *create(const glm::uvec2 &size);
};