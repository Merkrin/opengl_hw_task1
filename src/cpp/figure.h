//
// Created by Irina Barchuk on 04.03.2022.
//

#ifndef TASK1_FIGURE_H
#define TASK1_FIGURE_H
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <iostream>
#include <cmath>

#include "files.h"
#include "opengl.h"

#include "opengl.h"

class figure
{
private:
    GLfloat * figureCoordinates;
    int coordinatesAmount;

    GLuint figureVao{};

public:
    figure(const GLfloat * figureCoordinates, int coordinatesAmount, const GLfloat * figureColors);

    void setupFigure();

    void drawFigure(int usage) const;

    ~figure(){
        delete figureCoordinates;
    }
};


#endif //TASK1_FIGURE_H
