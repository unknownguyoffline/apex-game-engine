#pragma once
#include "entity_component_system/scene.hpp"

class Editor
{
  public:
    void init(void *nativeWindow);
    void loadScene(Scene &scene)
    {
        m_scene = &scene;
    }
    void update();

  private:
    Entity selectedEntity;
    char name[512];
    bool entityCreationPopup = false;
    bool addComponentPopup = false;
    Scene *m_scene = nullptr;
};
