#pragma once
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position = glm::vec3(0);
    glm::vec2 uv = glm::vec2(0);
    glm::vec3 color = glm::vec3(0);
};

struct ModelViewProj
{
    glm::mat4 model = glm::mat4(1);
    glm::mat4 view = glm::mat4(1);
    glm::mat4 proj = glm::mat4(1);
};

struct Transform
{
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);
};
