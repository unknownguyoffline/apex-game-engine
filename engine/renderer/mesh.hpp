#pragma once
#include "shader.hpp"
#include "texture.hpp"
#include "types.hpp"
#include <memory>
#include <vector>

enum MeshType
{
    STATIC,
    DYNAMIC
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

struct Material
{
    bool useColor = false;
    glm::vec4 color = glm::vec4(1.f);
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> albedo;
    std::shared_ptr<Texture> specular;
    std::shared_ptr<Texture> emission;
    std::shared_ptr<Texture> normal;
};

struct MeshRenderer
{
    Material material;
    Mesh mesh;
    MeshType type;
};
