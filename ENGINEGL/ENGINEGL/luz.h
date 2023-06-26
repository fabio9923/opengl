#pragma once
#ifndef LUZ_H
#define LUZ_H

#include <glad/glad.h>
#include <glfw3.h>

class Luz {
public:
    Luz();
    void configurar(GLuint shaderProgram);
    void aplicar();

private:
    GLfloat luzPosicion[3];
    GLfloat luzColor[3];
};

#endif