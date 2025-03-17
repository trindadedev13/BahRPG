#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>

#include "../gles.h"
#include "../shader/shader_program.hpp"

namespace BahRPG {
  class Cube {
    public:
      Cube(ShaderProgram& shader);

      void draw();

    private:
      ShaderProgram& shader;
      GLuint vbo, ibo;
      GLint aPosition, aColor;

      const GLfloat vertices[48] = {
          -0.5f, -0.5f, -0.5f,  1, 0, 0,  0.5f, -0.5f, -0.5f,  0, 1, 0,  
           0.5f,  0.5f, -0.5f,  0, 0, 1, -0.5f,  0.5f, -0.5f,  1, 1, 0,  
          -0.5f, -0.5f,  0.5f,  1, 0, 1,  0.5f, -0.5f,  0.5f,  0, 1, 1,  
           0.5f,  0.5f,  0.5f,  1, 1, 1, -0.5f,  0.5f,  0.5f,  0, 0, 0   
      };

      const GLushort indexes[36] = {
          0, 1, 2, 2, 3, 0,  4, 5, 6, 6, 7, 4,  
          0, 4, 7, 7, 3, 0,  1, 5, 6, 6, 2, 1,  
          3, 2, 6, 6, 7, 3,  0, 1, 5, 5, 4, 0   
      };

      void setupBuffers();
  };
}

#endif