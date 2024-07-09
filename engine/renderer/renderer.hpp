#pragma once
#include "camera.hpp"
#include "command.hpp"
#include "index_buffer.hpp"
#include "mesh.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "texture_library.hpp"
#include "types.hpp"
#include "vertex_buffer.hpp"
#include <glm/glm.hpp>
#include <memory>

struct CircleInfo
{
    Transform transform;
    glm::vec4 color = glm::vec4(0);
};

struct RenderData
{
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;
    std::shared_ptr<Shader> shader;
};

class Renderer2D
{
  public:
    void initialize();
    void startFrame(const glm::vec4 &color, glm::ivec2 size);
    void endFrame();
    void terminate();
    void draw(std::shared_ptr<VertexBuffer> vbo, int count);
    void draw(std::shared_ptr<VertexBuffer> vbo, std::shared_ptr<IndexBuffer> ibo, int count);
    void drawBox(const Transform &transform, const glm::vec4 &color);
    void drawCircle(const Transform &transform, const glm::vec4 &color);
    void drawSprite(const Transform &transform, const Sprite &sprite);
    Camera &getCamera()
    {
        return camera;
    }

    void renderBox();
    void renderCircle();

  private:
    uint32_t boxCount = 0;
    uint32_t circleCount = 0;

    Camera camera;
    RenderCommand *renderCommand = nullptr;

    RenderData boxData;
    RenderData circleData;
    RenderData spriteData;
};
