#include "s21_sprintf_lib.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t strLength = 0;
  for (; str[strLength];) {
    strLength += 1;
  }
  return strLength;
}
