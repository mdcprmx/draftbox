#include "s21_library_header.h"
#include "s21_STRING_BASE_LIB_RENAME_ME.c"
#include "s21_test_header.h"

int main()
{
    char *stroka1 = "ayyyyyy";
    char *stroka2 = "bruh";
    char *ch;

    puts(stroka1);
    puts(stroka2);

    char ch_find = 'h';
    ch = s21_memchr(stroka2, ch_find, 8);

    // write(1, ch, 2);
    printf("%s", ch);
    return 0;
}


