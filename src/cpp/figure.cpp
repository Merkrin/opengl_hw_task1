//
// Created by Irina Barchuk on 04.03.2022.
//
#include "figure.h"

void figure::setupFigure()
{
    // Bind the OpenGL vertex array object for the figure
    glGenVertexArrays(1, &figureVao);
    glBindVertexArray(figureVao);

    // Create, bind and fill the OpenGL vertex buffer object for the figure
    GLuint figureVbo;
    glGenBuffers(1, &figureVbo);
    glBindBuffer(GL_ARRAY_BUFFER, figureVbo);
    glBufferData(GL_ARRAY_BUFFER, coordinatesAmount / 5 * 5 * sizeof(GLfloat), &figureCoordinates[0], GL_STATIC_DRAW);

    // Enable the a_position attribute and specify how the data from the vertex buffer object is assigned to it
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) nullptr);

    // Enable the a_color attribute and specify how the data from the vertex buffer object is assigned to it
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat)));
}

figure::figure(const GLfloat* figureCoordinates, int coordinatesAmount, const GLfloat* figureColors)
{
    this->figureCoordinates = new GLfloat[coordinatesAmount];
    this->coordinatesAmount = coordinatesAmount;

    int coordinateCounter = 0;
    int colorCounter = 0;

    // Make the interleaved coordinates and colors of the figure's vertices
    for (int i = 0; i < coordinatesAmount; i += 5)
    {
        this->figureCoordinates[i] = figureCoordinates[coordinateCounter];
        this->figureCoordinates[i + 1] = figureCoordinates[coordinateCounter + 1];
        coordinateCounter += 2;

        this->figureCoordinates[i + 2] = figureColors[colorCounter];
        this->figureCoordinates[i + 3] = figureColors[colorCounter + 1];
        this->figureCoordinates[i + 4] = figureColors[colorCounter + 2];
        colorCounter += 3;
    }
}

void figure::drawFigure(int usage) const
{
    // Bind the vertex array object for the figure
    glBindVertexArray(figureVao);

    // Draw the square depending on usage type
    if (usage == 0)
        glDrawArrays(GL_TRIANGLES, 0, coordinatesAmount / 5);
    else if (usage == 1)
        glDrawArrays(GL_TRIANGLE_STRIP, 0, coordinatesAmount / 5);
    else if (usage == 2)
        glDrawArrays(GL_TRIANGLE_FAN, 0, coordinatesAmount / 5);
}
