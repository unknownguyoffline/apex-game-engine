#include "font.hpp"
#include "utility/macro.hpp"
#include "ft2build.h"
#include <freetype/freetype.h>

Font loadFontFromMemory(const unsigned char *data, uint32_t size)
{
    Font font;
    // FT_Library library;
    // if (FT_Init_FreeType(&library))
    // {
    //     ERROR("freetype initialization failed");
    // }
    // FT_Face face;
    // if (FT_New_Memory_Face(library, data, size, 0, &face))
    // {
    //     ERROR("face loading failed");
    // }
    // FT_Set_Pixel_Sizes(face, 0, 48);
    // for (char c = 0; c <= 128; c++)
    // {
    //     if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    //     {
    //         ERROR("freetype char loading failed");
    //     }
    //     Glyph glyph;
    //     Image image;

    //     image.data = face->glyph->bitmap.buffer;
    //     image.size = {face->glyph->bitmap.width, face->glyph->bitmap.rows};
    //     image.channels = 1;

    //     glyph.character = c;
    //     glyph.size = {face->glyph->bitmap.width, face->glyph->bitmap.rows};
    //     glyph.texture.reset(Texture::create(image));
    //     glyph.bearing = {face->glyph->bitmap_left, face->glyph->bitmap_top};
    //     glyph.advance = face->glyph->advance.x;

    //     font.glyphs.push_back(glyph);
    // }
    // FT_Done_Face(face);
    return font;
}
Font loadFontFromTTF(const char *path)
{
    ARG_CHECK(fopen(path, "r") == NULL, {});

    Font font;
    // FT_Library library;
    // if (FT_Init_FreeType(&library))
    // {
    //     ERROR("freetype initialization failed");
    // }
    // FT_Face face;
    // if (FT_New_Face(library, path, 0, &face))
    // {
    //     ERROR("face loading failed");
    // }
    // FT_Set_Pixel_Sizes(face, 0, 48);
    // for (char c = 0; c <= 128; c++)
    // {
    //     if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    //     {
    //         ERROR("freetype char loading failed");
    //     }
    //     Glyph glyph;
    //     Image image;

    //     image.data = face->glyph->bitmap.buffer;
    //     image.size = {face->glyph->bitmap.width, face->glyph->bitmap.rows};
    //     image.channels = 1;

    //     glyph.character = c;
    //     glyph.size = {face->glyph->bitmap.width, face->glyph->bitmap.rows};
    //     glyph.texture.reset(Texture::create(image));
    //     glyph.bearing = {face->glyph->bitmap_left, face->glyph->bitmap_top};
    //     glyph.advance = face->glyph->advance.x;

    //     font.glyphs.push_back(glyph);
    // }
    // FT_Done_Face(face);
    return font;
}
