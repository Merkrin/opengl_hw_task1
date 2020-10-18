#pragma once
#include <GL/glew.h>

#include <string>

GLuint createShader(const std::string& source, GLenum type);

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
