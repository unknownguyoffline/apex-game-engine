#pragma once
#include <glm/glm.hpp>

struct MouseProperties
{
    bool leftPressed = false;
    bool rightPressed = false;
    bool middlePressed = false;
    bool leftClicked = false;
    bool rightClicked = false;
    bool middleClicked = false;
    glm::dvec2 scrollOffset = glm::dvec2(0);
};