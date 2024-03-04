#ifndef S21_SPRINTF_H_
#define S21_SPRINTF_H_
#include "s21_string_lib.h"
#include <stdarg.h>  // для va_list

typedef struct {

    int minus_align_left;  
    // в строке есть минус (который выравнивает влево) (sprintf("-%d",);)

    int plus_show_positv_negtv; 
    // знак плюса или минуса обязателен                (sprintf("%+d",);)

    int space;             
    // пробел после знака '%'. например                (sprintf("% d",);)

    int reshetka_hexidecimal; 
    // указывает что записывается 16-тиричное число    (sprintf("%#d",);)

    int width;
    // ширина строки до точки                          (sprintf("%14d",);)

    int zero;
    // заполняет вывод нулями а не пробелами           (sprintf("%0d",);)

    int float_accuracy;
    // точность вывода, если стоит точка.              (sprintf("%.3d");)

    char var_length;
    // надо заметить что это char! не инт как все другие
    // для спцфктров ld или lf, или lld. (long)        (sprintf("%ld");)
    // также для спецфктрв hd, hf, итд   (short)

    int number_system;
    // использовать 10-тиричную или 16-рчную систему счисления
    // по дефолту 10, но если есть символ 'X' или 'x' в конце то 16ричная
    // если 'x' маленькая то выводит в нижнем регистре (a-z)
    // если 'X' большая то выводит в верхнем регистре (A-Z)
    // (sprintf("%dX",);) | (sprintf("%dx");) 

    int plus_or_space_present;
    // вспомогательная переменная,если перменные plus_positv_negatv или space 
    // включены, то включаем эту переменну. нужна для логики спецификаторов

    int dot_is_present;
    // вспомогательная переменная, включается когда есть accuracy. для флага G

    int is_upper_case;
    // флаги (X F E G) могут быть заглавными и строчными, эта вспомог переменная
    // нужна чтоб отслеживать это

    int spec_g;
    // используется ли спецфктр g    (sprintf("%dg",);)

    int spec_e;
    // используется ли спецфктр e, записывает число в научной нотации (втф?!)
    //                               (sprintf("%de",);)
} struct_sprintf_specs;


#endif // S21_PRINTF_H