#include <iostream>

#include "cube.hpp"
#include "../gles.h"
#include "../shader/shader_program.hpp"

namespace BahRPG {
  Cube::Cube(ShaderProgram& shader) : shader(shader) {
    setupBuffers();
  }

  void Cube::draw() {
    shader.use();

    glEnableVertexAttribArray(aPosition);
    glEnableVertexAttribArray(aColor);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(aPosition, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(aColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(aPosition);
    glDisableVertexAttribArray(aColor);
  }

  void Cube::setupBuffers() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    aPosition = shader.getAttribLocation("aPosition");
    aColor = shader.getAttribLocation("aColor");
  }
}