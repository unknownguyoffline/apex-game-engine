#pragma once
#include "assets/image.hpp"
#include <glm/glm.hpp>

class Texture
{
  public:
    virtual void select(int slot) = 0;
    virtual void deselect() = 0;
    virtual ~Texture()
    {
    }
    static Texture *create(const Image &image);
};
