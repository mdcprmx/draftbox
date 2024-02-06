#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define BUFFER_SIZE 2048

void scenario_open_file(int argc, char **argv);
void scenario_no_arguments();
void funct_file_print(FILE *fname_b);
void funct_arguments_parser(int argc, char **argv);
void check_file_exist(FILE *fname_c);
void funct_file_open(int argc, char **argv, FILE *fname);


//////////////////
//////////////////
int main(int argc, char *argv[])
{
    // if arguments exist.
    if (argc > 1)   
    {
        scenario_open_file(argc, argv);
    }

    // if no arguments.
    else scenario_no_arguments(); 
    
    return 0;
}
//////////////////
//////////////////


void scenario_open_file(int argc, char **argv)
{
    FILE *fname = NULL;
    
    funct_file_open(argc, argv, fname);
    // check_file_exist(fname);
    // funct_arguments_parser(argc, argv);
    funct_file_print(fname);
}

void funct_file_print(FILE *fname)
{
    char ch_buffer;
    ch_buffer = fgetc(fname);
    while (ch_buffer != EOF)
    {
        printf("%c", ch_buffer);
        ch_buffer = fgetc(fname);
    }
    fclose(fname);

}

void funct_file_open(int argc, char **argv, FILE *fname)
{
    for (int i = 0; i < argc ; i++ )    // depends of arg counter.
    {
        fname = fopen(argv[i], "r+");
        if (fname != NULL)              // if fopen returns anything that is not NULL, it means that fopen have opened a file.
        {                               // so we break the cycle. 
            break;                      // tho, there is no scenario for multiple files.. so.. yeah =(
        }
    }
    printf("funct_file_open done!\n");
}

void scenario_no_arguments()
{
    char usr_inpt_buffer[BUFFER_SIZE];

    while (1)
    {
    scanf("%2000[^\n]s", usr_inpt_buffer);
    printf("%s\n", usr_inpt_buffer);
    break; // WIP
   }

}

void check_file_exist(FILE *fname_c)
{
    if (fname_c == 0)  // yeah, not 'NULL', it is '0'
    {
        printf("Error, couldn't open a file\n");
        exit(1);
    }

}


void funct_arguments_parser(int argc,char **argv)
{
    // this struct is used fo SWITCHES ONLY
    struct option long_opt[] = {
        {"show-all",              no_argument, 0, 'A'},
        {"number-nonblank",       no_argument, 0, 'b'},
        {0,                       no_argument, 0, 'e'},
        {"show-ends",             no_argument, 0, 'E'},
        {"number",                no_argument, 0, 'n'},
        {"squeeze-blank",         no_argument, 0, 's'},
        {0,                       no_argument, 0, 't'},
        {"show-tabs",             no_argument, 0, 'T'},
        {0,                       no_argument, 0, 'u'},
        {"show-nonprinting",      no_argument, 0, 'v'},
        {"help",                  no_argument, 0,   0},
        {"version",               no_argument, 0,   0},
        {0,                                 0, 0,   0} // why is that? well.. just. because.
        };


    // small : b e n s t
    //  big  : A E T
    int b_flag = 0;
    int e_flag = 0;
    int n_flag = 0;
    int s_flag = 0;
    int t_flag = 0;
    int A_flag = 0;
    int E_flag = 0;
    int T_flag = 0;
    int u_flag = 0;
    int v_flag = 0;
    int help_flag = 0;
    int version_flag = 0;

    // buffer with flags, for cycle.

    const char *short_opt = "benstAETuv";
    int buffer_w_flag;
    
    while ((buffer_w_flag = getopt_long(argc, argv, short_opt, long_opt, NULL )) != -1)
    {
        switch (buffer_w_flag)
        {
            case 'b':
                b_flag = 1;
                printf("b flag is on\n");
                break;

            case 'e':
                e_flag = 1;
                printf("e flag is on\n");
                break;

            case 'n':
                n_flag = 1;
                printf("n flag is on\n");
                break;
            case 's':
                s_flag = 1;
                printf("s flag is on\n");
                break;

            case 't':
                t_flag = 1;
                printf("t flag is on\n");
                break;

            case 'A':                
                A_flag = 1;
                printf("A flag is on\n");
                break;

            case 'E':
                E_flag = 1;
                printf("E flag is on\n");
                break;

            case 'T':
                T_flag = 1;
                printf("T flag is on\n");
                break;

            case 'u':
                u_flag = 1;
                printf("u flag is on\n");
                break;

            case 'v':
                v_flag = 1;
                printf("v flag is on\n");
                break;

            case '?':
                printf("error, valid flags are [-benstAETuv]");

        }
    }

}