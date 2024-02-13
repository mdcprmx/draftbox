////// HEADER FILE START //////////
#ifndef S21_GREP_LIB
#define S21_GREP_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <getopt.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

const struct option LONG_OPT[] = 
{
    {"ignore-case",         no_argument, NULL, 'i'},
    {"regexp",              required_argument, NULL, 'e'},
    {"invert-match",        no_argument, NULL, 'v'},
    {"files-witch-matches", no_argument, NULL, 'l'},
    {"count",               no_argument, NULL, 'c'},
    {"line-number",         no_argument, NULL, 'n'},
    {"no-filename",         no_argument, NULL, 'h'},
    {"no-messages",         no_argument, NULL, 's'},
    {"file",                required_argument, NULL, 'f'},
    {"only-matching",       no_argument, NULL, 'o'},
    {NULL, 0, NULL, 0}
};

typedef struct {
    int e_flag;    // pattern 
    int i_flag;    // ignore case sensetivity
    int v_flag;    // invert match
    int c_flag;    // count
    int l_flag;    // output only matching files
    int n_flag;    // prefix each line of output with number
    int h_flag;    // supress filename
    int f_flag;    // obtains patterns from FILE
    int s_flag;    // hide error messages
    int o_flag;    // only matching string part print 
} grep_flags;



#endif // S21_GREP_LIB
////// HEADER FILE END ////////////


// soo we are doing grep. 
// with flags: -e, -i, -v, -c, -l, -n
// only use libraries pcre or regex (what?!)

// soo.. as usual. I just have to.. write grep. essentially
// how tho? that's.. a good question!

// additional quest: add support for flags -h, -s, -f, -o
// additional ultra quest: just dont bother, I'll never be able to do it

// soo.. basic layout is like that:
// 1 - 

int main(int argc, char **argv)
{
    if (argc > 2)
    {
    char buffer_pattern[BUFFER_SIZE] = " ";

    grep_flags opt_state = {0};
    opt_state = funct_args_parser(argc, argv, opt_state, buffer_pattern);
    scenario_grep_start(argc, argv, opt_state);
    }

    else
    {
        error_print();
    }

    return EXIT_SUCCESS;
}

void scenario_grep_start(int argc, char  **argv, grep_flags opt_status)
{

    while (1)
    {
    funct_file_open(argc, argv);
    funct_grep_logic(argc, argv);

    }

}

FILE funct_file_open(int argc, char **argv)
{
  

}

grep_flags funct_args_parser(int argc, char **argv, grep_flags *opts, char buffer_str)
{
    const char *SHORT_OPT = ":e:ivclnsf:ho";

    int buffer_ch = 0;
    buffer_ch = getopt_long(argc, argv, SHORT_OPT, LONG_OPT, 0);
    
    while(buffer_ch != -1)
    {
        switch (buffer_ch) {
            case 'e':
            printf("flag e is ON!\n");
            opts->e_flag = 1;
            char max_length[] = BUFFER_SIZE - strlen(buffer_ch);
            strncat(buffer_str, optarg, max_length);
            strcat(buffer_str, "|");
            break;

            case 'i':
            printf("flag i is ON!\n");
            opts->i_flag = 1;
            break;

            case 'v':
            printf("flag v is ON!\n");
            opts->v_flag = 1;

            case 'c':
            printf("flag c is ON!\n");
            opts->c_flag = 1;

            case 'l':
            printf("flag l is ON!\n");
            opts->l_flag = 1;

            case 'n':
            printf("flag n is ON!\n");
            opts->n_flag = 1;

            default:
            //error_print(); // WIP
        }
    }

    return opts;
}

void error_print()
{
    printf("Error, correct flags are [e, i, v, c, l, n, h, s, o]\n");
    exit(EXIT_FAILURE);
}







