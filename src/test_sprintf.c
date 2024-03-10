#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s21_sprintf.c"

int main()
{
    printf("check 0"); 
    char line_buffer[4096];
    // int day = 28;
    // int month = 02;
    // int year = 2024;

    printf("check 1 s");
    s21_sprintf(line_buffer, "year");
    // what's the difference between printf and sprintf?
    // sprintf forwards it to string, not stdout.
    // yeah, that's literally it.

    printf("%s\n", line_buffer);

    return 0;
}