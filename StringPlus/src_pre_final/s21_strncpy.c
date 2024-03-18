#include "s21_string.h"

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  char* out = dest;

  if (src == S21_NULL) {
    *dest = '\0';
    return out;
  }

  while (n > 0) {
    if (*src != '\0') {
      *dest = *src;
      src++;
    } else {
      *dest = '\0';
      while (--n > 0) {
        *(++dest) = '\0';
      }
      break;
    }
    dest++;
    n--;
  }

  return out;
}