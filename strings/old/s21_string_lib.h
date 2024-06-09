#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
#include <stdio.h>
#include <stdlib.h>

#define S21_EXIT_SUCCESS 0
#define S21_NULL ((void*)0) // указатель на NULL, по сути это число 0 переведённое в тип void

typedef unsigned long int s21_size_t;  // стандартный size_t нельзя использовать, поэтому испзуем наш
                                       // и да, это по сути просто unsigned long int

#endif // SRC_S21_STRING_H