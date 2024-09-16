#include "Shaders.h"
#include <fstream>
#include <sstream>

Shader::Shader() : m_Id(0) {}

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    Init(vertexShaderPath, fragmentShaderPath);
}

void Shader::Init(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    m_Id = createShaderProgram(vertexShaderPath, fragmentShaderPath);
    isInitialized = true;
}

Shader::~Shader() { glDeleteProgram(m_Id); }

void Shader::Bind() const { glUseProgram(m_Id); }
void Shader::Unbind() const { glUseProgram(0); }

std::string Shader::loadShaderSource(const char *filePath)
{
    std::ifstream file;
    std::stringstream stream;

    file.open(filePath);
    stream << file.rdbuf();
    file.close();

    return stream.str();
}

u32 Shader::compileShader(GLenum type, const std::string &source)
{
    u32 shader               = glCreateShader(type);
    const char *shaderSource = source.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        if (type == GL_VERTEX_SHADER)
        {
            printf("ERROR::VERTEX_SHADER::COMPILATION_FAILED\n {%s}", infoLog);
        }
        else if (type == GL_FRAGMENT_SHADER)
        {
            printf("ERROR::VERTEX_SHADER::COMPILATION_FAILED\n {%s}", infoLog);
        }
    }

    return shader;
}

u32 Shader::createShaderProgram(const char *vertexPath,
                                const char *fragmentPath)
{
    std::string vertexCode   = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);

    GLuint vertexShader   = compileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        printf("ERROR::PROGRAM::LINKING_FAILED\n {%s}", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void Shader::SetUniformFloat3(const char *name, f32 x, f32 y, f32 z) const
{
    glUniform3f(glGetUniformLocation(m_Id, "textColor"), x, y, z);
}

void Shader::SetUniformMat4(const std::string &name, const mat4x4 &matrix) {
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetInt(const std::string &name, s32 Id)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    glUniform1i(location, Id);
}

void Shader::SetIntArray(const std::string &name, s32 *array, s32 array_count)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    glUniform1iv(location, array_count, array);
}
