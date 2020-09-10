#pragma once

#include <GL/glew.h>

class IndexBuffer
{
private:
    unsigned int renderer_id;
    unsigned int m_count;

public:
    IndexBuffer(const void *data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline unsigned int getCount() const {return m_count;};
};
