#include <stdio.h>

int main(int arg_counter, char* arg_values[]) {
  printf("argument count: %d\n", arg_counter);
  for (int i = 0; i < arg_counter; i++) {
    printf("arg %d - %s\n", i, arg_values[i]);
  }

  return 0;
}
