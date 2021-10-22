#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include "rotate_image.h"

void rotate_image(SDL_Surface *image, double angle)
{
    SDL_Surface *rotation = NULL;
    rotation = rotozoomSurface(image,angle,1.0,2);
    SDL_SaveBMP(rotation, "rotate.bmp");
    SDL_FreeSurface(image);
    SDL_FreeSurface(rotation);
}
