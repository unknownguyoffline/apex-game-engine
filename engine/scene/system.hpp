#pragma once
#include "renderer/renderer.hpp"
#include "scene.hpp"

class ComponentSystem
{
  public:
    void selectScene(Scene &scene);
    void initialize();
    void update();
    void drawBoxes();
    void drawSprite();
    void drawCircles();
    void updateScripts();

  private:
    std::shared_ptr<Texture> defaultTexture;
    Renderer *renderer = nullptr;
    Scene *m_scene = nullptr;
};