#include "s21_string.h"
// why use const? for easier understanding - be it for reader or coder himself.

// search. it looks for single char in line.
void *s21_memchr(const void *line, int ch, s21_size_t line_length)
{
    const unsigned char *pointer = line;
    while(line_length = line_length - 1)
    {
        if (*pointer == (unsigned char)ch) // forced cast to unsigned char
        {
            return (void*)pointer; // forced cast to void (just to be sure)
        }
    }
    // if something went wrong, returns NULL
    return S21_NULL;
} 

// memory compare. it compares bytes, not strings (as 'strcmp' does)
void *s21_memcmp(const void *first_line, const void *second_line, s21_size_t bytes_length)
{
    const unsigned char *ptr1 = first_line;
    const unsigned char *ptr2 = second_line;

    while (bytes_length--) // aka, while bytes_length is positive keep on going
    {
        if (*ptr1 != *ptr2)
        {
            return *ptr1 - *ptr2; // it will return negative value, meaning first ptr is smaller than second
        }
        ptr1++; 
        ptr1++;
    }
    const int IDENTICAL = 0; // well, bruh.
    return IDENTICAL;
}
