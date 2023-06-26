#include "luz.h"

Luz::Luz() {
    luzPosicion[0] = 1.0f;
    luzPosicion[1] = 1.0f;
    luzPosicion[2] = 1.0f;

    luzColor[0] = 1.0f;
    luzColor[1] = 1.0f;
    luzColor[2] = 1.0f;
}

void Luz::configurar(GLuint shaderProgram) {
    GLint luzPosicionLoc = glGetUniformLocation(shaderProgram, "luzPosicion");
    GLint luzColorLoc = glGetUniformLocation(shaderProgram, "luzColor");

    glUseProgram(shaderProgram);
    glUniform3fv(luzPosicionLoc, 1, luzPosicion);
    glUniform3fv(luzColorLoc, 1, luzColor);
}
