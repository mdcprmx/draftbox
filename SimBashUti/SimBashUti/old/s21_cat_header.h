#ifndef S21_CAT_HEADER
#define S21_CAT_HEADER

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void scenario_file_doesnt_exist(int file_descr);
void scenario_no_arguments();
void arguments_parser(int argc, char **argv);

#endif