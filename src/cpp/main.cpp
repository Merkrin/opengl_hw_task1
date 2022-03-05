#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <iostream>

#include "files.h"
#include "opengl.h"

#include "utils.h"
#include "figure.h"

void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "The GLFW function call completed with errors:\n" << description << std::endl;
}

int main()
{
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
    if (!window)
    {
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
    if (glewStatus != GLEW_OK)
    {
        std::cerr << "The GLEW initialization completed with errors:\n" << glewGetErrorString(glewStatus) << std::endl;
        glfwTerminate();
        return -1;
    }

    GLfloat backgroundCoordinates[]{
            utils::intCoordinateToFloat(-10), utils::intCoordinateToFloat(10),
            utils::intCoordinateToFloat(-10), utils::intCoordinateToFloat(-10),
            utils::intCoordinateToFloat(10), utils::intCoordinateToFloat(10),
            utils::intCoordinateToFloat(10), utils::intCoordinateToFloat(-10)
    };

    GLfloat backgroundColors[]{
            utils::intColorToFloat(66), utils::intColorToFloat(102), utils::intColorToFloat(212),
            utils::intColorToFloat(66), utils::intColorToFloat(102), utils::intColorToFloat(212),
            utils::intColorToFloat(66), utils::intColorToFloat(212), utils::intColorToFloat(207),
            utils::intColorToFloat(66), utils::intColorToFloat(212), utils::intColorToFloat(207)
    };

    GLfloat grassCoordinates[]{
            utils::intCoordinateToFloat(-10), utils::intCoordinateToFloat(-4),
            utils::intCoordinateToFloat(-10), utils::intCoordinateToFloat(-10),
            utils::intCoordinateToFloat(10), utils::intCoordinateToFloat(-4),
            utils::intCoordinateToFloat(10), utils::intCoordinateToFloat(-10)
    };

    GLfloat grassColors[]{
            utils::intColorToFloat(75), utils::intColorToFloat(156), utils::intColorToFloat(31),
            utils::intColorToFloat(30), utils::intColorToFloat(173), utils::intColorToFloat(14),
            utils::intColorToFloat(28), utils::intColorToFloat(128), utils::intColorToFloat(17),
            utils::intColorToFloat(73), utils::intColorToFloat(179), utils::intColorToFloat(91)
    };

    GLfloat houseCoordinates[]{
            utils::intCoordinateToFloat(-7), utils::intCoordinateToFloat(2),
            utils::intCoordinateToFloat(-7), utils::intCoordinateToFloat(-5),
            utils::intCoordinateToFloat(5), utils::intCoordinateToFloat(2),
            utils::intCoordinateToFloat(5), utils::intCoordinateToFloat(-5)
    };

    GLfloat houseColors[]{
            utils::intColorToFloat(217), utils::intColorToFloat(199), utils::intColorToFloat(130),
            utils::intColorToFloat(217), utils::intColorToFloat(199), utils::intColorToFloat(130),
            utils::intColorToFloat(217), utils::intColorToFloat(199), utils::intColorToFloat(130),
            utils::intColorToFloat(217), utils::intColorToFloat(199), utils::intColorToFloat(130)
    };

    GLfloat roadCoordinates[]{
            utils::intCoordinateToFloat(-2), utils::intCoordinateToFloat(-5),
            utils::intCoordinateToFloat(-7), utils::intCoordinateToFloat(-10),
            utils::intCoordinateToFloat(0), utils::intCoordinateToFloat(-5),
            utils::intCoordinateToFloat(5), utils::intCoordinateToFloat(-10)
    };

    GLfloat roadColors[]{
            utils::intColorToFloat(163), utils::intColorToFloat(137), utils::intColorToFloat(126),
            utils::intColorToFloat(163), utils::intColorToFloat(137), utils::intColorToFloat(126),
            utils::intColorToFloat(163), utils::intColorToFloat(137), utils::intColorToFloat(126),
            utils::intColorToFloat(163), utils::intColorToFloat(137), utils::intColorToFloat(126)
    };

    GLfloat doorCoordinates[]{
            utils::intCoordinateToFloat(-2), utils::intCoordinateToFloat(-2),
            utils::intCoordinateToFloat(0), utils::intCoordinateToFloat(-2),
            utils::intCoordinateToFloat(-2), utils::intCoordinateToFloat(-5),
            utils::intCoordinateToFloat(0), utils::intCoordinateToFloat(-5)
    };

    GLfloat doorColors[]{
            utils::intColorToFloat(162), utils::intColorToFloat(169), utils::intColorToFloat(171),
            utils::intColorToFloat(162), utils::intColorToFloat(169), utils::intColorToFloat(171),
            utils::intColorToFloat(162), utils::intColorToFloat(169), utils::intColorToFloat(171),
            utils::intColorToFloat(162), utils::intColorToFloat(169), utils::intColorToFloat(171)
    };

    GLfloat windowCoordinates[]{
            utils::intCoordinateToFloat(1), utils::intCoordinateToFloat(0),
            utils::intCoordinateToFloat(1), utils::intCoordinateToFloat(-2),
            utils::intCoordinateToFloat(3), utils::intCoordinateToFloat(0),
            utils::intCoordinateToFloat(3), utils::intCoordinateToFloat(-2)
    };

    GLfloat windowColors[]{
            utils::intColorToFloat(255), utils::intColorToFloat(253), utils::intColorToFloat(112),
            utils::intColorToFloat(219), utils::intColorToFloat(217), utils::intColorToFloat(194),
            utils::intColorToFloat(255), utils::intColorToFloat(253), utils::intColorToFloat(112),
            utils::intColorToFloat(219), utils::intColorToFloat(217), utils::intColorToFloat(194)
    };

    GLfloat roofCoordinates[]{
            utils::intCoordinateToFloat(-7), utils::intCoordinateToFloat(2),
            utils::intCoordinateToFloat(-1), utils::intCoordinateToFloat(5),
            utils::intCoordinateToFloat(5), utils::intCoordinateToFloat(2)
    };

    GLfloat roofColors[]{
            utils::intColorToFloat(166), utils::intColorToFloat(22), utils::intColorToFloat(22),
            utils::intColorToFloat(191), utils::intColorToFloat(83), utils::intColorToFloat(47),
            utils::intColorToFloat(240), utils::intColorToFloat(93), utils::intColorToFloat(14)
    };

    GLfloat sunCoordinates[]{
            utils::intCoordinateToFloat(7), utils::intCoordinateToFloat(9),
            utils::intCoordinateToFloat(8), utils::intCoordinateToFloat(9),
            utils::intCoordinateToFloat(9), utils::intCoordinateToFloat(8),
            utils::intCoordinateToFloat(9), utils::intCoordinateToFloat(7),
            utils::intCoordinateToFloat(8), utils::intCoordinateToFloat(6),
            utils::intCoordinateToFloat(7), utils::intCoordinateToFloat(6),
            utils::intCoordinateToFloat(6), utils::intCoordinateToFloat(7),
            utils::intCoordinateToFloat(6), utils::intCoordinateToFloat(8),
            utils::intCoordinateToFloat(7), utils::intCoordinateToFloat(9)
    };

    GLfloat sunColors[]{
            utils::intColorToFloat(255), utils::intColorToFloat(230), utils::intColorToFloat(0),
            utils::intColorToFloat(255), utils::intColorToFloat(230), utils::intColorToFloat(0),
            utils::intColorToFloat(255), utils::intColorToFloat(230), utils::intColorToFloat(0),
            utils::intColorToFloat(255), utils::intColorToFloat(230), utils::intColorToFloat(0),
            utils::intColorToFloat(255), utils::intColorToFloat(230), utils::intColorToFloat(0),
            utils::intColorToFloat(255), utils::intColorToFloat(230), utils::intColorToFloat(0),
            utils::intColorToFloat(255), utils::intColorToFloat(230), utils::intColorToFloat(0),
            utils::intColorToFloat(255), utils::intColorToFloat(230), utils::intColorToFloat(0),
            utils::intColorToFloat(255), utils::intColorToFloat(230), utils::intColorToFloat(0)
    };

    // The OpenGL program
    GLuint program;

    try
    {
        // Load the shader source
        std::string vertexShaderSource = loadText("../src/glsl/vertex.glsl");
        std::string fragmentShaderSource = loadText("../src/glsl/fragment.glsl");

        // Create the OpenGL shaders (see the implementation)
        GLuint vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        // Create the OpenGL program (see the implementation)
        program = createProgram(vertexShader, fragmentShader);
    }
    catch (const std::exception& e)
    {
        // Close the application if there is an error while loading the files, compiling the shaders or linking the program
        std::cerr << e.what() << std::endl;
        glfwTerminate();
        return -1;
    }

    // Use the created program for drawing
    glUseProgram(program);

    figure background = figure(backgroundCoordinates,
                               sizeof(backgroundCoordinates) / sizeof(*backgroundCoordinates) / 2 * 5,
                               backgroundColors);
    background.setupFigure();

    figure grass = figure(grassCoordinates,
                          sizeof(grassCoordinates) / sizeof(*grassCoordinates) / 2 * 5,
                          grassColors);
    grass.setupFigure();

    figure house = figure(houseCoordinates,
                          sizeof(houseCoordinates) / sizeof(*houseCoordinates) / 2 * 5,
                          houseColors);
    house.setupFigure();

    figure road = figure(roadCoordinates,
                         sizeof(roadCoordinates) / sizeof(*roadCoordinates) / 2 * 5,
                         roadColors);
    road.setupFigure();


    figure door = figure(doorCoordinates,
                         sizeof(doorCoordinates) / sizeof(*doorCoordinates) / 2 * 5,
                         doorColors);
    door.setupFigure();

    figure windowFigure = figure(windowCoordinates,
                         sizeof(windowCoordinates) / sizeof(*windowCoordinates) / 2 * 5,
                         windowColors);
    windowFigure.setupFigure();

    figure roof = figure(roofCoordinates,
                                 sizeof(roofCoordinates) / sizeof(*roofCoordinates) / 2 * 5,
                                 roofColors);
    roof.setupFigure();

    figure sun = figure(sunCoordinates,
                         sizeof(sunCoordinates) / sizeof(*sunCoordinates) / 2 * 5,
                         sunColors);
    sun.setupFigure();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Clear the drawing area
        glClear(GL_COLOR_BUFFER_BIT);

        background.drawFigure(1);

        grass.drawFigure(1);

        house.drawFigure(1);

        road.drawFigure(1);

        door.drawFigure(1);

        windowFigure.drawFigure(1);

        roof.drawFigure(0);

        sun.drawFigure(2);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Close the application
    glfwTerminate();

    return 0;
}
