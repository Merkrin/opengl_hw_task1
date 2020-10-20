#pragma once

#include <GL/glew.h>

#include <string>

/**
 * Creates the shader
 * @param source the shader source
 * @param type the shader type
 * @return the created shader
 */
GLuint createShader(const std::string& source, GLenum type);

/**
 * Creates the program
 * @param vertexShader the vertex shader
 * @param fragmentShader the fragment shader
 * @return the created program
 */
GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
