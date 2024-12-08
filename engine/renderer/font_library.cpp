#include "font_library.hpp"
#include "utility/macro.hpp"

void FontLibrary::loadFont(const char *path)
{
    ARG_CHECK(fopen(path, "r") == nullptr, );

    m_fontMap[path] = loadFontFromTTF(path);
}

Font FontLibrary::getFont(const char *name)
{
    return m_fontMap[name];
}
