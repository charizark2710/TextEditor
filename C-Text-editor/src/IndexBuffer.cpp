#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void *data, unsigned int count)
    : m_count(count)
{
    glGenBuffers(1, &renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &renderer_id);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
}

void IndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
