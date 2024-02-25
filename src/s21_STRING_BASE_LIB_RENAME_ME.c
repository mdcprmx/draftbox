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
    // if char was not found returns null
    return S21_NULL;
} 

// memory compare. it compares bytes, not strings (as 'strcmp' does)
// void *s21_memcmp(const void *first_line, const void *second_line, s21_size_t bytes_length)
// {
//     const unsigned char *ptr1 = first_line;
//     const unsigned char *ptr2 = second_line;

//     while (bytes_length--) // aka, while bytes_length is positive keep on going
//     {
//         if (*ptr1 != *ptr2)
//         {
//             return *ptr1 - *ptr2; // it will return negative value, meaning first ptr is smaller than second
//         }
//         ptr1++; 
//         ptr1++;
//     }
//     // const int IDENTICAL = 0; // well, bruh.
//     return S21_EXIT_SUCCESS;
// }

// memory copy. it doesnt care about data type.
void *s21_memcpy(void *where_to, const void *from, s21_size_t num_bytes)
{
    int cntr = 0;
    while (num_bytes--)
    {
        ((char *)where_to)[cntr] = ((char *)from)[cntr]; // forced cast to 'char*'
        cntr++;
    }
    return where_to;
}

// memory move. similar to copy, but is safer (why tho? idk)
void *s21_memmove(void *where_to, const void *from, s21_size_t num_bytes)
{
    unsigned char *ptr_dest = (unsigned char*) where_to;  // forced conversion
    unsigned char *ptr_src = (unsigned char*) from;       // to unsigned char

    if (ptr_dest < ptr_src) // khm.. I dont understad this
    {
        while (num_bytes--) // while hmb variable remains positive
        {
            *ptr_dest++ = *ptr_src++;
        }
    }

    else // 
    {
        ptr_dest = ptr_dest + num_bytes - 1; // -1 cuz last char is '\0'
        ptr_src = ptr_src + num_bytes - 1;
        while (num_bytes--)
        {
            *ptr_dest-- = *ptr_src--; // per symbol char replacement. it just goes thru pointer
        }
    }
    return where_to;
}



