#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];
    int file_descr = STDIN_FILENO;



    if (argc >1 )   // if first argument exists (first argument is always a file name btw) do: 
    {
        file_descr = open(argv[1], O_RDONLY);
        
        if (file_descr == -1)   // if file_desc couldn't open anything it will return -1, do:
        {
            write(STDERR_FILENO, "File does not exist.\n", 21);   // 21 is number of chars in prev part.
            exit(EXIT_FAILURE);
        }
         
    ssize_t bytes_length;

    while ((bytes_length = read(file_descr, buffer, BUFFER_SIZE)))
        {
        write(1, buffer, bytes_length);
        }
    }





    else
    {
        ssize_t bytes_length;
        read (STDIN_FILENO, buffer, BUFFER_SIZE);
        write (STDOUT_FILENO, buffer, bytes_length);
    }

    close(file_descr);
    return 0;

}