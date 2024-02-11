////// HEADER FILE START //////////
#ifndef S21_GREP_LIB
#define S21_GREP_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <getopt.h>

#define BUFFER_SIZE 2048

typedef struct {
    int e_flag;
    int i_flag;
    int v_flag;
    int c_flag;
    int l_flag;
    int n_flag;
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
    grep_flags opt_switcher = {0};

    opt_switcher = funct_args_parser(argc, argv, opt_switcher);
    scenario_grep_start(argc, argv, opt_switcher);
    }

    return EXIT_SUCCESS;
}

void scenario_grep_start(int argc,char  **argv, grep_flags opt_stat)
{  
    funct_file_open(argc, argv); 
    funct_grep_logic(argc, argv);


}


FILE funct_file_open(int argc, char **argv)
{
  

}

grep_flags funct_args_parser(int argc, char **argv, grep_flags opt_switcher)
{
    const char *SHORT_OPT = "e:ivcln";

    int buffer_ch;
    buffer_ch = getopt(argc, argv, SHORT_OPT);
    
    while(buffer_ch != -1)
    {
        switch (buffer_ch) {
            case 'e':
            printf("flag e is ON!\n");
            opt_switcher.e_flag = 1;
            break;

            case 'i':
            printf("flag i is ON!\n");
            opt_switcher.i_flag = 1;
            break;

            case 'v':
            printf("flag v is ON!\n");
            opt_switcher.v_flag = 1;

            case 'c':
            printf("flag c is ON!\n");
            opt_switcher.c_flag = 1;

            case 'l':
            printf("flag l is ON!\n");
            opt_switcher.l_flag = 1;

            case 'n':
            printf("flag n is ON!\n");
            opt_switcher.n_flag = 1;

            default:
            //error_print(); // WIP
        }
    }

    return opt_switcher;
}

void error_print()
{
    printf("Error, correct flags are [e, i, v, c, l, n]\n");
    exit(EXIT_FAILURE);
}







