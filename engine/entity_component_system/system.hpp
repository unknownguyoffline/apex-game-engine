#pragma once
#include "entity_component_system/scene.hpp"
#include "renderer/texture_library.hpp"

class SpriteSystem
{
  public:
    void loadTexture(const char *path);
    void loadScene(Scene &scene)
    {
        m_scene = &scene;
    }

  private:
    Scene *m_scene;
    TextureLibrary m_textureLibrary;
};
