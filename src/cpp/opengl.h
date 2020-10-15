#ifndef TEST_OPENGL_H
#define TEST_OPENGL_H

#include <GL/glew.h>

#include <string>

GLuint createShader(const std::string& source, GLenum type);

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

#endif //TEST_OPENGL_H
