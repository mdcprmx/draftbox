#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void practice_string_compare();

int main() {
  int bfr_c;

  // lmao, what does ungetc do?! my brain can't understand it, sadly.
  bfr_c = getchar();
  ungetc(bfr_c, stdin);
  ungetc(bfr_c, stdin);
  ungetc(bfr_c, stdin);
  ungetc(bfr_c, stdin);
  ungetc(bfr_c, stdin);
  ungetc(bfr_c, stdin);
  ungetc(bfr_c, stdin);

  putchar(bfr_c);
  putchar(bfr_c);
  putchar(bfr_c);
  putchar(bfr_c);
  putchar(bfr_c);
  putchar(bfr_c);
  putchar(bfr_c);
  putchar(bfr_c);
  putchar(bfr_c);
  putchar(bfr_c);
  return 0;
}

void practice_string_compare() {
  char *buff1 = "Hello";
  char *buff2 = "Hello";

  // so, function strcmp returns 0 when comparing is successfull
  if (strcmp(buff1, buff2) == 0) {
    printf("compare result: equal\n");
  }

  else {
    printf("not equal\n");
  }
}
