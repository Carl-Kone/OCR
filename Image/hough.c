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

/*
  accumulator : a matrix with the values of rho and teta
  rows : the maximum number of rows of the matrix
  cols : the maximum number of columns of the matrix
  coord : the coordinates of maximum value in accumulator matrix = values of rho and theta for each line of the sudoku => polar coordinates
  -------------
  returns : the len of coord
*/
int coordinates(int** accumulator, int rows, int cols, int* coord)
{
    int max = 0;
    int i = 0;
    for(size_t j = 0; j < rows; j++)
    {
        for(size_t i = 0; i < cols; i++)
        {
            if(accumulator[j][i] > max)
                max = accumulator[j][i];
        }
    }
    for(size_t y = 0; y < rows; y++)
    {
        for(size_t x = 0; x < cols; x++)
        {
            if(accumulator[j][i] == max)
            {
                // can I create a array of tuples for the coordinates? or am I supposed to create a structure?
                coord[i] = (j, i);
                i++;
            }
        }
    }
    return i;
}

/*
  image : the image on which we applied the hough function
  accumulator : a matrix with the values of rho and teta
  rows : the maximum number of rows of the matrix
  cols : the maximum number of columns of the matrix
  coord : coordinates of the maximum value in the accumulator = values of rho and theta are the polar coordinates of a line
  size_c : length of coordinates array
*/
void drawHough(SDL_Surface* image, int** accumulator, int rows, int cols, int* coord, int size_c) 
{
    int x, y;
    double rho, rad;
    // j'ai plus d'idees, il est 7h je vais me coucher
}
