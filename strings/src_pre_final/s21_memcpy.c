#include "s21_string.h"

//Копирует n символов из src в dest.

void *s21_memcpy(
    void *restrict dest, const void *restrict src,
    s21_size_t n) {  //слово restrict используется для указания компилятору, что
                     //указатели dest и src не перекрываются.
  unsigned char *dest_p = (unsigned char *)dest;
  const unsigned char *src_p = (const unsigned char *)src;

  while (n--) *dest_p++ = *src_p++;
  return dest;
}