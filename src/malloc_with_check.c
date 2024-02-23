#include "malloc_with_check.h"

void malloc_shielded(char *buffer)
{
    buffer = malloc(sizeof(char) * 2048);
    if (buffer == NULL)
    {
        error_malloc_shielded();
    }
}

void error_malloc_shielded()
{
    const int print_to_stdout = 1;
    const char *ERROR_MSG = "Error, malloc failed!";
    write (print_to_stdout, ERROR_MSG, strlen(ERROR_MSG)); 
    // write (1, "Error bruhh", 11); // alternative
}

void free_shielded(char *buffer)
{
    if (buffer != NULL)
    free(buffer);
    buffer = NULL;
}

void calloc_shielded(char *buffer)
{
    buffer = calloc(1, sizeof(char) * 2048);
    if (buffer == NULL)
    {
        error_malloc_shielded();
    }
}