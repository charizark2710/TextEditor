#pragma once
#include <GL/glew.h>
#include <glfw3.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *msg, const void *data);

class Renderer
{
private:
    /* data */
public:
    Renderer(/* args */);
    ~Renderer();
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader);
};
