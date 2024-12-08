#pragma once
#include "assets/font.hpp"
#include "renderer/camera.hpp"
#include "renderer/command.hpp"
#include "renderer/index_buffer.hpp"
#include "renderer/shader.hpp"
#include "renderer/types.hpp"
#include "renderer/vertex_buffer.hpp"

class TextRenderer
{
  public:
    void drawText(const Transform &transform, const char *string, const glm::vec4 &color);
    void initialize(bool initializeGpuCommand = true);
    Camera &getCamera();
    Font &getFont();
    friend class Renderer;

  private:
    Camera camera;
    Font font;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;
    std::shared_ptr<RenderCommand> command = nullptr;
};
