#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char **argv)
{
    //int a = 5;
    //printf("printing a %d\n", a);
    float celsius = 0;
    float farenheit = 0;
    float kelvin = 0;

    celsius = 21;
    farenheit = celsius * 9 / 5 + 32;
    kelvin = celsius +273.15f;

    printf("celsius %.2f\n", celsius);
    printf("farenheit %.2f\n", farenheit);
    printf("kelvin %.2f\n", kelvin);


    return EXIT_SUCCESS;
}