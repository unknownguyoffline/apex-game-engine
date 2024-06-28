#pragma once
#include <glm/glm.hpp>

class RenderCommand
{
  public:
    virtual void init() = 0;
    virtual void clearScreen(const glm::vec4 &color) = 0;
    virtual void drawArray(int count) = 0;
    virtual void drawIndexed(int count) = 0;
    virtual void setViewport(glm::ivec2 pos, glm::ivec2 size) = 0;
    virtual ~RenderCommand() {}

    static RenderCommand *create();
};
