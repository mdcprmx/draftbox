#include "s21_sprintf_lib.h"
#include <string.h> // DELETE ME LATER
// пока школьные функции s21_ не подключены, юзаю string.h
// строки где надо заменить стринговые функции: 36, 

// CURRENT LINE 312

// три точки (...) в s21_sprintf для получения аргументов в sprintf
//               речь про вот эти ниже:       |        |        |
//                                            v        v        v
// например - sprintf(string,"%d %c %f", output_num, char, float_num);
// тоесть три точки указывают на третий элемент, часть после второй запятой
// и говорят про то что их может быть сколько угодно
int s21_sprintf(char *buffer_string, const char *FORMAT, ...) // <-- в строке 8 речь про вот эти три точки
{
    // old_string нужен для return-a. чтоб узнать скок символов мы записали
    char *old_string = buffer_string;

    printf("check 1");
    va_list valist_args;           // (...) аргументы летят сюда, в эту структуру
    va_start(valist_args, FORMAT); // 1-ым идёт то что запускается, 
                                   // 2-ым идёт переменная из функции после которой начинать искать аргументы
    
    struct_sprintf_specs specfctrs = {0};   // создаём, и заполняем нулями структуру
    specfctrs.number_system = DECIMAL;      // десятиричная система по дефолту

    printf("check 1");
    while(*FORMAT) // пока не дошли до конца форматной строки // "while format is true"
    {
        if (*FORMAT == '%')  // если в форматной строке видим процент, то начинаем обработку
        {
            FORMAT++;        // смещаемся на 1 символ

            FORMAT = main_funct_parsing(FORMAT, &valist_args, &specfctrs); // парсинг и нахождение спецификаторов

            const char specs_options[] = "diuocsnpXxGgEeFf"; // все возможные спецфктры
            while (!strchr(specs_options, *FORMAT))          // ищем в формате возможные спецификаторы
            {
                FORMAT++; // крутим цикл пока не найдём корректную букву (но по идее он сразу в первой итерации цикла найдёт)
                          // (s21_)strchr остановит цикл когда найдёт подходящий символ
            }

            // Функция форматированного вывода.             
            buffer_string = main_funct_output(buffer_string, old_string, specfctrs, FORMAT, &valist_args);
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
const char *main_funct_parsing(const char *FORMAT_A, va_list *valist_args_a, struct_sprintf_specs *specs_a)
{
    FORMAT_A = funct_specs_switcher(FORMAT_A, specs_a); // обрабатываем наличие '+-#0 ' (и пробел тож)
    FORMAT_A = funct_process_width(FORMAT_A, valist_args_a, &specs_a->width); // ищем цифру ширины или '*'

    if (*FORMAT_A == '.') // ищем точку, для float точности
    {
        specs_a->dot_is_present = true;
        specs_a->fill_w_nulls = false; // не может быть одновременно и '.' и '0', поэтому f_w_nulls обнуляем
        FORMAT_A = FORMAT_A + 1;       // двигаемся на одну позицию вперёд
        
        // в этом случае запуск поиска ширины произойдёт после '.', поэтому отправляем f_accuracy
        FORMAT_A = funct_process_width(FORMAT_A, valist_args_a, &specs_a->float_accuracy);
        // а вообще это гениальное переиспользование кода!
    }

    // узнаём %Ld ли это (или %ld, %hd)
    if (*FORMAT_A == 'L')
        specs_a->spec_length = 'L';
    else if (*FORMAT_A == 'l')
        specs_a->spec_length = 'l';
    else if (*FORMAT_A == 'h')
        specs_a->spec_length = 'h';

    if (specs_a->spec_length != false) 
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
        specs_b->plus_show_positv_negtv = true;

        else if (*FORMAT_B == '-') 
        specs_b->minus_align_left = true;

        else if (*FORMAT_B == '#')
        specs_b->reshetka_hexidecimal = true;

        else if (*FORMAT_B == ' ')
        specs_b->space_is_present= true;

        else if (*FORMAT_B == '0')
        specs_b->fill_w_nulls = true;
        
        else         // если форматная строка кончилась, то цикл кончаем
        {
            break;
        }
        FORMAT_B++;  // крутит цикл
    }

    // если одновременно и плюс и пробел
    specs_b->space_is_present = (specs_b->space_is_present == true && specs_b->plus_show_positv_negtv == false);

    // если одновременно и ноль и минус
    specs_b->fill_w_nulls = (specs_b->fill_w_nulls == true && specs_b->minus_align_left == false);

    return FORMAT_B;
}

// (вторичная) обрабатывает цифры в форматной строке, типа "sprintf("%69.d", output_num);" или "sprintf("%.69d", output_num)"
const char *funct_process_width(const char *FORMAT_C, va_list *valist_args_b, int *int_from_specs)
{
    *int_from_specs = false;    // по дефолту 0
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
            *int_from_specs = *int_from_specs + *FORMAT_C - '0'; // у нуля по ASCII число 48
            // почему решение именно такое? яхз, там какаят сложная математика связанная с ASCII
            // суть в том что FORMAT эт не int, это char.
        }

        else break; // если же символ не цифра, то брейкаемся.
        FORMAT_C++;
    }
    return FORMAT_C;
}

// (основная) функция переделывания строки
char *main_funct_output(char *buffer_string_a, char *old_string_a, struct_sprintf_specs specs_c, const char *FORMAT_D, va_list *valist_args_c)
{
    switch (*FORMAT_D)
    {
        case 'i':
        case 'd':  // почему d и i вместе? потомучт эт одно и тоже
        buffer_string_a = print_decimal(buffer_string_a, specs_c, valist_args_c);

        case 'u':
        case 'o':
        case 'x':
        case 'X':
        specs_c = set_number_system(specs_c, *FORMAT_D);
        buffer_string_a = print_u(buffer_string_a, specs_c, *(FORMAT_D - 1), valist_args_c);

    }

    if (!buffer_string_a)
    {
        *old_string_a = '\0';
    }
    return buffer_string_a;
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
        output_num = (int) va_arg(*valist_args_d, int);
    }

    // если %d
    else
    {
        // то прост кастим его в инт (однако 'int' и 'short int' это одно и то же)
        output_num = (int) va_arg(*valist_args_d, int);
    }

    s21_size_t buffer_size = 0;
    buffer_size = get_width_decimal(&specs_d, output_num); // узнаём ширину поля вывода

    char *str_to_num = calloc(buffer_size, sizeof(char));  // маллочим/каллочим память

    if (str_to_num != NULL) // проверка выделения памяти
    {
        int i = 0;
        i = cast_decimal_to_string(specs_d, output_num, str_to_num, buffer_size);

        // это кажется обычный принт-вывод
        for (int k = i - 1; k >= 0 ; k--)
        {
            *bfr_str = str_to_num[k];
            bfr_str++;
        }
        
        // а это сценарий принта с спцфктром minus_align_left..
        while((i < specs_d.width))
        {
            *bfr_str = ' ';
            bfr_str++;
        }
    }
    
    if (str_to_num)
    {
        free(str_to_num);
    }
    
    return bfr_str;
}

// (третичная) функция для print_decimal
s21_size_t get_width_decimal(struct_sprintf_specs *specs_e, long int num)
{
    s21_size_t result = 0;
    long int num_copy = num;

    // если каким-то образом оно пришло отрицтлнм, делаем его плжтлнм
    if (num_copy < 0)
        num_copy = -num_copy; 
    
    // узнаём какое это число - однозначное, или двузначное, или трехзначное и тд
    while (num_copy > 0)
    {
        num_copy = num_copy / 10;
        result++;
    }

    // если спецификаторов ширины нет, то надо выделить один символ под вывод
    if(num_copy == 0 && result == 0 && (specs_e->float_accuracy || specs_e->width || specs_e->space_is_present))
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
    if (specs_e->space_is_present|| specs_e->plus_show_positv_negtv || num < 0)
    {
        specs_e->plus_or_space_present = true;
        result++;
    }

    // если в переменной '0', и числа ширины поля нет, и пробела нет, и точки тоже нет
    if (result == 0 && num_copy == 0 && !specs_e->float_accuracy && !specs_e->width && !specs_e->space_is_present&& !specs_e->dot_is_present)
    {
        result++; // то всё равно надо выделить одну ячейку под вывод этого нуля
    }
    return result;
}

// (третичная) функция для print_decimal
int cast_decimal_to_string(struct_sprintf_specs specs_f, long int num, char *str_to_num, s21_size_t buffer_size_a)
{
    bool is_num_negative = false; // по дефолту предпологаем что число позитивное

    // проверка на отрицательное число, это нужно чтоб получить модулус и провести логику, 
    // так как с отриц числом этого не сделать
    if (num < 0)
    {
        is_num_negative = true;
        num = -num; // и преобразование в положительное, на пока что
    }

    int loop_i = 0;
    long int copy_num = num;
    char sym;
    
    // Если, (в num 0, и (число дробной точности больше нуля, или число ширины больше нуля, или есть пробел))
    //        или (в num 0, и спецификаторов точности, ширины, и пробела, и точки НЕТ)
    // Если записан '0' крч говоря
    if ((copy_num = 0 && (specs_f.float_accuracy || specs_f.width || specs_f.space_is_present)) ||
    (copy_num == 0 && !specs_f.float_accuracy && !specs_f.width && !specs_f.space_is_present && !specs_f.dot_is_present))
    {
        // нужно из-за конверта int в char, и опять же логики ASCII
        sym = copy_num % specs_f.number_system + '0';

        str_to_num[loop_i] = sym;  // записываем в строку вывода
        loop_i++;
        buffer_size_a--;           // уменьшаем потомучт 1 символ уже записали
        copy_num = copy_num / 10;
    }

    // пока эти 3 переменные положительные 
    while(copy_num && str_to_num && buffer_size_a) 
    {
        // основная логика через '%' модулус 
        char sym = get_num_char(copy_num % specs_f.number_system, specs_f.is_upper_case);

        str_to_num[loop_i] = sym;
        loop_i++;
        buffer_size_a--;
        copy_num = copy_num / 10;
    }

    // конвертируем обратно если число было отрацительное
    if (is_num_negative == true)
    {
        num = -num;
    }

    // проверка на спецификатор '0'  (sprintf("%0d");)
    if (specs_f.float_accuracy - loop_i > 0)
    {
        specs_f.float_accuracy = specs_f.float_accuracy - loop_i;
        specs_f.fill_w_nulls = 1;
    }

    else
    is_num_negative = true;

    // если флаг ноль включён (sprintf("%04d", 293);) но в выводе нет места под этот нуль
    // то важно выключить этот флаг
    if (buffer_size_a == 1 && specs_f.fill_w_nulls == true && specs_f.plus_or_space_present == true)
    specs_f.fill_w_nulls = 0;

    // обработка спецфктра '0'. пока есть место в буфере и выполняются условия
    while(specs_f.fill_w_nulls && str_to_num && (buffer_size_a - specs_f.plus_or_space_present > 0) && (specs_f.float_accuracy || is_num_negative))
    {
        if (buffer_size_a == 1 && specs_f.plus_or_space_present == true)
        {
            break;
        }
        else
        {
            str_to_num[loop_i] = '0';
            loop_i++;
            buffer_size_a--;
            specs_f.float_accuracy--;
        }
    }

    // обработка спецфктра пробел
    if (specs_f.space_is_present == true && num >= 0 && buffer_size_a)
    {
        str_to_num[loop_i] = ' ';
        loop_i++;
        buffer_size_a--;
    }

    // обработка спцктра минус
    if (num < 0 && buffer_size_a)
    {
        str_to_num[loop_i] = '-';
        loop_i++;
        buffer_size_a--;
    }

    // обработка спцфктра плюс
    if (num < 0 && specs_f.plus_show_positv_negtv && buffer_size_a)
    {
        str_to_num[loop_i] = '+';
        loop_i++;
        buffer_size_a--;
    }

    // процессинг ситуации, когда осталось свободное место в строке
    if (buffer_size_a > 0 && specs_f.minus_align_left == false)
    {
        while((buffer_size_a - specs_f.plus_or_space_present > 0) && str_to_num)
        {
            str_to_num[loop_i] = ' ';
            loop_i++;
            buffer_size_a--;
        }
    }
    return loop_i;
}

// (четвертиричная) функция преобразования int в char
char get_num_char(int num, int is_upper_case)
{
    char ch = '0';

    // если HEXADECIMAL (шестнадцатиричная)
    switch (num)
    {
        case 10:
        ch = (char)('a' - is_upper_case * 32);
        break;

        case 11:
        ch = (char)('b' - is_upper_case * 32);
        break;

        case 12:
        ch = (char)('c' - is_upper_case * 32);
        break;

        case 13:
        ch = (char)('d' - is_upper_case * 32);
        break;

        case 14:
        ch = (char)('e' - is_upper_case * 32);
        break;

        case 15:
        ch = (char)('f' - is_upper_case * 32);
        break;

    }

    // если DECIMAL (десятиричная)
    if (0 <= num && num <= 9)
    {
        ch = (char)(num + 48);
    }

    return ch;
}

struct_sprintf_specs set_number_system (struct_sprintf_specs specs_g, char FORMAT_E)
{
    // o для 8ричной системы
    if (FORMAT_E == 'o')
    specs_g.number_system = 8;

    // x или X для 16ричной
    else if (FORMAT_E == 'x' || FORMAT_E == 'X')
    {
        specs_g.number_system = 16;
    }

    // и если большой Х, то надо писать капсом
    if (FORMAT_E == 'X')
    {
        specs_g.is_upper_case = true;
    }

    return specs_g;
}

char *print_u(char *bfr_str, struct_sprintf_specs specs_e, char FORMAT_F, va_list *valist_args_e)
{
    unsigned long int num = 0;
    if (FORMAT_F == 'l')
        num = (unsigned long int)va_arg (*valist_args_e, unsigned long int);
    
    if (FORMAT_F = 'h')
        num = (unsigned short)va_arg (*valist_args_e, unsigned int);

    else
        num = (unsigned int)va_arg (*valist_args_e, unsigned int);

    s21_size_t size_to_num = get_buf_size_unsigned_decimal(specs_e, num);
    char *buffer = malloc(sizeof(char) * size_to_num);
    
    int i = 0;
    if (buffer) 
    {
        i = cast_Udecimal_to_string(buffer, specs_e, num, size_to_num);
    }

    if (buffer)
    free(buffer);
    return bfr_str;
}

int cast_Udecimal_to_string(char *buffer, struct_sprintf_specs specs, unsigned long int num, s21_size_t size_to_num)
{
    int i = 0;
    int flag = 0;
    unsigned long int copy_num = num;

}

s21_size_t get_width__Udecimal(struct_sprintf_specs *specs_e, long int num)
{
    s21_size_t result = 0;
    long int num_copy = num;

    // если каким-то образом оно пришло отрицтлнм, делаем его плжтлнм
    if (num_copy < 0)
        num_copy = -num_copy; 
    
    // узнаём какое это число - однозначное, или двузначное, или трехзначное и тд
    while (num_copy > 0)
    {
        num_copy = num_copy / 10;
        result++;
    }

    // если спецификаторов ширины нет, то надо выделить один символ под вывод
    if(num_copy == 0 && result == 0 && (specs_e->float_accuracy || specs_e->width || specs_e->space_is_present))
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
    if (specs_e->space_is_present|| specs_e->plus_show_positv_negtv || num < 0)
    {
        specs_e->plus_or_space_present = true;
        result++;
    }

    // если в переменной '0', и числа ширины поля нет, и пробела нет, и точки тоже нет
    if (result == 0 && num_copy == 0 && !specs_e->float_accuracy && !specs_e->width && !specs_e->space_is_present&& !specs_e->dot_is_present)
    {
        result++; // то всё равно надо выделить одну ячейку под вывод этого нуля
    }
    return result;
}

