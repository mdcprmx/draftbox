#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 100

void scenario_file_doesnt_exist(int file_descr);

int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];
    int file_descr = STDIN_FILENO; // just a fancy way to write "0". yeeah, u can write 0 and get the same result
    ssize_t bytes_length;

    // Use case 1 - with a file //
    if (argc >1 )   // if first argument exists (first argument is always a file name btw) do: 
    {
        file_descr = open(argv[1], O_RDONLY); // tries to open a file
        
        scenario_file_doesnt_exist(file_descr); // if filename is written wrong (or it doesnt exist), prints error
         
        while ((bytes_length = read(file_descr, buffer, BUFFER_SIZE))) // while loop, that works until var "bytes_length" is matching number of chars that are schitanni
        {
        write(STDOUT_FILENO, buffer, bytes_length); // printf basically
        }
    }
    // Use case 1 end. //


    // Use case 2 - return stdin to stdout (text that user wrote in terminal returns to terminal) //
    else
    {
        ssize_t bytes_length;
        read (0, buffer, BUFFER_SIZE);
        write (1, buffer, bytes_length);
    }
    // Use case 2 end. //

    close(file_descr);
    return 0;

}


void scenario_file_doesnt_exist(int file_descr)
{
if (file_descr == -1)   // if file_desc couldn't open anything it will return -1, do:
    
    {
        write(STDERR_FILENO, "File does not exist.\n", 21);   // 21 is number of chars in prev part.
        exit(EXIT_FAILURE);
    }
 
}