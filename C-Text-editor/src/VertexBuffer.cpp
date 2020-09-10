#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    glGenBuffers(1, &renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &renderer_id);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
}

void VertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
