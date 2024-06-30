#pragma once
#include "component.hpp"
#include "renderer/renderer.hpp"
#include "renderer/texture_library.hpp"
#include "scene.hpp"
class SpriteSystem
{
  public:
    void initialize();
    void loadTexture(const char *path);
    void loadScene(Scene *scene);
    void draw(Shader *shader, glm::vec2 windowSize);

  private:
    VertexBuffer *vbo = nullptr;
    IndexBuffer *ibo = nullptr;
    Scene *m_scene;
    TextureLibrary m_textureLibrary;
};
