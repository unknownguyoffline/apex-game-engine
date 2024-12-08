#pragma once
#include "scene/scene.hpp"

class SceneSerializer
{
  public:
    static std::string serialize(Scene &scene);
    static Scene deserialize(const std::string &data);
    static Scene loadScene(const char *path);

    static void saveScene(const char *path, Scene &scene);
};
