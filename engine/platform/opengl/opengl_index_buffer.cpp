#include "opengl_index_buffer.hpp"
#include "utility/macro.hpp"
#include <GLES3/gl3.h>

IndexBuffer *IndexBuffer::create(size_t size, void *data) { return new OpenglIndexBuffer(size, data); }

OpenglIndexBuffer::OpenglIndexBuffer(size_t size, void *data)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}
void OpenglIndexBuffer::setData(size_t size, void *data)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
}
void OpenglIndexBuffer::subData(size_t size, void *data, size_t offset)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}
void OpenglIndexBuffer::select() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
void OpenglIndexBuffer::deselect() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
