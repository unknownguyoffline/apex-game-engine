#pragma once
#include <glm/glm.hpp>

struct Image
{
    unsigned char *data = nullptr;
    glm::ivec2 size = glm::ivec2(0);
};

Image loadImage(const char *path);
