#include "pixel_operations.h"

// Uint32 pixel = get_pixel(image_surface, x, y);

// put_pixel(image_surface, x, y, pixel);

// Uint8 r, g, b;
// SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

// Uint32 pixel = SDL_MapRGB(image_surface->format, r, g, b);

// int width = image_surface->w;

// int height = image_surface->h;

/*
 * Function: grayscale
 * ----------------------------
 *   takes a surface and returns it in grayscale
 *
 *    image : the image of the sudoku loaded in a surface
 *    .....
 *
 *   returns: the surface in grayscale 
 */
SDL_Surface* grayscale(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;
    Uint32 pixel;
    Uint8 r, g, b, av;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            av = 0.3 * r + 0.59 * g + 0.11 * b;
            r = av;
            g = av;
            b = av;
            pixel = SDL_MapRGB(image->format, r, g, b);
            put_pixel(image, x, y, pixel);
        }
    }
    return image;
}

/*
 * Function: blackWhite
 * ----------------------------
 *   takes and image in grayscale and returns it in black and white
 *
 *    image = the surface from the image in grayscale
 *
 *   returns: the surface of the image in black and white
 */
SDL_Surface* blackWhite(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;
    Uint32 pixel;
    Uint8 r, g, b, av;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if(r < 128)
            {
                r = 0;
                g = 0;
                b = 0;
            }
            else 
            {
                r = 255;
                g = 255;
                b = 255;
            }
            pixel = SDL_MapRGB(image->format, r, g, b);
            put_pixel(image, x, y, pixel);
        }
    } 
    return image;  
}