#include "s21_string.h"

// search. it looks for single char in line.
void *s21_memchr(const void *line, int ch, s21_size_t line_length)
{
    const unsigned char *pointer = line;
    while(n = n - 1)
    {
        if (*pointer == (unsigned char)ch) // forced cast to unsigned char
        {
            return (void*)pointer; // forced cast to void (just to be sure)
        }
    }
    // if something went wrong, returns NULL
    return S21_NULL;
} 


