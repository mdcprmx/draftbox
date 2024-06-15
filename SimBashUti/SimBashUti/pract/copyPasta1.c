#include "s21_cat.h"

FILE *printData(FILE *file, options *config) {
  // so, this is some sort of flag initialization for "double flags"
  for (char sym = '0'; (sym = getc(file)) != EOF;) {
    config->emptyLine = 0;

    if (config->s && config->counterS == 0 && sym == '\n') {
      config->counterS += 1;
    }

    else if (config->counterS != 0 && sym == '\n') {
      config->counterS += 1;
      config->emptyLine = 1;
    }

    else if (config->counterS > 1 && sym != '\n') {
      config->counterS = 0;
      config->e ? printf("$\n") : printf("\n");
      if (config->n != 0) printf("%6d\t", config->n++);
    }

    else {
      config->counterS = 0;
    }
    ///////////////////////////////////////
    ///////////////////////////////////////

    // and this, is printing logic
    if (config->n != 0 || config->b != 0) {
      if (config->newLine == 1 && !(config->newLine = 0))
        printf("%6d\t", config->n++);

      if (config->n == 1) printf("%6d\t", config->n++);

      if (config->b == 1) printf("%6d\t", config->b++);

      if (sym == '\n' && config->n != 0 && config->emptyLine == 0)
        config->newLine = 1;

      if (sym == '\n' && config->b != 0) config->counterB += 1;

      if (sym != '\n' && config->counterB != 0 && config->counterS == 0)
        if (!(config->counterB = 0)) printf("%6d\t", config->b++);
    }

    // and that?
    // printing logic part 2
    if (sym == '\n' && config->e && config->emptyLine == 0) printf("$");

    if (config->v) {
      if (sym < 32 && sym != 9 && sym != 10)
        if (sym += 64) printf("^");
      if (sym == 127)
        if ((sym = '?')) printf("^");
    }

    if (config->t && sym == '\t')
      if ((sym = 'I')) printf("^");

    if (config->emptyLine == 0) printf("%c", sym);
  }

  return file;
}