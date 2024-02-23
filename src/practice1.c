#include <stdio.h>
#include <string.h>
#include "malloc_with_check.c"

int main()
{
    write(1, "start!", 6);
    char *bfr_string = malloc(5069 * sizeof(char));
    strcat(bfr_string, "yeeeeah boiii");
    // malloc_shielded(bfr_string);
    write(STDERR_FILENO, bfr_string, strlen(bfr_string));
    // free_shielded(bfr_string);
    // free(bfr_string);
    return EXIT_SUCCESS;
}