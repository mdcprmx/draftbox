#define SRC_S21_STRING_H
#include <stdio.h>
#include <stdlib.h>

#define S21_NULL ((void*)0) // that's literally a POINTER TO VOID. yep. "NULL" is defined as this

typedef unsigned long s21_size_t;  // and this is "size_t". yeah, literally just a unsigned long int (from 0 to 4,294,967,295)