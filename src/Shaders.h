#pragma once
#include <glad/glad.h>
#include <string>
#include "types.h"

class Shader
{
  public:
    Shader();
    Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
    ~Shader();
    void Init(const char *vertexShaderPath, const char *fragmentShaderPath);
    void Bind() const;
    void Unbind() const;
    void SetUniformFloat3(const char *name, f32 x, f32 y, f32 z) const;

    u32 m_Id;

  private:
    u32 compileShader(GLenum type, const std::string &source);
    u32 createShaderProgram(const char *vertexPath, const char *fragmentPath);
    std::string loadShaderSource(const char *filePath);

  private:
};
