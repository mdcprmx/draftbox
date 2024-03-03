#include "s21_sprintf_lib.h"
#include <string.h> // DELETE ME LATER
// пока школьные функции s21_ не подключены, юзаю string.h
// строки где надо заменить стринговые функции: 32, 

// CURRENT LINE 223, time stamp 45:20

// три точки (...) в s21_sprintf для получения аргументов в sprintf
//               речь про вот эти ниже:  |    |        |
//                                       v    v        v
// например - sprintf(string,"%d %c %f", output_num, char, float_num);
// тоесть три точки указывают на третий элемент, часть после второй запятой
// и говорят про то что их может быть сколько угодно
int s21_sprintf(char *buffer_string, const char *FORMAT, ...)
{
    // old_string нужен для return-a. чтоб узнать скок символов мы записали
    char *old_string = buffer_string;
    const char specs_options[] = "diuocsnpXxGgEeFf"; // все возможные спецфктры


    va_list valist_args;           // (...) аргументы летят сюда, в эту структуру
    va_start(valist_args, FORMAT); // 1-ым идёт то что запускается, 
                                   // 2-ым идёт переменная из функции после которой начинать искать аргументы

    while(*FORMAT) // пока не дошли до конца форматной строки // "while format is true"
    {
        if (*FORMAT == '%')  // если в форматной строке видим процент, то начинаем обработку
        {
            FORMAT++;        // крутим цикл по всем символам
            struct_sprintf_specs specfctrs = {0}; // заполняем нулями структуру
            specfctrs.number_system = 10;         // десятиричная система по дефолту
            FORMAT = funct_set_specs(FORMAT, &valist_args, &specfctrs); // вызываем set_specs и передаём туда спецы,
                                                                        // строку формата, и указатель на валист.
            while (!strchr(specs_options, *FORMAT))  // ищем в формате возможные спецификаторы
            {
                FORMAT++; // крутим цикл пока не найдём корректную букву
                          // s21_strchr остановит цикл когда найдёт подходящий символ
            }

            // 
            buffer_string = funct_parser(buffer_string, old_string, specfctrs, FORMAT, &valist_args);
        }

        else    // если же процента нет, то это просто текст
        {
            *buffer_string = *FORMAT;
            buffer_string++;
        }   
        
    }

    *buffer_string = '\0';         // заканчиваем стрингу
    va_end(valist_args);           // закрываем va_list 
    return(buffer_string - old_string); // возвращаем кол-во записанных символов
}

// (основная) функция обработки спецификаторов 
const char *funct_set_specs(const char *FORMAT_A, va_list valist_args_a, struct_sprintf_specs *specs_a)
{
    FORMAT_A = funct_specs_switcher(FORMAT_A, specs_a); // обрабатываем наличие '+-#0 ' (и пробел тож)
    FORMAT_A = funct_process_width(FORMAT_A, valist_args_a, &specs_a->width); // ищем цифру ширины или '*'

    if (*FORMAT_A == '.') // ищем точку, для float точности
    {
        specs_a->dot_is_present = 1;
        specs_a->fill_w_nulls = 0; // не может быть одновременно и '.' и '0', поэтому f_w_nulls обнуляем
        FORMAT_A = FORMAT_A + 1;
        
        // в этом случае запуск поиска ширины произойдёт после '.', поэтому отправляем f_accuracy
        FORMAT_A = funct_process_width(FORMAT_A, valist_args_a, &specs_a->float_accuracy);
        // а вообще это гениальное переиспользование кода!
    }


    if (*FORMAT_A == 'L')
        specs_a->spec_length = 'L';
    else if (*FORMAT_A == 'l')
        specs_a->spec_length = 'l';
    else if (*FORMAT_A == 'h')
        specs_a->spec_length = 'h';

    if (specs_a->spec_length != 0) 
        FORMAT_A = FORMAT_A + 1;


    // необязательная часть, в случае если funct_process_width сработает с ошибкой
    // однако, всегда хорошо иметь дополнительные проверки
    if (specs_a->width < 0)
    {
        specs_a->width = -specs_a->width; // отрицательное число переводим в полжтльное
        specs_a->minus_align_left = 1;    // ну и минус переводим в спецификатор
    }

    return FORMAT_A;
}

// (вторичная) переключалка наличия спецификаторов в форматной строке
const char *funct_specs_switcher(const char *FORMAT_B, struct_sprintf_specs *specs_b)
{
    while(FORMAT_B)  // пока переменная FORMAT_B положительна
    {
        if (*FORMAT_B == '+') 
        specs_b->plus_show_positv_negtv = 1;

        else if (*FORMAT_B == '-') 
        specs_b->minus_align_left = 1;

        else if (*FORMAT_B == '#')
        specs_b->reshetka_hexidecimal = 1;

        else if (*FORMAT_B == ' ')
        specs_b->space = 1;

        else if (*FORMAT_B == '0')
        specs_b->fill_w_nulls = 1;
        
        else         // если форматная строка кончилась, то цикл кончаем
        {
            break;
        }
        FORMAT_B++;  // крутит цикл
    }

    // если одновременно и плюс и пробел
    specs_b->space = (specs_b->space != 0 && specs_b->plus_show_positv_negtv == 0);

    // если одновременно и ноль и минус
    specs_b->fill_w_nulls = (specs_b->fill_w_nulls != 0 && specs_b->minus_align_left == 0);

    return FORMAT_B;
}

// (вторичная) обрабатывает цифры в форматной строке, типа "sprintf("%69.d", output_num);" или "sprintf("%.69d", output_num)"
const char *funct_process_width(const char *FORMAT_C, va_list *valist_args_b, int *int_from_specs)
{
    *int_from_specs = 0;   // по дефолту 0
    if (*FORMAT_C == '*')  // если звёзда, то надо взять ширину строки из первого аргумента
    {                      // например (sprintf("%*d", 37, output_num);) - в этом примере оно возьмёт 37
        *int_from_specs = va_arg(*valist_args_b, int);   // ожидает что первое число будет int
                                                         // и записывает его в наш valist_args
        FORMAT_C++;  // проверяет всю строку получаетс?
    }
    
    while (FORMAT_C) // пока не конец строки (который '\0')
    {
        if ('0' <= *FORMAT_C && *FORMAT_C <= '9') // если символ является цифрой (по ASCII от 48 до 57)
        {
            *int_from_specs = *int_from_specs * 10;  // эт умножение
            *int_from_specs = int_from_specs + *FORMAT_C - '0'; // у нуля по ASCII число 48
            // почему решение именно такое? яхз, там какаят сложная математика связанная с ASCII
            // суть в том что FORMAT эт не int, это char.
        }

        else break; // если же символ не цифра, то брейкаемся.
        FORMAT_C++;
    }
    return FORMAT_C;
}

// (основная) функция переделывания строки
char *funct_parser(char *buffer_string_a, char *old_string_a, struct_sprintf_specs specs_c, const char *FORMAT_D, va_list *valist_args_c)
{
    switch (*FORMAT_D)
    {
        case 'i':
        case 'd':  // почему d и i вместе? потомучт эт одно и тоже
        buffer_string_a = print_decimal(buffer_string_a, specs_c, valist_args_c);

        case 'b':

    }

}

// (вторичная) функция для %d и %i
char *print_decimal(char *bfr_str, struct_sprintf_specs specs_d, va_list *valist_args_d)
{
    long int output_num = 0;  // число которое ставим на место %d в строке вывода

    // если %ld
    if (specs_d.spec_length == 'l')  
    {
        // если до этого в spec_length был записан 'l' то преобразуем в long int (64 бита)
        output_num = (long int) va_arg(*valist_args_d, long int);  
    }
    // если %hd
    else if (specs_d.spec_length == 'h')
    {
        // если же в spec_length был записан 'h' то кастим в short (16 бит)
        output_num = (short) va_arg(*valist_args_d, short int);
    }

    // если %d
    else
    {
        // то прост кастим его в инт (однако 'int' и 'short int' это одно и то же)
        output_num = (int) va_arg(*valist_args_d, int);
    }

    s21_size_t buffer_size = 0;
    buffer_size = get_width_decimal(&specs_d, output_num); // узнаём ширину поля вывода

    char *str_to_num = calloc(buffer_size, sizeof(char)); // маллочим/каллочим память

    if (str_to_num != NULL) // проверка выделения памяти
    {
        int i = 0;
        i = decimal_to_string(specs_d, output_num, str_to_num, buffer_size);
        for (int k = i - 1; k >= 0 ; k--)
        {
            *bfr_str = str_to_num[k];
            bfr_str++;
        }
    }
}

// (третичная) функция для print_decimal
s21_size_t get_width_decimal(struct_sprintf_specs *specs_e, long int num)
{
    s21_size_t result = 0;
    long int saved_num = num;

    // если каким-то образом оно пришло отрицтлнм, делаем его плжтлнм
    if (saved_num < 0)
        saved_num = -saved_num; 
    
    // узнаём какое это число - однозначное, или двузначное, или трехзначное и тд
    while (saved_num > 0)
    {
        saved_num = saved_num / 10;
        result++;
    }

    // если спецификаторов ширины нет, то надо выделить один символ под вывод
    if(saved_num == 0 && result == 0 && (specs_e->float_accuracy || specs_e->width || specs_e->space ))
    {
        result++;
    }

    // если ширина больше результата, то результат берётся из ширины
    // пример: если width = 7, а result = 2, то result станет 7
    if ((s21_size_t)specs_e->width > result)
        result = specs_e->width;

    // если точность больше результата, то результат берётся из точность
    if ((s21_size_t)specs_e->float_accuracy > result) 
        result = specs_e->float_accuracy;

    // если есть пробел, или плюс, или наше число меньше нуля
    if (specs_e->space || specs_e->plus_show_positv_negtv || num < 0)
    {
        specs_e->plus_or_space_present = 1;
        result++;
    }

    // если в переменной 0, и числа ширины поля нет, и пробела нет, и точки тоже нет
    if (result == 0 && saved_num == 0 && !specs_e->float_accuracy && !specs_e->width && !specs_e->space && !specs_e->dot_is_present)
    {
        result++; // то всё равно надо выделить одну ячейку под вывод этого нуля
    }
    return result;
} 

// (третичная) функция для print_decimal
int decimal_to_string(struct_sprintf_specs specs_f, long int num, char *str_to_num, s21_size_t buffer_size_a)
{

}


