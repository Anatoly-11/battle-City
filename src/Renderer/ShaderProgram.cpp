#include "ShaderProgram.h"
#include <iostream>
//-------------------------------------------------------------------------------------------------------------
namespace Renderer {
  ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader) noexcept
    : m_isCompiled(false), m_ID(0) {
    GLuint vertexShaderID, fragmentShaderID;
    if(!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
      std::cerr << "VERTEX SHADER::Compile time error" << std::endl;
      return;
    }
    if(!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
      std::cerr << "FRAGMENT SHADER::Compile time error" << std::endl;
      glDeleteShader(vertexShaderID);
      return;
    }
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShaderID);
    glAttachShader(m_ID, fragmentShaderID);
    glLinkProgram(m_ID);
    GLint success;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if(!success) {
      GLchar infoLog[1024];
      glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
      std::cerr << "ERROR::SHADER::Link time error:\n" << infoLog << std::endl;
    } else {
      m_isCompiled = true;
    }
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
  }
  //-------------------------------------------------------------------------------------------------------------
  ShaderProgram :: ~ShaderProgram() noexcept {
    if(m_isCompiled) {
      glDeleteProgram(m_ID);
    }
  }
  //-------------------------------------------------------------------------------------------------------------
  bool ShaderProgram :: createShader(const std::string &shader, const GLenum shaderType, GLuint &shaderID) noexcept {
    shaderID = glCreateShader(shaderType);
    const char *code = shader.data();
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);
    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success) {
      GLchar infoLog[1024];
      glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
      std::cerr << "ERROR::SHADER::Compile time error:\n" << infoLog << std::endl;
      return false;
    }
    return true;
  }
  //-------------------------------------------------------------------------------------------------------------
  ShaderProgram :: ShaderProgram(ShaderProgram &&shaderProgram) noexcept
    : m_ID(shaderProgram.m_ID), m_isCompiled(shaderProgram.m_isCompiled) {

    shaderProgram.m_ID = 0;
    shaderProgram.m_isCompiled = false;
  }
  //-------------------------------------------------------------------------------------------------------------
  ShaderProgram &ShaderProgram ::operator=(ShaderProgram &&shaderProgram) noexcept {
    if(m_isCompiled) {
      glDeleteProgram(m_ID);
    }
    m_ID = shaderProgram.m_ID;
    m_isCompiled = shaderProgram.m_isCompiled;

    shaderProgram.m_ID = 0;
    shaderProgram.m_isCompiled = false;
    return *this;
  }
  //-------------------------------------------------------------------------------------------------------------
  bool ShaderProgram :: isCompiled() const noexcept {
    return m_isCompiled;
  }
  //-------------------------------------------------------------------------------------------------------------
  void ShaderProgram :: use() const noexcept {
    if(m_isCompiled) {
      glUseProgram(m_ID);
    }
  }
  //-------------------------------------------------------------------------------------------------------------
  void ShaderProgram :: setInt(const std::string &name, const GLint value) noexcept {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
  }
  //-------------------------------------------------------------------------------------------------------------
}