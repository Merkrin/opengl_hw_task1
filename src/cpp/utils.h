//
// Created by Irina Barchuk on 04.03.2022.
//

#ifndef TASK1_UTILS_H
#define TASK1_UTILS_H


class utils
{
private:
    constexpr static const float MAX_RGB = 255;
    // The screen has 20x20 blocks to draw
    constexpr static const int HALF_SCREEN_BLOCKS_AMOUNT = 10;

public:
    static float intColorToFloat(int color);
    static float intCoordinateToFloat(int coordinate);
};


#endif //TASK1_UTILS_H
