#pragma once
#include "renderer/texture.hpp"
#include <glm/glm.hpp>
#include <memory>

struct Vertex
{
    glm::vec4 position = glm::vec4(0);
    glm::vec2 uv = glm::vec2(0);
    glm::vec4 color = glm::vec4(0);
    int textureSlot = -1;
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

glm::mat4 getTransformMatrix(const Transform &transform);

struct Sprite
{

    std::shared_ptr<Texture> texture;
    glm::ivec2 count = glm::ivec2(1);
    glm::ivec2 index = glm::ivec2(0);
};