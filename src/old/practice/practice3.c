#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char buffer[1024] = "Dance revolution gura gura lava lava\n";

    write(STDOUT_FILENO, buffer, strlen(buffer));

    char search_for = 'c';
    char bfr_scnd = memchr(buffer, search_for, strlen(buffer));
    
    write(STDOUT_FILENO, bfr_scnd, strlen(bfr_scnd));

    return 0;
}