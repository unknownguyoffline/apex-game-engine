#include "texture_library.hpp"
#include "utility/macro.hpp"

void TextureLibrary::loadTexture(const char *path)
{
    ARG_CHECK(fopen(path, "r") == nullptr, );

    Image image = loadImage(path);

    LOG("image.channel: %d", image.channels);
    m_textureList[path] = Texture::create(image);
}
Texture *TextureLibrary::getTexture(const std::string &name)
{
    ARG_CHECK(!has(name), nullptr);

    return m_textureList[name];
}

bool TextureLibrary::has(const std::string &name)
{
    return !(m_textureList.find(name) == m_textureList.end());
}
