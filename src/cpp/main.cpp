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
    GLfloat triangleVertices[] {
        -0.5, 0.5, // The upper vertex coordinates
        1, 0, 0, // The upper vertex color (red)
        -0.5f - 0.75f / std::sqrt(3.0f), -0.25, // The left vertex coordinates
        0, 1, 0, // The left vertex color (green)
        -0.5f + 0.75f / std::sqrt(3.0f), -0.25, // The right vertex coordinates
        0, 0, 1 // The right vertex color (blue)
    };

    // The coordinates of the square vertices
    GLfloat squareCoordinates[] {
        0.1, 0.4, // The upper left vertex coordinates
        0.1, -0.4, // The lower left vertex coordinates
        0.9, 0.4, // The upper right vertex coordinates
        0.9, -0.4 // The lower right vertex coordinates
    };

    // The colors of the square vertices
    GLfloat squareColors[] {
        1, 1, 1, // The upper left vertex color
        1, 1, 0, // The lower left vertex color
        0, 1, 1, // The upper right vertex color
        1, 0, 1 // The lower right vertex color
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

    // Create and bind the OpenGL vertex array object for the triangle
    GLuint triangleVao;
    glGenVertexArrays(1, &triangleVao);
    glBindVertexArray(triangleVao);

    // Create, bind and fill the OpenGL vertex buffer object for the triangle
    GLuint triangleVbo;
    glGenBuffers(1, &triangleVbo);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * 5 * sizeof(GLfloat), &triangleVertices, GL_STATIC_DRAW);

    // Enable the a_position attribute and specify how the data from the vertex buffer object is assigned to it
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) 0);

    // Enable the a_color attribute and specify how the data from the vertex buffer object is assigned to it
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat)));

    // Create and bind the OpenGL vertex array object for the square
    GLuint squareVao;
    glGenVertexArrays(1, &squareVao);
    glBindVertexArray(squareVao);

    // Create the OpenGL vertex buffer objects for the square
    GLuint squareVbo[2];
    glGenBuffers(2, squareVbo);

    // Bind and fill the vertex buffer object for the coordinates of the square vertices
    glBindBuffer(GL_ARRAY_BUFFER, squareVbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), &squareCoordinates, GL_STATIC_DRAW);

    // Enable the a_position attribute and specify how the data from the vertex buffer object is assigned to it
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    // Bind and fill the vertex buffer object for the colors of the square vertices
    glBindBuffer(GL_ARRAY_BUFFER, squareVbo[1]);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), &squareColors, GL_STATIC_DRAW);

    // Enable the a_color attribute and specify how the data from the vertex buffer object is assigned to it
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Clear the drawing area
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind the vertex array object for the triangle
        glBindVertexArray(triangleVao);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Bind the vertex array object for the square
        glBindVertexArray(squareVao);

        // Draw the square
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Close the application
    glfwTerminate();

    return 0;
}
