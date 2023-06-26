#pragma once
#ifndef LIBRERIA_H
#define LIBRERIA_H

#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
GLuint createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

using namespace std;

#endif

