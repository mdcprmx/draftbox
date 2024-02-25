#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// puts - put string and add '\n' at the end. noice. lovely

int main()
{
    char string_one[] = "MoshiMoshi";
    char string_two[] = "It's ya boii Alex";

    puts(string_one);
    puts(string_two);

    char str_third[] = "dance";
    memmove(string_two, string_one, strlen(string_one));

    puts("\nAfter memmove");
    puts(string_one);
    puts(string_two);
    return 0;
}