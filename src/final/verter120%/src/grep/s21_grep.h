#ifndef S21_GREP_LIB
#define S21_GREP_LIB

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 2048
#define YES 1
#define NO 0

const struct option LONG_OPT[] = {
    {"ignore-case", no_argument, NULL, 'i'},
    {"regexp", required_argument, NULL, 'e'},
    {"invert-match", no_argument, NULL, 'v'},
    {"files-witch-matches", no_argument, NULL, 'l'},
    {"count", no_argument, NULL, 'c'},
    {"line-number", no_argument, NULL, 'n'},
    {"no-filename", no_argument, NULL, 'h'},
    {"no-messages", no_argument, NULL, 's'},
    {"file", required_argument, NULL, 'f'},
    {"only-matching", no_argument, NULL, 'o'},
    {NULL, 0, NULL, 0}};

typedef struct {
  int e_flag;  // pattern
  int i_flag;  // ignore case sensetivity
  int v_flag;  // invert match
  int c_flag;  // count
  int l_flag;  // output only matching files
  int n_flag;  // prefix each line of output with number
  int h_flag;  // supress filename
  int f_flag;  // obtains patterns from FILE
  int s_flag;  // hide error messages
  int o_flag;  // only matching string part print
} grep_flags;

typedef struct {
  int line;
  int n_logic;
  int name;
} guards;

int scenario_grep_start(int argc, char **argv);
void funct_grep(grep_flags *opts, char pattern_d[BUFFER_SIZE], char *filename_b,
                int num_of_files);
void funct_args_parser(int argc, char **argv, grep_flags *opts,
                       char *pattern_a);
void job_file_pattern(char *path_to_file, char *pattern_b);
int check_argument_or_name(char *filename_a);
void check_file_exist(FILE *fname_a);
void check_ef_flags(char *pattern_c, char **argv, grep_flags *opts_b);
void util_guards_reset(guards *received_struct);
void error_print();

#endif  // S21_GREP_LIB