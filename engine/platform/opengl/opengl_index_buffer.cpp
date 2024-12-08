#include "opengl_index_buffer.hpp"
#include "utility/macro.hpp"
#include <glad/glad.h>

IndexBuffer *IndexBuffer::create(size_t size, void *data)
{
    return new OpenglIndexBuffer(size, data);
}

OpenglIndexBuffer::OpenglIndexBuffer(size_t size, void *data)
{
    ARG_CHECK(size == 0, );
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}
OpenglIndexBuffer::~OpenglIndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}
void OpenglIndexBuffer::setData(size_t size, void *data)
{
    ARG_CHECK(size == 0, );
    ARG_CHECK(data == nullptr, );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
}
void OpenglIndexBuffer::subData(size_t size, void *data, size_t offset)
{
    ARG_CHECK(size == 0, );
    ARG_CHECK(data == nullptr, );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}
void OpenglIndexBuffer::select()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}
void OpenglIndexBuffer::deselect()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
