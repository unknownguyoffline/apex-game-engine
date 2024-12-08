#pragma once
#include <glm/glm.hpp>

struct CursorProperties
{
    glm::dvec2 position = glm::dvec2(0);
    glm::dvec2 deltaPosition = glm::dvec2(0);
    bool hidden = false;
};
