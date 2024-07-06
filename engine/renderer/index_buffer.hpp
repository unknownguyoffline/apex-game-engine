#pragma once
#include <stddef.h>
#include <stdint.h>

class IndexBuffer
{
  public:
    virtual void setData(size_t size, void *data) = 0;
    virtual void subData(size_t size, void *data, size_t offset) = 0;

    virtual void select() = 0;
    virtual void deselect() = 0;
    virtual ~IndexBuffer()
    {
    }

    static IndexBuffer *create(size_t size, void *data);
};
