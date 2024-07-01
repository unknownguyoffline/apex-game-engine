#include "opengl_vertex_buffer.hpp"
#include "utility/macro.hpp"
#include <GLES3/gl3.h>

uint32_t glType[] = {
    GL_FLOAT, GL_INT, GL_FLOAT, GL_INT, GL_FLOAT, GL_INT, GL_FLOAT, GL_INT,
};

int elementCount[] = {1, 1, 2, 2, 3, 3, 4, 4};

size_t typeSize[] = {sizeof(float),     sizeof(int),       sizeof(float) * 2, sizeof(float) * 2,
                     sizeof(float) * 3, sizeof(float) * 3, sizeof(float) * 4, sizeof(float) * 4};

VertexBuffer *VertexBuffer::create(size_t size, void *data)
{
    return new OpenglVertexBuffer(size, data);
}

OpenglVertexBuffer::OpenglVertexBuffer(size_t size, void *data)
{
    if (size == 0)
    {
        ERROR("OpenglVertexBuffer::constructor [size = 0]");
    }

    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}
void OpenglVertexBuffer::setData(size_t size, void *data)
{
    if (size == 0)
    {
        ERROR("OpenglVertexBuffer::setData [size = 0]");
    }
    if (data == nullptr)
    {
        ERROR("OpenglVertexBuffer::setData [data = nullptr]");
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
void OpenglVertexBuffer::subData(size_t size, void *data, size_t offset)
{
    if (size == 0)
    {
        ERROR("OpenglVertexBuffer::subData [size = 0]");
    }
    if (data == nullptr)
    {
        ERROR("OpenglVertexBuffer::subData [data = nullptr]");
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
void OpenglVertexBuffer::addLayout(VertexLayoutType type)
{
    m_stride += typeSize[type];
    m_layouts.push_back(type);
}

void OpenglVertexBuffer::select()
{
    size_t offset = 0;
    for (int i = 0; i < m_layouts.size(); i++)
    {
        VertexLayoutType type = m_layouts[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, elementCount[type], glType[type], GL_FALSE, m_stride, (void *)offset);
        offset += typeSize[type];
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}
void OpenglVertexBuffer::deselect()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
