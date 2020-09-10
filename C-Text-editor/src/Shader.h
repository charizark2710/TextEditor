#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderSource
{
    std::string vs;
    std::string fs;
};

class Shader
{
private:
    std::string filePath;
    unsigned int rendererId;
    std::unordered_map<std::string, int> UniformLocationCache;

public:
    Shader(const std::string &fileName);
    ~Shader();

    void Bind() const;
    void UnBind() const;

    //set uniform
    void setUniform4f(const std::string &name, float v0, float v1, float f2, float f3);
    void setUniform1f(const std::string &name, float value);
    void setUniform1i(const std::string &name, int value);
    void setUniform4fMatrix(const std::string &name, const glm::mat4 &matrix);

private:
    int getUniformLocation(const std::string &name);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);
    ShaderSource ParseShader(const std::string path);
};
