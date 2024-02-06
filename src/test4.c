#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048

int main(int arg_cntr, char **arg_vctr) {
  FILE *input_file;
  FILE *exit_file;

  fopen(input_file, arg_vctr[1], 'r');
  if (input_file == NULL) {
    printf("erro bruh\n");
    exit(1);
  }

  else {
  }

  return 0;
}