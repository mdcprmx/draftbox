#ifndef S21_CAT_LIB
#define S21_CAT_LIB

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define BUFFER_SIZE 2048

void scenario_open_file(int argc, char **argv);
void scenario_no_arguments();
void check_file_exist(FILE *fname_c);
void funct_file_print(FILE *fname_b);

// this struct is part of getopt.h, it must remain constant
const struct option long_opt[] = 
{
{"number-nonblank",       no_argument, 0, 'b'},
{0,                       no_argument, 0, 'e'},
{"show-ends",             no_argument, 0, 'E'},
{"number",                no_argument, 0, 'n'},
{"squeeze-blank",         no_argument, 0, 's'},
{0,                       no_argument, 0, 't'},
{"show-tabs",             no_argument, 0, 'T'},
{"show-nonprinting",      no_argument, 0, 'v'},
{0,                                 0, 0,   0}
};


typedef struct {
    int b_flag;
    int e_flag;
    int n_flag;
    int s_flag;
    int t_flag;
    int E_flag;
    int T_flag;
    int v_flag;
} flag_config;

void funct_arguments_parser(int argc, char **argv, flag_config *opt_switcher);

#endif // S21_CAT_LIB