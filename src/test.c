#include "s21_string.h"
#include "s21_STRING_BASE_LIB_RENAME_ME.c"

int main()
{
    char *stroka1 = "ayyyyyy";
    char *stroka2 = "bruh";
    char *ch;

    puts(stroka1);
    puts(stroka2);

    ch = s21_memchr(stroka2, 'u', 4);

    // write(1, ch, 2);
    printf("%c", ch);
    return 0;
}


