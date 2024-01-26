#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 255


void scenario_file_doesnt_exist(int file_descr);
void arguments_parser(int argc, char **argv);


int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];  // 1. create buffer
    int filename_arg = 0;      // 2. create fd (like creating a FILE *f)
    ssize_t bytes_length;      // 3. create  


    // Use case One - with a file //
    // 4.1 - if arguments exist.
    if (argc >1 )   // if first argument exists (first argument is always a file name btw) do: 
    {
        filename_arg = open(argv[1], O_RDONLY); // tries to open a file
        
        scenario_file_doesnt_exist(filename_arg); // if filename is written wrong (or it doesnt exist), prints error
         
        while ((bytes_length = read(filename_arg, buffer, BUFFER_SIZE))) // while loop, that works until var "bytes_length" is matching number of chars that are schitanni
        {
        write(STDOUT_FILENO, buffer, bytes_length); // printf basically
        }
    }
    // Use case One end. //




    // Use case Two - return stdin to stdout (text that user wrote in terminal returns to terminal) //
    // 4.2 - if no arguments are present.
    else
    {
        //ssize_t bytes_length;
        //read (0, buffer, BUFFER_SIZE);
        //write (1, buffer, bytes_length);
        char usr_inpt_buffer[BUFFER_SIZE];
        scanf("%2000[^\n]", usr_inpt_buffer);
        printf("%s\n", usr_inpt_buffer);
    }
    // Use case Two end. //

    close(filename_arg);
    return 0;

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

    while ((option = getopt(argc, argv, "benstAETuv")) != -1)
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