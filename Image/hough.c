#include <err.h>
#include <math.h>
#include "pixel_operations.h"
#include "hough.h"

// converts degree to radian
double to_radian(int degree)
{
    return degree * (M_PI / 180.0);
}

/*
  image : sobel image
  accumulator : matrix to store the coordinates of the lines
*/
int houghTransform(SDL_Surface* image, int** accumulator)
{
    int width = image->w;
    int height = image->h;
    int r_max = (int) sqrt(width * width + height * height);
    double rho, rad;
    Uint32 pixel;
    Uint8 r, g, b;
    // iterate through the pixels of the image
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            // get the color of the pixel
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            // enter if the pixel is white
            if(r == 255)
            {
                for(int theta = 0; theta < 180; ++theta)
                {
                    rad = to_radian(theta);
                    rho = x * cos(rad) + y * sin(rad);
                    accumulator[(int) rho + r_max][theta] += 1;
                }
            }
        }
    }
    return r_max;
}
