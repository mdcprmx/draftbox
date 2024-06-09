#include <stdio.h>
#include <stdlib.h>

typedef char c;
typedef long long int LLI;
// sooo typedef is used as a "macro", as enum (sort of)
// instead of typing "long long int var_name" u can type "LLI var_name"
// khm, so it is mostly cosmetic?

struct box_type {
  int a;
  int b;
};

int main(int argc, char** argv) {
  struct box_type plastic_box;
  plastic_box.a = 27;
  plastic_box.b = 92;

  return 0;
}