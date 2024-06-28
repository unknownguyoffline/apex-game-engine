#include "texture_library.hpp"

void TextureLibrary::loadTexture(const char *path) { m_textureList.emplace(path, Texture::create(loadImage(path))); }
Texture *TextureLibrary::getTexture(std::string name) { return m_textureList.at(name); }
