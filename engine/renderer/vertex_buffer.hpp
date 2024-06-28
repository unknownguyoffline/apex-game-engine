#pragma once
#include <stddef.h>
#include <stdint.h>

enum VertexLayoutType
{
    FLOAT,
    INT,
    FLOAT2,
    INT2,
    FLOAT3,
    INT3,
    FLOAT4,
    INT4
};

class VertexBuffer
{
  public:
    virtual void setData(size_t size, void *data) = 0;
    virtual void subData(size_t size, void *data, size_t offset) = 0;
    virtual void addLayout(VertexLayoutType type) = 0;

    virtual void select() = 0;
    virtual void deselect() = 0;

    static VertexBuffer *create(size_t size, void *data);
};
