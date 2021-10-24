#ifndef SOBEL_FILTER_H
#define SOBEL_FILTER_H

#include <stdlib.h>
#include <SDL.h>
#include <math.h>

int gradient(int x, int y);
int updatePixel2(Uint8 pixels[]);
void Sfilter(SDL_Surface* image, SDL_Surface* n_image);

#endif
