#ifndef GREP_H
#define GREP_H

typedef struct arguments {
  int i, v, c, l, f, e, n, h, s, o;
  char* pattern;
  int len_pattern;
  int mem_pattern;
} arguments;
#endif
