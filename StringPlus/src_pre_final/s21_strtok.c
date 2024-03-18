#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last;
  char *ref;
  int flag_working = 1;
  if ((ref = str) == S21_NULL && (ref = last) == S21_NULL) flag_working = 0;
  for (int i = 0; flag_working && *ref && delim[i]; i++) {
    if (*ref == delim[i]) {
      ref++;
      i = -1;
    }
  }
  if (flag_working && *ref == '\0') {
    ref = S21_NULL;
    last = S21_NULL;
    flag_working = 0;
  }
  str = ref;
  while (flag_working && *ref) {
    for (int i = 0; delim[i]; i++) {
      if (*ref == delim[i]) {
        flag_working = 0;
        *ref = '\0';
        ref++;
        if (*ref == '\0') ref = S21_NULL;
        last = ref;
        break;
      }
    }
    if (flag_working) {
      ref++;
      if (*ref == '\0') {
        last = S21_NULL;
      }
    }
  }
  return str;
}