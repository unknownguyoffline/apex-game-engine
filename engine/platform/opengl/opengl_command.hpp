#pragma once
#include "renderer/command.hpp"

class OpenglRenderCommand : public RenderCommand
{
  public:
    void init() override;
    void clearScreen(const glm::vec4 &color) override;
    void drawArray(int count) override;
    void drawIndexed(int count) override;
    void drawInstancedIndex(int count, int instanceCount) override;
    void setViewport(glm::ivec2 pos, glm::ivec2 size) override;
};
