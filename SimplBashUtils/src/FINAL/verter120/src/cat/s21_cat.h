#ifndef S21_CAT_LIB
#define S21_CAT_LIB

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

// this struct is part of getopt.h, it must remain constant
const struct option LONG_OPT[] = {{"number-nonblank", no_argument, 0, 'b'},
                                  {0, no_argument, 0, 'e'},
                                  {"show-ends", no_argument, 0, 'E'},
                                  {"number", no_argument, 0, 'n'},
                                  {"squeeze-blank", no_argument, 0, 's'},
                                  {0, no_argument, 0, 't'},
                                  {"show-tabs", no_argument, 0, 'T'},
                                  {"show-nonprinting", no_argument, 0, 'v'},
                                  {"help", no_argument, 0, 'h'},
                                  {NULL, 0, NULL, 0}};

// struct for flag switching (0 or 1)
typedef struct {
  int b_flag;
  int e_flag;
  int n_flag;
  int s_flag;
  int t_flag;
  int E_flag;
  int v_flag;
} flag_config;

void scenario_open_file(int argc, char **argv);
void scenario_no_arguments();
FILE *funct_file_open(int argc, char **argv);
void funct_arguments_parser(int argc, char **argv, flag_config *opt_switcher);
void funct_file_print(FILE *fname, flag_config *opt_state);
void check_memory_allocation(char **ofu_buffer);
void check_file_exist(FILE *fname_c);
void text_squeeze(FILE *fname_b);
void text_show_dollar();
void error_usage_print();
void error_help_print();

#endif  // S21_CAT_LIB