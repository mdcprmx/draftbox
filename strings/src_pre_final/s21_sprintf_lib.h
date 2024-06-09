#ifndef S21_HEADER_SPRINTF
#define S21_HEADER_SPRINTF

#include "s21_string.h"
#include <stdarg.h>  // для va_list
#include <stdbool.h> // для bool-ов

typedef struct {
  int minus_align_left;  
  // в строке есть минус (который выравнивает влево) (sprintf("-%d",);)

  int plus_show_sign;  
  // знак плюса или минуса обязателен                (sprintf("%+d",);)

  int reshetka_hexidcml;   
  // указывает что записывается 16-тиричное число    (sprintf("%#d",);)

  int fill_w_space;  
  // пробел после знака '%'. например                (sprintf("% d",);)

  int fill_w_nulls;  
  // заполняет вывод нулями а не пробелами           (sprintf("%0d",);)

} flags;

typedef struct {
  int width;
  // ширина строки                                   (sprintf("%14d",);)

  int float_accuracy;
  // точность вывода, если стоит точка.              (sprintf("%.3d",);)

  int length;
  // для спцфктров ld или lf, или lld. (long)        (sprintf("%ld",);)
  // и для спецификаторов hd, hf       (short)       (sprintf("%hd",);)

  int dot;
  // вспомогательная переменная, включается когда есть accuracy. для флага G

  int flag_to_size;
  // bruh, кароч он юзает эту переменную не только как 'plus_or_space_present'
  // но и как флаг. пусть будт

  int number_system;
  // использовать 10-тиричную или 16-рчную систему счисления
  // по дефолту 10, но если есть символ 'X' или 'x' в конце то 16ричная
  // если 'x' маленькая то выводит в нижнем регистре (a-z)
  // если 'X' большая то выводит в верхнем регистре (A-Z)
  // (sprintf("%dX",);) | (sprintf("%dx");) 

  int is_upper_case;
  // флаги (X F E G) могут быть заглавными и строчными, эта вспомог переменная
  // нужна чтоб отслеживать это

  char c;
  int g_small;
  int G_big;
  int e_small;
  int E_big;
  unsigned int x;
  unsigned int X;
  int o;
  int ptr;

} struct_specfrs;

char *main_print_char(char *buffer, char sym, flags opt, struct_specfrs specs, int *ch); 
char *main_print_string(char *buffer, va_list *args, flags opt, struct_specfrs specs);
char *main_print_int(char *buffer, va_list *args, flags opt, struct_specfrs specs); 
char *main_print_float(char *buffer, va_list *args, flags opt, struct_specfrs specs);
char *main_print_Uint(char *buffer, va_list *args, flags opt, struct_specfrs specs);
char *main_print_hex(char *buffer, va_list *args, flags opt, struct_specfrs specs);
char *main_print_octal(char *buffer, va_list *args, flags opt, struct_specfrs specs);
char *main_print_ptr(char *buffer, va_list *args, flags opt, struct_specfrs specs);
const char *main_get_width(const char *format, int *width, va_list *args);

char get_num_char(int num, int is_upper_case);
int int_to_string(long int num, char *buffer, struct_specfrs specs, s21_size_t size_to_decimal, flags opt);
int float_to_string(long double num, char *buffer, struct_specfrs specs, s21_size_t size_to_double, flags opt);
int unsigned_to_string(unsigned long int num, char *buffer, struct_specfrs specs, s21_size_t size_to_unsigned, flags opt);
int octal_to_string(unsigned long int num, char *buffer, struct_specfrs specs, s21_size_t size_to_unsigned, flags opt);
int hex_to_string(unsigned long int num, char *buffer, struct_specfrs specs, s21_size_t size_to_unsigned, flags opt);
s21_size_t get_size_to_decimal(struct_specfrs *specs, flags *opt, long int num);
s21_size_t get_size_to_double(struct_specfrs *specs, flags *opt, long double num);
s21_size_t get_size_to_unsigned(struct_specfrs *specs, flags *opt, unsigned long int num);

#endif // S21_PRINTF_H