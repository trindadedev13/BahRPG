#include <iostream>
#include "../gles.h"
#include "shader_program.hpp"

namespace BahRPG {
  ShaderProgram::ShaderProgram(const char* vertexSrc, const char* fragmentSrc) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    checkLinkingErrors();
  }

  void ShaderProgram::use() {
    glUseProgram(program);
  }

  GLint ShaderProgram::getAttribLocation(const char* name) {
    return glGetAttribLocation(program, name);
  }

  GLuint ShaderProgram::compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    return shader;
  }

  void ShaderProgram::checkLinkingErrors() {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
      std::cerr << "Shader linking failed!" << std::endl;
    }
  }
}