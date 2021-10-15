#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

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

SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
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
    init_sdl();
    SDL_Surface *image = loadImage("image.jpg");
    SDL_Surface *n_image = grayscale(image);
    image = *blackWhite(n_image);
    SDL_SaveBMP(image, "image2.jpg");
    SDL_FreeSurface(image);
    SDL_FreeSurface(n_image);
}
