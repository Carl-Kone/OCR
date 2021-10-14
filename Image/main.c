#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

/*
 * Function: loadImage
 * ----------------------------
 *   loads an image
 *
 *    path: the path to the image
 *
 *   returns: a surface
 */
SDL_Surface *loadImage(char *path)
{
    SDL_Surface *image = NULL;
    image = IMG_Load(path);
    if (!image)
        errx(3, "can't load %s: %s", path, IMG_GetError());
    return image;
}

/*
 * Function: main
 * ----------------------------
 *   will take an image with a sudoku and save the cells as images
 *
 *
 *   returns: 0 I think
 */
int main(int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "Coult not initialize SDL : %s\n", SDL_GetError());
    SDL_Surface *image = loadImage("image.jpg");
    // à finir
}