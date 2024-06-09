#ifndef S21_STRING_H_
#define S21_STRING_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define S21_EXIT_SUCCESS 0
#define S21_EXIT_FAILURE 1
#define S21_NULL ((void*)0) // указатель на NULL, по сути это число 0 переведённое в тип void

typedef unsigned long int s21_size_t;  // стандартный size_t нельзя использовать, поэтому испзуем наш
                                       // и да, это по сути просто unsigned long int

// part 1
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str, const char *keys); 
char *s21_strrchr(const char *str, int symbol); 
char *s21_strstr(const char *destptr, const char *srcptr); 
char* s21_strncpy(char* dest, const char* src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strerror(int errnum);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strchr(const char *str, int c);
char *s21_strtok(char *str, const char *delim); 
char *s21_strerror(int errnum); 
char *s21_strtok(char *str, const char *delim);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n); 
void *s21_memcpy(void *restrict dest, const void *restrict src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n); 
char *s21_strncat(char *dest, const char *src, size_t n); 

// part 2 & 3
void s21_sprintf(char *buffer, const char *format, ...);

// part 5
void *s21_trim(const char *src, const char *trim_chars);
int right_side(const char *src, const char *trim_chars, int last);
int left_side(const char *src, const char *trim_chars, int last);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

#endif // SRC_S21_STRING_H