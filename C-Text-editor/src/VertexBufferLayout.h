#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
    unsigned int count;
    float type;
    unsigned char normalized;
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> element;
    unsigned int stride;

public:
    VertexBufferLayout(/* args */) : stride(0)
    {}
    ~VertexBufferLayout(){}

    /*
    *@tparam type: Specifies the data type of each component in the array. The symbolic constants GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, and GL_UNSIGNED_INT are accepted by glVertexAttribPointer and glVertexAttribIPointer. Additionally GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV and GL_UNSIGNED_INT_10F_11F_11F_REV are accepted by glVertexAttribPointer. GL_DOUBLE is also accepted by glVertexAttribLPointer and is the only token accepted by the type parameter for that function. The initial value is GL_FLOAT.
    *@tparam count: Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
    *@tparam normalized: For glVertexAttribPointer, specifies whether fixed-point data values should be normalized
    */
    template <typename T>
    void push(unsigned int count, T type, unsigned char normalized)
    {
        element.push_back({count, type, normalized});
        stride += sizeof(T)*count;
    }

    inline const std::vector<VertexBufferElement> getElement() const
    {
        return element;
    }

    inline unsigned int getStride() const
    {
        return stride;
    }
};
