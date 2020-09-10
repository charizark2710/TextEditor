#include "Shader.h"

std::string filePath;
unsigned int rendererId;

Shader::Shader(const std::string &path) : filePath(path), rendererId(0)
{
    ShaderSource source = ParseShader(path);
    rendererId = createShader(source.vs, source.fs);
}

Shader::~Shader()
{
    glDeleteProgram(rendererId);
}

void Shader::Bind() const
{
    glUseProgram(rendererId);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

ShaderSource Shader::ParseShader(const std::string path)
{
    std::string s = path + "\\res\\Shader\\Basic.glsl";
    std::ifstream stream(s);
    std::string line;

    enum class shaderType
    {
        NONE = -1,
        vertex = 0,
        fragment = 1,
    };

    std::stringstream ss[2];

    shaderType type = shaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("vertex") != std::string::npos)
        {
            type = shaderType::vertex;
        }
        else if (line.find("fragment") != std::string::npos)
        {
            type = shaderType::fragment;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char *message = new char[len * sizeof(char)];
        glGetShaderInfoLog(id, len, &len, message);
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

//set uniform
void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniform1f(const std::string &name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform1i(const std::string &name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform4fMatrix(const std::string &name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::getUniformLocation(const std::string &name)
{

    if (UniformLocationCache.find(name) != UniformLocationCache.end())
    {
        return UniformLocationCache[name];
    }

    int location = glGetUniformLocation(rendererId, name.c_str());
    if (location == -1)
    {
        std::cout << "Warning: uniform " << name << " doesn't exist" << std::endl;
    }

    UniformLocationCache[name] = location;

    return location;
}
