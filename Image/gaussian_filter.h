#ifndef GAUSSIAN_FILTER_H
#define GAUSSIAN_FILTER_H

#include <stdlib.h>
#include <SDL.h>

void updateKernel();
Uint32 updatePixel(Uint32 image[]);
void filter(SDL_Surface* image, SDL_Surface* n_image);

#endif
