#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void malloc_shielded(char *buffer);
void error_malloc_shielded();
void free_shielded(char *buffer);
void calloc_shielded(char *buffer);