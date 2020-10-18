#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <iostream>
#include <cmath>

#include "load_file.h"
#include "opengl.h"

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    /* Need for mac os */
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    GLenum err = glewInit();

    if (GLEW_OK != err) {
        fprintf(stderr, "Glew errors: %s\n", glewGetErrorString(err));
        return -1;
    }

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    GLfloat vertices[] {
            0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
            -0.75f / sqrtf(3), -0.25f, 0.0f, 1.0f, 0.0f,
            0.75f / sqrtf(3), -0.25f, 0.0f, 0.0f, 1.0f
    };

    GLuint program;

    try {
        std::string vertexShaderSource = loadFile("../src/glsl/vertex.glsl");
        std::string fragmentShaderSource = loadFile("../src/glsl/fragment.glsl");

        GLuint vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        program = createProgram(vertexShader, fragmentShader);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;

        glfwTerminate();

        return -1;
    }

    glUseProgram(program);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * 5 * sizeof(GLfloat), &vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat)));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
