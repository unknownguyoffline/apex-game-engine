#include "opengl_frame_buffer.hpp"
#include "utility/macro.hpp"
#include <glad/glad.h>

FrameBuffer *FrameBuffer::create(const glm::uvec2 &size)
{
    return new OpenglFrameBuffer(size);
}

OpenglFrameBuffer::OpenglFrameBuffer(const glm::uvec2 &size)
{
    glGenFramebuffers(1, &m_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);

    glGenRenderbuffers(1, &m_renderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        ERROR("framebuffer not complete");
    }
}

void OpenglFrameBuffer::select()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void OpenglFrameBuffer::deselect()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t OpenglFrameBuffer::getId() const
{
    return m_id;
}
uint32_t OpenglFrameBuffer::getTextureId() const
{
    return m_textureId;
}

void OpenglFrameBuffer::resize(const glm::uvec2 &size)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);
}
void OpenglFrameBuffer::resizeIfNecessary(const glm::uvec2 &size)
{
    if (m_size != size)
    {
        resize(size);
    }
}
OpenglFrameBuffer::~OpenglFrameBuffer()
{
    glDeleteFramebuffers(1, &m_id);
    glDeleteTextures(1, &m_textureId);
    glDeleteRenderbuffers(1, &m_renderBufferId);
}