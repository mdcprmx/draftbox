#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int mathemagic(int a, int b)
{
  int a_copy = a;
  int b_copy = b;
  int result = 0;

  result = a_copy + b_copy;

return (int)result;
}

#define MOSHI 5

int main(int argc, char **argv) {

  int buffer = mathemagic(5, 4);
  printf("\nour result is %d\n", buffer);

  return EXIT_SUCCESS;
}