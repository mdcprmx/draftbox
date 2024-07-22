#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float cel_to_farenheit(float cel);
float cel_to_kelvin(float cel);

int main(int argc, char **argv) {
  float celsius = 0;

  celsius = 21;
  while (celsius < 100) {
    float farenheit = cel_to_farenheit(celsius);
    float kelvin = cel_to_kelvin(celsius);

    printf("celsius %.2f | ", celsius);
    printf("farenheit %.2f | ", farenheit);
    printf("kelvin %.2f\n", kelvin);

    celsius = celsius + 10;
  }

  return EXIT_SUCCESS;
}

float cel_to_farenheit(float cel) {
  cel = cel * 9 / 5 + 32;
  return cel;
}

float cel_to_kelvin(float cel) { return cel + 273.15f; }