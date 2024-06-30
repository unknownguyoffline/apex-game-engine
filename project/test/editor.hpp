#pragma once
#include "entity_component_system/scene.hpp"

class Editor
{
  public:
    void initialize(void *nativeWindow);
    void loadScene(Scene *scene)
    {
        m_scene = scene;
    }
    void update();

  private:
    Entity selectedEntity;
    char name[512];
    char path[512];
    bool entityCreationPopup = false;
    bool addComponentPopup = false;
    Scene *m_scene = nullptr;
};
