#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define BFR_SIZE 1024

int main()
{
    write(1, "\npractice boii\n", 16);

    char *stringg = "\nI love turtles!\n";
    write(1, stringg, strlen(stringg));

    char line_msg[BFR_SIZE] = "\nlalala, dance dance revolution!\n";
    write(STDOUT_FILENO, line_msg, strlen(line_msg));

    char *error_msg = "\nBruh, error!\n";
    write(STDERR_FILENO, error_msg, strlen(error_msg));

    write(1, "\nd\n", 3);

    // opening a file thru FD, file descriptor, using lib <fcntl.h>
    char *file_name = "ayo.txt";
    int fd = 0;
    fd = open(file_name, O_RDONLY, O_WRONLY);
    if (fd == -1)
    {
        perror("write");
        return EXIT_FAILURE;
    }
    char to_file_msg[BFR_SIZE] = "ayayo?";
    write(fd, to_file_msg, strlen(to_file_msg));


    return EXIT_SUCCESS;
}