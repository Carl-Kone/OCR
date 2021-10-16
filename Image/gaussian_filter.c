#include <err.h>
#include <math.h>
#include "pixel_operations.h"
#include "gaussian_filter.h"

float kernel[] = {2, 4, 5, 4, 2, 4, 9, 12, 9, 4, 5, 12, 15, 12, 5, 4, 9, 12, 9, 4, 2, 4, 5, 4, 2}; 
size_t size_k = 25;
float maxval = 160;

// updates the kernel with its exact values 
void updateKernel()
{
    for(int i = 0; i < size_k; i++)
    {
        kernel[i] += kernel[i] * (float)1/159;
    }
}

/*
 * Function: updatePixel
 * ----------------------------
 *   takes a list of pixels of the image and finds a new pixel value
 *
 *    image[] = pixel values
 *    .....
 *
 *   returns: a new pixel value 
 */
Uint32 updatePixel(Uint32 image[])
{
    Uint32 pixel = 0;
    // multiplication of the values of the pixels with the kernel values
    for(i = 0; i < size_k; i++)
    {
        pixel += (image[i] * kernel[i]);
    }
    // average =  new value of pixel
    pixel = pixel/maxval;
    return pixel;
}

/*
 * Function: Filter
 * ----------------------------
 *   Applies the Gaussian filter to an image
 *
 *    image : the surface of an image
 *    .....
 *
 *   returns: should return the image with the noise removed
 */
SDL_Surface* Filter(SDL_Surface* image)
{
    SDL_Surface* n_image = image;
    int width = image->w;
    int height = image->h;
    Uint32 pixel;
    Uint32 pixels[25];
    int i;
    for(int y = 2; y < height-2; y++)
    {
        for(int x = 2; x < width-2; x++)
        {
            i = 0;
            for(int b = y-2; b <= y+2; b++)
            {
                for(int a = x-2; a <= x+2; a++)
                {
                    pixels[i] = get_pixel(image, a, b);
                }
            }
            pixel = updatePixel(pixels);
            put_pixel(n_image, x, y, pixel);
        }
    }
    return n_image;
}