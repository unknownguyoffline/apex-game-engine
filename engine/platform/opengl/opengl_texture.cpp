#include "opengl_texture.hpp"
#include <GLES3/gl3.h>

Texture *Texture::create(const Image &image) { return new OpenglTexture(image); }
OpenglTexture::OpenglTexture(const Image &image)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.size.x, image.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
}
void OpenglTexture::select(int slot)
{
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void OpenglTexture::deselect() { glBindTexture(GL_TEXTURE_2D, 0); }
