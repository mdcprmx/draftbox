#include "s21_string.h"

char *s21_strstr(const char *destptr, const char *srcptr) {
  size_t srcptrLength = s21_strlen(srcptr);
  const char *result = S21_NULL;

  if (srcptrLength != 0) {
    for (int x = 0; result == S21_NULL && destptr[x] != '\0'; x += 1) {
      if (destptr[x] == srcptr[0]) {
        if (s21_strncmp(destptr + x, srcptr, srcptrLength) == 0)
          result = destptr + x;
      }
    }
  }

  return (char *)(result == S21_NULL ? destptr : result);
}
