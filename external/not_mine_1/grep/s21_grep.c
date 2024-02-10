#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VALID_OPTS "e:ivclnhsf:o"

// Options storage
struct arguments {
  bool e;  // выполняется поиск по всем заданным шаблонам
  int i;    // игнор регистра
  bool c;  // подсчет строк с совпадениями
  bool l;  // выводит имя файла, где найдено совпадение
  bool n;  // номер строки совпадения
  bool h;  // выводит совпадения без имени файла
  bool s;  // без сообщений об ошибках о несущ файлах или нечитаемых флагах
  bool f;  // -f FILE, ищет шаблоны из файла
  bool o;  // выводит только совпадающие части строки
  bool v;           // выводит несовпадающие линии
  char* pattern;    // паттерн
  int len_pattern;  // длина паттерна
  int mem_pattern;  // размер выделенной памяти для паттерна
};

struct arguments arguments_parser(int argc, char* argv[]);
void job(struct arguments arg, char* path, regex_t* reg);
void output_line(char* line, int n);
void print_match(regex_t* re, char* line);
void add_reg_from_file(struct arguments* arg, char* filepath);
void pattern_adding(struct arguments* arg, char* pattern);
void output(struct arguments arg, int argc, char** argv);

int main(int argc, char** argv) {
  struct arguments arg = arguments_parser(argc, argv);
  regex_t re;

  if (arg.pattern == NULL) {
    printf("error");
  } else {
    int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
    if (error) perror("Error");

    for (int i = optind; i < argc; i++) {
      job(arg, argv[i], &re);
    }
  }

  regfree(&re);
  free(arg.pattern);
  return 0;
}

// Set arguments
struct arguments arguments_parser(int argc, char* argv[]) {
  struct arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        pattern_adding(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;  // флаг игнора регистра
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.c = 1;
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        add_reg_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
    }
  }
  if (arg.len_pattern == 0) {
    pattern_adding(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

void add_reg_from_file(struct arguments* arg, char* filepath) {
  // Obtain patterns from FILE, one per line
  FILE* f = fopen(filepath, "r");
  if (f == NULL) {
    if (!arg->s) perror(filepath);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  ssize_t read = getline(&line, &memlen, f);
  while (read != -1 && read != EOF) {
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    pattern_adding(arg, line);
    read = getline(&line, &memlen, f);
  }
  free(line);
  fclose(f);
}

void pattern_adding(struct arguments* arg, char* pattern) {
  // Allocation memory and adding pattern
  if (pattern == NULL) {
    printf("error");
    return;
  }
  int n = strlen(pattern);
  if (arg->len_pattern == 0) {
    arg->pattern = malloc(1024 * sizeof(char));
    arg->mem_pattern = 1024;
  }
  if (arg->mem_pattern < arg->len_pattern + n) {
    arg->pattern = realloc(arg->pattern, arg->mem_pattern * 2 * sizeof(char));
  }
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void job(struct arguments arg, char* path, regex_t* reg) {
  FILE* f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) perror(path);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  ssize_t read = getline(&line, &memlen, f);
  int line_count = 1;
  int c = 0;
  while (read != -1 && read != EOF) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_count);
        if (arg.o) {
          print_match(reg, line);
        } else {
          output_line(line, read);
        }
      }
      c++;
    }
    read = getline(&line, &memlen, f);
    line_count++;
  }
  free(line);
  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", c);
  }
  if (arg.l && c > 0) printf("%s\n", path);
  fclose(f);
}

void output_line(char* line, int n) {
  // Print line
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void print_match(regex_t* re, char* line) {
  // Print match
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(re, line + offset, 1, &match, 0);
    if (result != 0) {
      break;
    }
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[offset + i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}
