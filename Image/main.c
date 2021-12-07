#include <err.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "display.h"
#include "remove_color.h"
#include "gaussian_filter.h"
#include "sobel_filter.h"
#include "hough.h"

char *preprocessing(SDL_Surface *image)
{
    /*
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
    SDL_Surface *image = loadImage(path);
    */
    int width = image->w;
    int height = image->h;
    grayscale(image);
    SDL_Surface *bimage = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    filter(image, bimage);
    Sfilter(bimage, image);
    char *path2 = "image_filter.bmp";
    if(SDL_SaveBMP(image, path2) != 0)
    {
        // Error saving bitmap
        printf("SDL_SaveBMP failed: %s\n", SDL_GetError());
    }
    return path2;
}
/*
int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
    SDL_Surface *image = loadImage("carre10.jpg");
    int width = image->w;
    int height = image->h;
    SDL_Surface *bimage = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_Surface *n_image = display_image(image);
    grayscale(image);
    if(SDL_SaveBMP(image, "image2.bmp") != 0)
    {
        // Error saving bitmap
        printf("SDL_SaveBMP failed: %s\n", SDL_GetError());
    }
    wait_for_keypressed();
    update_surface(n_image, image);
    wait_for_keypressed();
    filter(image, bimage);
    update_surface(n_image, bimage);
    wait_for_keypressed();
    Sfilter(bimage, image);
    //SDL_FreeSurface(image);
    //filter(image, bimage);
    //update_surface(n_image, bimage);
    //wait_for_keypressed();
    update_surface(n_image, image);
    wait_for_keypressed();
    SDL_FreeSurface(n_image);
    HoughMain(image);
    SDL_FreeSurface(image);
    SDL_FreeSurface(bimage);
    printf("la fonction va jusqu'au bout\n");
    return 0;
}
*/
