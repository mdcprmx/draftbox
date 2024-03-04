#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char line_buffer[255];
    int day = 28;
    int month = 02;
    int year = 2024;

    sprintf(line_buffer, "year: %02d", year);
    // what's the difference between printf and sprintf?
    // sprintf forwards it to string, not stdout.
    // yeah, that's literally it.

    printf("%s\n", line_buffer);

    return 0;
}