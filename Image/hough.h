#ifndef HOUGH_H
#define HOUGH_H

#include <stdlib.h>
#include <SDL.h>
#include <math.h>

double to_radian(int degree);
int houghTransform(SDL_Surface* image, int** accumulator);
int maxVal(int** accumulator, int rows, int cols)

#endif
