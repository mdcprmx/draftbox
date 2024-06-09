#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const char *str1_p = (const char *)str1;
  const char *str2_p = (const char *)str2;
  while (n--) {
    if (*str1_p != *str2_p) {
      return *str1_p - *str2_p;
    }
    str1_p++;
    str2_p++;
  }
  return 0;
}