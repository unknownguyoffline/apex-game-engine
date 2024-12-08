#pragma once
#include "assets/font.hpp"
#include <string>
#include <unordered_map>

class FontLibrary
{
  public:
    void loadFont(const char *path);
    void unloadFont(const char *path);

    Font getFont(const char *name);

  private:
    std::unordered_map<std::string, Font> m_fontMap;
};