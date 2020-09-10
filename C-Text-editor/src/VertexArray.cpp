#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray(/* args */)
{
    glGenVertexArrays(1, &rendererId);
    glBindVertexArray(rendererId);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &rendererId);
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const auto &elements = layout.getElement();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements.at(i);

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *)offset);

        offset += element.count * sizeof(element.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(rendererId);
}

void VertexArray::UnBind() const
{
    glBindVertexArray(0);
}
