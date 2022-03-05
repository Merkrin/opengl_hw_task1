//
// Created by Irina Barchuk on 04.03.2022.
//

#include "utils.h"

float utils::intColorToFloat(int color)
{
    return (float) color / MAX_RGB;
}

float utils::intCoordinateToFloat(int coordinate)
{
    return (float) coordinate / HALF_SCREEN_BLOCKS_AMOUNT;
}
