#include "opengl_texture.hpp"
#include "utility/macro.hpp"
#include <glad/glad.h>

Texture *Texture::create(const Image &image)
{
    return new OpenglTexture(image);
}
OpenglTexture::OpenglTexture(const Image &image)
{
    ARG_CHECK(image.data == nullptr, );

    GLenum format = GL_RGBA;
    if (image.channels == 1)
    {
        format = GL_RED;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }

    if (image.channels == 2)
        format = GL_RG;
    if (image.channels == 3)
        format = GL_RGB;
    if (image.channels == 4)
        format = GL_RGBA;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, format, image.size.x, image.size.y, 0, format, GL_UNSIGNED_BYTE, image.data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void OpenglTexture::select(int slot)
{
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void OpenglTexture::deselect()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t OpenglTexture::getId()
{
    return m_id;
}

OpenglTexture::~OpenglTexture()
{
    glDeleteTextures(1, &m_id);
}
