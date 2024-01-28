#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

#define BUFFER_SIZE 2048


void scenario_file_print(int filename);
int funct_open_file(int argc, char **argv, FILE* fname);


//////////////////
//////////////////
int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];
    FILE *filename;

    // if arguments exist.
    if (argc > 1)   // if second argument exists (first(0th) argument is always an executable name btw) do: 
    {
        // funct_arguments_parser(argc, argv);
        funct_open_file(argc, argv, filename); // tries to open a file // btw, FIX THIS! IT MUST LOOK FOR FILENAME, not just take argv[1], cuz there could be a flag
        // scenario_file_print(filename);
        
    }
    
    else
    printf("no arguments bruddah\n");

    return 0;
}
//////////////////
//////////////////



int funct_open_file(int argc, char **argv, FILE* fname)
{
    for (int i = 1; i < argc ; i++ ) // start from 1, not 0. depends of arg counter.
    {
        printf("arg string is: %s\n", argv[i]);
        fname = fopen(argv[i], "r"); // is trying to open a string name (sorting thru)
        printf("current file name is: %p\n", fname);
        if (fname != NULL)           // if it couldn't open, it means that it have read a flag
        {                            // so it reads until fname returns not null
            break;
        }
    }

}


// void scenario_file_print(int filename)
// {  
//     ssize_t bytes_length;
//     while ((bytes_length = read(filename, buffer, BUFFER_SIZE))) // function "read" returns number of bytes that were read.
//     {
//         write(STDOUT_FILENO, buffer, bytes_length);                  // so it writes the exact number of bytes that func "read" returned.
//     }
//     close(filename);
// }


