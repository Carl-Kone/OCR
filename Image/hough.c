#include <err.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "hough.h"
#include "display.h"

// converts degree to radian
double to_radian(int degree)
{
    return degree * (M_PI / 180.0);
}

/*
  image : sobel image
  accumulator : matrix to store the coordinates of the lines
*/
void houghTransform(SDL_Surface* image, int accumulator[][181])
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
                for(int theta = 0; theta < 181; ++theta)
                {
                    rad = to_radian(theta);
                    rho = x * cos(rad) + y * sin(rad);
                    // +1 in accumulator for each theta for each point
                    accumulator[(int) rho + r_max][theta] += 1;
                }
            }
        }
    }
}

/*
  accumulator : a matrix with the values of rho and teta
  rows : the maximum number of rows of the matrix
  cols : the maximum number of columns of the matrix
  coord : the coordinates of maximum value in accumulator matrix = values of rho and theta for each line of the sudoku => polar coordinates
  -------------
  returns : the len of coord
*/
void coordinates(int accumulator[][181], int rows, int cols)
{
    int max = 0;
    for(int j = 0; j < rows; j++)
    {
        for(int i = 0; i < cols; i++)
        {
            if(accumulator[j][i] > max)
                max = accumulator[j][i];
        }
    }
    for(int y = 0; y < rows; y++)
    {
        for(int x = 0; x < cols; x++)
        {
            if(accumulator[y][x] != max)
            {
                // can I create a array of tuples for the coordinates? or am I supposed to create a structure?
                accumulator[y][x] = 0;
            }
        }
    }
}

/*
  image : the image on which we applied the hough function
  accumulator : a matrix with the values of rho and teta
  rows : the maximum number of rows of the matrix
  cols : the maximum number of columns of the matrix
  coord : coordinates of the maximum value in the accumulator = values of rho and theta are the polar coordinates of a line
  size_c : length of coordinates array

void drawHough(SDL_Surface* image, int** accumulator, int rows, int cols)
{
    int x, y;
    double rho, rad;
    // j'ai plus d'idees, il est 7h je vais me coucher
}
*/

void HoughMain(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    int rho = (int) sqrt(width * width + height * height);
    int w = 181;
    int h = 2*rho+1;
    int accumulator[h][w];
    for(int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {
            accumulator[j][i] = 0;
        }
    }
    houghTransform(image, accumulator);
    //coordinates(accumulator, 2*(rho+1), 181);
    SDL_Surface *bimage = SDL_CreateRGBSurface(0, 180, 2*rho, 32, 0, 0, 0, 0);
    for(int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {
            int val = accumulator[j][i];
            Uint32 pixel = SDL_MapRGB(bimage->format, val, val, val);
            put_pixel(bimage, i, j, pixel);
        }
    }
    SDL_Surface *n_image = display_image(image);
    wait_for_keypressed();
    SDL_FreeSurface(n_image);
    SDL_FreeSurface(bimage);
}
