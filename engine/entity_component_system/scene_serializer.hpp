#pragma once
#include "scene.hpp"

class SceneSerializer
{
  public:
    void save(Scene *scene, const char *path);
    Scene *load(const char *path);
};
