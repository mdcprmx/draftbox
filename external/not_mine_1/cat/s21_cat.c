
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VALID_OPTS "bnsetvET"

// Options storage
struct arguments {
  bool b; // numbers only non-empty lines
  bool n; // number all output lines
  bool s; // squeeze multiple adjacent blank lines
  bool e; // but also display end-of-line characters as $, implies -v
  bool t; // but also display tabs as ^I, implies -v
  bool v; // non printing symbols
  bool E; // but also display end-of-line characters as $
  bool T; // but also display tabs as ^I
};

// Recieve options
static const struct option is_opts[] = {
    {"number-nonblank", optional_argument, 0, 'b'},
    {"number", optional_argument, 0, 'n'},
    {"squeeze-blank", optional_argument, 0, 's'},
    {"", optional_argument, 0, 'e'},
    {"", optional_argument, 0, 't'},
    {"", optional_argument, 0, 'v'},
    {"", optional_argument, 0, 'E'},
    {"", optional_argument, 0, 'T'},
    {0, 0, 0, 0}};

void job(FILE *file, int *num_line, struct arguments *opt_stor, char *last);
int non_printing_symbols(int sym);
struct arguments set_options(int argc, char *const argv[], int *option_index);

int main(int argc, char *argv[]) {
  // Main function
  int option_index = 0;
  int num_line = 0;
  char last = '\n';

  struct arguments opt_stor = set_options(argc, argv, &option_index);

  // Get file name from options and job
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      // strcpy(file_name, argv[i]);
      // Open file
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        printf("Error opening the file.\n");
      } else {
        job(file, &num_line, &opt_stor, &last);
      }
    }
  }
  return 0;
}

struct arguments set_options(int argc, char *const argv[], int *option_index) {
  // Set options
  struct arguments opt_stor = {0};
  int opt;
  while ((opt = getopt_long(argc, argv, VALID_OPTS, is_opts, option_index)) !=
         -1) {
    switch (opt) {
    case 'b':
      opt_stor.b = true;
      break;
    case 'n':
      opt_stor.n = true;
      break;
    case 's':
      opt_stor.s = true;
      break;
    case 'e':
      opt_stor.e = true;
      opt_stor.v = true;
      break;
    case 't':
      opt_stor.t = true;
      opt_stor.v = true;
      break;
    case 'v':
      opt_stor.v = true;
      break;
    case 'E':
      opt_stor.e = true;
      break;
    case 'T':
      opt_stor.t = true;
      break;
    default:
      // Invalid option
      printf("Invalid option\n");
      exit(EXIT_SUCCESS);
      break;
    }
  }
  return opt_stor;
}

void job(FILE *file, int *num_line, struct arguments *opt_stor, char *last) {
  // Show result
  char c;
  bool empty_line = '\n';
  while ((c = fgetc(file)) != EOF) {
    // Pass empty line
    if (opt_stor->s && c == *last && c == '\n' && empty_line)
      continue;
    else if (opt_stor->s && c != *last && *last == '\n' && empty_line)
      empty_line = false;
    // In end each line add $ symbols
    if (opt_stor->e && c == '\n' && *last != '\n')
      printf("$");
    // Numbered line
    if (opt_stor->b && c != '\n' && *last == '\n') {
      *num_line = *num_line + 1;
      printf("%6d\t", *num_line);
    } else if (opt_stor->n && !opt_stor->b && *last == '\n') {
      *num_line = *num_line + 1;
      printf("%6d\t", *num_line);
    }
    if (opt_stor->s && c == *last && c == '\n' && !empty_line) {
      empty_line = true;
    }
    // More 1 empty line, print & in e opt
    if (opt_stor->e && c == *last && c == '\n' && *last != '$')
      printf("$");
    // Any TAB changed to ^I symbols
    if (opt_stor->t && c == '\t')
      printf("^I");
    else {
      // Print non printing symbols, use ^ and M- notation
      if (opt_stor->v)
        c = non_printing_symbols(c);
      // Print remaining symbols
      printf("%c", c);
    }
    *last = c;
  }
}

int non_printing_symbols(int c) {
  // Print non printing symbols, use ^ and M- notation
  if (c < 0) {
    printf("M-");
    if (c + 256 >= 128 + 32) {
      if (c + 256 < 128 + 127) {
        c = c + 256 - 128;
      } else {
        printf("^?");
        c = '\0';
      }
    } else {
      printf("^");
      c = c + 256 - 128 + 64;
    }
  } else if (c == 127) {
    printf("^");
    c = 127 - 64;
  } else if (c >= 0 && c < 32 && c != '\n' && c != '\t') {
    printf("^");
    c = c + 64;
  }
  return c;
}
