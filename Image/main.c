#include <err.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "remove_color.h"
#include "gaussian_filter.h"
#include "rotate_image.h"

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

/*
 * Function: main
 * ----------------------------
 *   will take an image with a sudoku and save the cells as images
 *
 *
 *   returns: 0 I think
 */
int main(void)
{
    init_sdl();
    SDL_Surface *image = loadImage("image.jpg");
    SDL_Surface *n_image = display_image(image);
    SDL_Surface *bimage = image;
    grayscale(image);
    wait_for_keypressed();
    update_surface(n_image, image);
    wait_for_keypressed();
    //SDL_FreeSurface(image);
    filter(image, bimage);
    update_surface(n_image, bimage);
    wait_for_keypressed();
    rotate_image(image,45); // rotates the image at angle 45 degrees
    wait_for_keypressed();
    SDL_FreeSurface(n_image);
    HoughMain(image);
    SDL_FreeSurface(n_image);
    SDL_FreeSurface(bimage);
    printf("la fonction va jusqu'au bout\n");
    return 0;
}
