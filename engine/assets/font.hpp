#pragma once
#include "renderer/texture.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

struct Glyph
{
    char character = 0;
    glm::uvec2 bearing = glm::uvec2(0);
    uint32_t advance = 0;
    std::shared_ptr<Texture> texture = nullptr;
    glm::uvec2 size = glm::uvec2(0);
};

struct Font
{
    std::vector<Glyph> glyphs;
};

Font loadFontFromTTF(const char *path);
Font loadFontFromMemory(const unsigned char *data, uint32_t size);
