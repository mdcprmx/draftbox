#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

#define BUFFER_SIZE 1024

void scenario_file_doesnt_exist(int file_descr);
void scenario_no_arguments();
void arguments_parser(int argc, char **argv);



//////////////////
//////////////////
int main(int argc, char *argv[])
{
    const char *options_short = "benstAETuv";
    char buffer[BUFFER_SIZE];  
    int filename_arg = 0;

    // Use case One - with a file //
    // if arguments exist.
    if (argc > 1)   // if second argument exists (first argument is always an executable name btw) do: 
    {
        arguments_parser(argc, argv);
        filename_arg = open(argv[1], O_RDONLY); // tries to open a file
        scenario_file_doesnt_exist(filename_arg); // if filename is written wrong (or it doesnt exist), prints error
        
        ssize_t bytes_length;
        while ((bytes_length = read(filename_arg, buffer, BUFFER_SIZE))) // while loop, that works until var "bytes_length" is matching number of chars that are schitanni
        {
        write(STDOUT_FILENO, buffer, bytes_length); // printf basically
        }

    close(filename_arg);
    }
    // Use case One end. //




    // Use case Two - return stdin to stdout (text that user wrote in terminal returns to terminal) //
    // if no arguments are present.
    else
    {
        scenario_no_arguments();
    }
    // Use case Two end. //

    return 0;

}
//////////////////
//////////////////



void scenario_no_arguments()
{
    char usr_inpt_buffer[BUFFER_SIZE];
    
    while (1)
    {
    scanf("%255[^\n]", usr_inpt_buffer);
    printf("%s\n", usr_inpt_buffer);
    }
}



void scenario_file_doesnt_exist(int file_descr)
{
if (file_descr == -1)   // if file_desc couldn't open anything it will return -1, do: 
    {
        write(2, "File does not exist.\n", 21);   // 21 is number of chars in prev part.
        exit(EXIT_FAILURE);
    }
}


void arguments_parser(int argc,char **argv)
{

    static struct cat_flags options_long[] = {
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
        };


    int option = 0;
    
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

    //  additional flags, not rly need to do them.
    //  list : u v help version
    int u_flag = 0;
    int v_flag = 0;
    int help_flag = 0;
    int version_flag = 0;

    while ((option = getopt_long(argc, argv, "benstAETuv")) != -1)
    {
        switch (option)
        {
            case 'b':

            case 'e':

            case 'n':
            
            case 's':

            case 't':

            case 'A':

            case 'E':

            case 'T':

            case 'u':

            case 'v':

        

        }
    }

}