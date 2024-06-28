#pragma once
#include "renderer/shader.hpp"
#include "renderer/texture.hpp"
#include "renderer/types.hpp"
#include <glm/glm.hpp>
#include <vector>

struct EntityInfo
{
    std::string name;
    bool selected = false;
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

struct MeshRenderer
{
    Shader *shader = nullptr;
};

struct Transform
{
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(0);
};

struct Sprite
{
    glm::ivec2 spriteCount = glm::ivec2(1);
    glm::ivec2 selectedSprite = glm::ivec2(1);
    Texture *texture = nullptr;
};
