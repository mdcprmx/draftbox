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

// const char *SHORT_OPT = ":ie:vlcnhsf:o";

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


void scenario_grep_start(int argc, char  **argv);
FILE funct_file_open(int argc, char **argv);
grep_flags funct_args_parser(int argc, char **argv, grep_flags *opts, char *bpattern_a);
void job_file_pattern(char *path_to_file, char* pattern_b);
void check_file_exist(FILE *fname_a);
void check_ef_flags(char *pattern_c, char **argv, grep_flags *opts_b, int cntr_a);
void error_print();




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
    scenario_grep_start(argc, argv);
    }

    else
    {
        printf("second scenario went off\n"); // DELETE ME LATER
        error_print();
    }

    return EXIT_SUCCESS;
}

/////////////////////////////////////////////
/////////////////////////////////////////////

void scenario_grep_start(int argc, char  **argv)
{
    // 0 - initialization
    char buffer_pattern[BUFFER_SIZE] = "";
    grep_flags opt_status = {0};
    
    // 1 - parsing
    opt_status = funct_args_parser(argc, argv, &opt_status, buffer_pattern);

    // 2 - grep logic
    int counter = 1;
    printf("counter is: %d", counter); // DELETE ME LATER
    check_ef_flags(buffer_pattern, argv, &opt_status, counter);

    int number_of_files = 0;
    while (1)
    {
        counter++;
        if ()
    }

    

    while (1)
    {
    funct_file_open(argc, argv);
    // funct_grep_logic(argc, argv);
    }
}

FILE funct_file_open(int argc, char **argv)
{



}



void check_ef_flags(char *pattern_c, char **argv, grep_flags *opts_b, int cntr_a)
{
    if (opts_b->e_flag == 0 && opts_b->f_flag == 0)
    {
        strncpy(pattern_c, argv[optind], BUFFER_SIZE);
    }

    if (pattern_c[strlen(pattern_c) - 1] == '|')
    {
        pattern_c[strlen(pattern_c) - 1] == '\0';
    }

    if (!opts_b->e_flag && !opts_b->f_flag)
    {
        cntr_a = 2;
        printf("counter is now: %d", cntr_a); // DELETE ME LATER
    }
}

int check_argument_or_name(char *fname)
{
    const int NOT_A_FILE = 0;
    const int IS_FILE = 1;
    const int FLAG_EF_IS_ON = 2;

    int result = 1;

    if (strstr(fname))





    return result;
}

grep_flags funct_args_parser(int argc, char **argv, grep_flags *opts, char pattern_a[BUFFER_SIZE])
{
    const char *SHORT_OPT = ":ie:vlcnhsf:o";
    const int GETOPT_END = -1;

    int flag_reader = 0;
    flag_reader = getopt_long(argc, argv, SHORT_OPT, LONG_OPT, 0);
    
    while((flag_reader = getopt_long(argc, argv, SHORT_OPT, LONG_OPT, 0)) != GETOPT_END)
    {
        switch (flag_reader) {
            case 'e':
            printf("flag e is ON!\n");
            opts->e_flag = 1;
            strncat(pattern_a, optarg, BUFFER_SIZE - strlen(pattern_a));
            strcat(pattern_a, "|");
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

            case 'h':
            opts->h_flag = 1;
            printf("flag h is ON!\n");
            break;

            case 's':
            opts->s_flag = 1;
            printf("flag s is ON!\n");
            break;

            case 'f':
            opts->f_flag = 1;
            printf("flag f is ON!\n");
            job_file_pattern(optarg, pattern_a);
            break;

            case 'o':
            opts->o_flag = 1;
            break;

            default:
            //error_print(); // WIP
        }
    }

    return *opts;
}

void job_file_pattern(char *path_to_file, char* pattern_b)
{
    FILE *fname;
    fname = NULL;

    size_t length_pattern;
    length_pattern = strlen(pattern_b);  // length in bytes

    fname = fopen(path_to_file, "r");
    check_file_exist(fname);

    int buffer_ch;
    size_t loop_i;
    loop_i = 0;
    while (length_pattern < BUFFER_SIZE && (buffer_ch = fgetc(fname) != EOF))
    {
        if ((buffer_ch == 10 || buffer_ch == 13) && length_pattern > 1 && pattern_b[length_pattern - 1] != '|')
        {
            pattern_b[length_pattern++] = '|';
        }

        if (buffer_ch != 10 && buffer_ch != 13) 
        {
            pattern_b[length_pattern++] = buffer_ch;
        }

    loop_i++;
    }

    if (pattern_b[length_pattern -1] != '|' && length_pattern < BUFFER_SIZE)
    {
        pattern_b[length_pattern] = '|';
    }

    fclose(fname);
}

void check_file_exist(FILE *fname_a)
{
    if (fname_a == NULL)
    {
        printf("Error, file not found\n");
        exit(EXIT_FAILURE); // or should it be free and then exit? hmm..
    }
}

void error_print()
{
    printf("Error, correct flags are [-eivclnhso]\n");
    exit(EXIT_FAILURE);
}







