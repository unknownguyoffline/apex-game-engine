#include "mesh.hpp"
#include "core/application.hpp"
#include "renderer.hpp"
void Mesh::update()
{
    m_vertexBuffer.reset(VertexBuffer::create(sizeof(Vertex) * vertices.size(), vertices.data()));
    m_indexBuffer.reset(IndexBuffer::create(sizeof(uint32_t) * indices.size(), indices.data()));
    m_vertexBuffer->addLayout(FLOAT3);
    m_vertexBuffer->addLayout(FLOAT2);
    m_vertexBuffer->addLayout(FLOAT3);
}

void Mesh::draw()
{
    Application::get()->renderer2D.draw(m_vertexBuffer, m_indexBuffer, indices.size());
}
