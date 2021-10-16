#include <math.h>
#include <stdio.h>

float kernel[] = {2, 4, 5, 4, 2, 4, 9, 12, 9, 4, 5, 12, 15, 12, 5, 4, 9, 12, 9, 4, 2, 4, 5, 4, 2}; 
size_t size_k = 25;
float maxval = 0;
float *max = &maxval;

void updateKernel(float array[], size_t t)
{
    for(int i = 0; i < t; i++)
    {
        array[i] += array[i] * (float)1/159;
        *max += array[i];
    }
}

int main()
{
    printf("value of maxval = %f\n", *max);
    updateKernel(kernel, size_k);
    for(int i = 0; i < size_k; i++)
        printf("%f\n", kernel[i]);
    printf("value of maxval = %f\n", *max);
    float f = (float) 1/159;
    printf("value should be %f\n", 159 + f * 159);
    return 0;
}