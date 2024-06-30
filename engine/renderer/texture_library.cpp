#include "texture_library.hpp"

void TextureLibrary::loadTexture(const char *path)
{
    m_textureList[path] = Texture::create(loadImage(path));
}
Texture *TextureLibrary::getTexture(std::string name)
{
    if (m_textureList.find(name) == m_textureList.end())
        return nullptr;
    return m_textureList[name];
}
