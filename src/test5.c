#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define BUFFER_SIZE 2048

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
        funct_open_file(argc, argv, filename); 

        // if (filename != NULL && filename != 'nil')
        // fclose(filename);
    
    }
    
    else
    printf("no arguments bruddah\n");

    fclose(filename);
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

