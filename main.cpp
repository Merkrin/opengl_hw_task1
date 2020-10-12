#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <iostream>
#include <cmath>

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
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
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    GLfloat vertices[] {
            0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
            -0.75f / sqrtf(3), -0.25f, 0.0f, 1.0f, 0.0f,
            0.75f / sqrtf(3), -0.25f, 0.0f, 0.0f, 1.0f
    };

    std::string vertexShaderSource = R"(
    #version 410 core

    layout (location = 0) in vec2 a_position;
    layout (location = 1) in vec3 a_color;

    out vec3 v_color;

    void main() {
        v_color = a_color;
        gl_Position = vec4(a_position, 0.0, 1.0);
    }
    )";

    std::string fragmentShaderSource = R"(
    #version 410 core

    in vec3 v_color;

    out vec4 color;

    void main() {
        color = vec4(v_color, 1.0);
    }
    )";

    const char* text;

    GLint status;

    text = vertexShaderSource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &text, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        char s[1024];
        int l;

        glGetShaderInfoLog(vertexShader, 1024, &l, s);

        fprintf(stderr, "Vertex shader errors:\n%s\n", s);

        return -1;
    }

    text = fragmentShaderSource.c_str();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &text, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        char s[1024];
        int l;

        glGetShaderInfoLog(fragmentShader, 1024, &l, s);

        fprintf(stderr, "Fragment shader errors:\n%s\n", s);

        return -1;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        char s[1024];
        int l;

        glGetProgramInfoLog(program, 1024, &l, s);

        fprintf(stderr, "Error: %s\n", s);

        return -1;
    }

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
