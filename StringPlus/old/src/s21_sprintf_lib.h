#ifndef S21_SPRINTF_H_
#define S21_SPRINTF_H_
#include "s21_string_lib.h"
#include <stdarg.h>  // для va_list
#include <stdbool.h> // для bool-ов

#define HEXADECIMAL 16 // угу, эт просто макросы на числа 16 и 10. для красоты и читаемости. 
#define DECIMAL 10     // Нужно для '#', перемнной number_system

typedef struct {

    bool minus_align_left;  
    // в строке есть минус (который выравнивает влево) (sprintf("-%d",);)

    bool plus_show_positv_negtv; 
    // знак плюса или минуса обязателен                (sprintf("%+d",);)

    bool space_is_present;             
    // пробел после знака '%'. например                (sprintf("% d",);)

    bool fill_w_nulls;
    // заполняет вывод нулями а не пробелами           (sprintf("%0d",);)

    bool plus_or_space_present;
    // вспомогательная переменная,если перменные plus_show_positv_negatv или space_is_present 
    // включены, то включаем эту переменну. нужна для логики спецификаторов

    bool dot_is_present;
    // вспомогательная переменная, включается когда есть accuracy. для флага G

    bool is_upper_case;
    // флаги (X F E G) могут быть заглавными и строчными, эта вспомог переменная
    // нужна чтоб отслеживать это

    bool spec_g;
    // используется ли спецфктр g    (sprintf("%dg",);)

    bool spec_e;
    // используется ли спецфктр e, записывает число в научной нотации (втф?!)
    //                               (sprintf("%de",);)
    
    int reshetka_hexidecimal; 
    // указывает что записывается 16-тиричное число    (sprintf("%#d",);)

    int width;
    // ширина строки                                   (sprintf("%14d",);)

    int float_accuracy;
    // точность вывода, если стоит точка.              (sprintf("%.3d",);)

    int number_system;
    // использовать 10-тиричную или 16-рчную систему счисления
    // по дефолту 10, но если есть символ 'X' или 'x' в конце то 16ричная
    // если 'x' маленькая то выводит в нижнем регистре (a-z)
    // если 'X' большая то выводит в верхнем регистре (A-Z)
    // (sprintf("%dX",);) | (sprintf("%dx");) 

    char spec_length;
    // для спцфктров ld или lf, или lld. (long)        (sprintf("%ld",);)
    // и для спецификаторов hd, hf       (short)       (sprintf("%hd",))

} struct_sprintf_specs;


int s21_sprintf(char *buffer_string, const char *FORMAT, ...);
const char *main_funct_parsing(const char *FORMAT_A, va_list *valist_args_a, struct_sprintf_specs *specs_a);
const char *funct_specs_switcher(const char *FORMAT_B, struct_sprintf_specs *specs_b);
const char *funct_process_width(const char *FORMAT_C, va_list *valist_args_b, int *int_from_specs);
char *main_funct_output(char *buffer_string_a, char *old_string_a, struct_sprintf_specs specs_c, const char *FORMAT_D, va_list *valist_args_c);
char *print_decimal(char *bfr_str, struct_sprintf_specs specs_d, va_list *valist_args_d);
s21_size_t get_width_decimal(struct_sprintf_specs *specs_e, long int num);
int cast_decimal_to_string(struct_sprintf_specs specs_f, long int num, char *str_to_num, s21_size_t buffer_size_a);
char get_num_char(int num, int is_upper_case);

#endif // S21_PRINTF_H