////// HEADER FILE START //////////
#ifndef S21_GREP_LIB
#define S21_GREP_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
    grep_flags opt_switcher = {0};
    funct_args_parser(argc, argv, &opt_switcher);

    FILE *file_ptr;
    file_ptr = funct_file_open(argc, argv);

    funct_processor();
    funct_result_print();

    return EXIT_SUCCESS;
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

            case 'i':

            case 'v':

            case 'c':

            case 'l':

            case 'n':

            default:

        }
    }


}










