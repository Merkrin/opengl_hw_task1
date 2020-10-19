#include "opengl.h"

#include "exception.h"

GLuint createShader(const std::string& source, GLenum type) {
    const char* data = source.data();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &data, nullptr);
    glCompileShader(shader);

    GLint status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        GLint length;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        char* log = new char[length];

        glGetShaderInfoLog(shader, length, nullptr, log);

        std::string message = "createShader: the ";

        if (type == GL_VERTEX_SHADER) message += "vertex";
        else if (type == GL_FRAGMENT_SHADER) message += "fragment";

        message += " shader compilation completed with errors:\n";
        message += log;

        delete[] log;

        throw Exception(message);
    }

    return shader;
}

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint status;

    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        GLint length;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        char* log = new char[length];

        glGetProgramInfoLog(program, length, nullptr, log);

        std::string message = "createProgram: the program linking completed with errors:\n";
        message += log;

        delete[] log;

        throw Exception(message);
    }

    return program;
}
