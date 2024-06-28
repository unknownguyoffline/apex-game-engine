#pragma once
#include "texture.hpp"
#include <string>
#include <unordered_map>

class TextureLibrary
{
  public:
    void loadTexture(const char *path);
    Texture *getTexture(std::string name);

  private:
    std::unordered_map<std::string, Texture *> m_textureList;
};
