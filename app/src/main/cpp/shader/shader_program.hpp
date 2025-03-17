#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "../gles.h"

namespace BahRPG {
  class ShaderProgram {
    public:
      ShaderProgram(const char* vertexSrc, const char* fragmentSrc);

      GLuint program;
      GLint getAttribLocation(const char* name);

      void use();

    private:
      GLuint compileShader(GLenum type, const char* source);

      void checkLinkingErrors();
  };
}

#endif