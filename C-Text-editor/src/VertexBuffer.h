#pragma once

#include <GL/glew.h>
#include <glfw3.h>

class VertexBuffer
{
private:
    unsigned int renderer_id;

public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};
