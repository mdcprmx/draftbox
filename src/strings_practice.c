#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void practice_string_compare();

int main()
{
    char *buff1 = "Hello";
    char *buff2 = "Hello";

    // so, function strcmp returns 0 when comparing is successfull
    if (strcmp(buff1, buff2) == 0)
    {
        printf("compare result: equal\n");
    }

    else
    {
        printf("not equal\n");
    }

    return 0;
}


void practice_string_compare()
{
    char *buff1 = "Hello";
    char *buff2 = "Hello";

    // so, function strcmp returns 0 when comparing is successfull
    if (strcmp(buff1, buff2) == 0)
    {
        printf("compare result: equal\n");
    }

    else
    {
        printf("not equal\n");
    }
}

