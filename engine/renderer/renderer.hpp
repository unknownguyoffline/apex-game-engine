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

struct Vertex2
{
    glm::vec4 position;
    glm::vec2 uv;
    glm::vec4 color;
};

struct RenderResource
{
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;
    std::shared_ptr<Shader> shader;
};

class Renderer
{
  public:
    static void initialize();
    static void startFrame(const glm::vec4 &color, glm::ivec2 size);
    static void endFrame();
    static void terminate();
    static void draw(std::shared_ptr<VertexBuffer> vbo, int count);
    static void draw(std::shared_ptr<VertexBuffer> vbo, std::shared_ptr<IndexBuffer> ibo, int count);
    static void drawBox(const Transform &transform, const glm::vec4 &color);
    static void drawCircle(const Transform &transform, const glm::vec4 &color);
    static Camera &getCamera()
    {
        return camera;
    }

    static void renderBox();
    static void renderCircle();

  private:
    static uint32_t boxCount;
    static uint32_t circleCount;

    static Camera camera;
    static RenderCommand *renderCommand;

    static RenderResource boxRenderResource;
    static RenderResource circleRenderResource;
};
