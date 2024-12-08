#pragma once
#include "camera.hpp"
#include "command.hpp"
#include "index_buffer.hpp"
#include "mesh.hpp"
#include "renderer.hpp"
#include "renderer/font_library.hpp"
#include "shader.hpp"
#include "text_renderer.hpp"
#include "texture.hpp"
#include "texture_library.hpp"
#include "types.hpp"
#include "vertex_buffer.hpp"
#include <glm/glm.hpp>
#include <memory>

struct RenderData
{
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;
    std::shared_ptr<Shader> shader;
};

class Renderer
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
    void drawText(const Transform &transform, const char *string, const glm::vec4 &color, const char *fontName);
    void drawMesh(const MeshRenderer &meshRenderer);

    Camera &getCamera()
    {
        return m_camera;
    }
    Font &getFont()
    {
        return m_textRenderer.getFont();
    }

    void loadTexture(const char *path);
    void loadFont(const char *path);

    bool hasTexture(const char* name) { return m_textureLibrary.has(name); }

  private:
    Camera m_camera;
    TextRenderer m_textRenderer;
    std::shared_ptr<RenderCommand> m_command;

    RenderData m_boxData;
    RenderData m_circleData;
    RenderData m_spriteData;

    TextureLibrary m_textureLibrary;
    FontLibrary m_fontLibrary;
};
