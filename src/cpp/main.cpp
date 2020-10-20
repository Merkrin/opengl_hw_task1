#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <iostream>
#include <cmath>

#include "files.h"
#include "opengl.h"

// If you want to implement keyboard controls, look how to process keyboard events using the GLFW library
// https://www.glfw.org/docs/latest/quick.html#quick_key_input
//
// If you want to implement animation, look how to get the time since initialization using the GLFW library
// https://www.glfw.org/docs/latest/quick.html#quick_timer
//
// You can calculate the delta time like that:
//
// double time = glfwGetTime();
// ...
// while (!glfwWindowShouldClose(window)) {
//     double newTime = glfwGetTime();
//     double deltaTime = newTime - time;
//     time = newTime;
//     ...
// }

void glfwErrorCallback(int error, const char* description) {
    std::cerr << "The GLFW function call completed with errors:\n" << description << std::endl;
}

int main() {
    // Set the GLFW error callback
    glfwSetErrorCallback(glfwErrorCallback);

    // Initialize the GLFW library, close the application if the GLFW library isn't initialized
    if (!glfwInit()) return -1;

    // Set the OpenGL version window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Set the OpenGL context window hints (required for macOS)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 640, "Task 1", nullptr, nullptr);

    // Close the application if the window isn't created
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Limit the frame rate to a screen refresh rate
    glfwSwapInterval(1);

    // Initialize the GLEW library
    GLenum glewStatus = glewInit();

    // Close the application if the GLEW library isn't initialized
    if (glewStatus != GLEW_OK) {
        std::cerr << "The GLEW initialization completed with errors:\n" << glewGetErrorString(glewStatus) << std::endl;
        glfwTerminate();
        return -1;
    }

    // The interleaved coordinates and colors of the triangle vertices
    GLfloat vertices[] {
        0.0f, 0.5f, // The upper vertex coordinates
        1.0f, 0.0f, 0.0f, // The upper vertex color (red)
        -0.75f / sqrtf(3), // The left vertex coordinates
        -0.25f, 0.0f, 1.0f, 0.0f, // The left vertex color (green)
        0.75f / sqrtf(3), // The right vertex coordinates
        -0.25f, 0.0f, 0.0f, 1.0f // The right vertex color (blue)
    };

    // The OpenGL program
    GLuint program;

    try {
        // Load the shader source
        std::string vertexShaderSource = loadText("../src/glsl/vertex.glsl");
        std::string fragmentShaderSource = loadText("../src/glsl/fragment.glsl");

        // Create the OpenGL shaders (see the implementation)
        GLuint vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        // Create the OpenGL program (see the implementation)
        program = createProgram(vertexShader, fragmentShader);
    }
    catch (const std::exception& e) {
        // Close the application if there is an error while loading the files, compiling the shaders or linking the program
        std::cerr << e.what() << std::endl;
        glfwTerminate();
        return -1;
    }

    // Use the created program for drawing
    glUseProgram(program);

    // Create and bind the OpenGL vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create, bind and fill the OpenGL vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * 5 * sizeof(GLfloat), &vertices, GL_STATIC_DRAW);

    // Enable the a_position attribute and specify how the data from the vertex buffer object is assigned to it
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) 0);

    // Enable the a_color attribute and specify how the data from the vertex buffer object is assigned to it
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat)));

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Clear the drawing area
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Close the application
    glfwTerminate();

    return 0;
}
