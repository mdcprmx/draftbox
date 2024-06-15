#include "s21_sprintf_lib.h"
// line 30 

// три точки (...) на 10 строке в функции s21_sprintf для получения аргументов 
//               речь про вот эти ниже:  |    |        |
//                                       v    v        v
// например - sprintf(string,"%d %c %f", num, char, float_num);
// тоесть три точки указывают на третий элемент, часть после второй запятой
// и говорят про то что их может быть сколько угодно
int s21_sprintf(char *buffer_string, const char *FORMAT, ...)
{
    // old_string нужен для return-a. чтоб узнать скок символов мы записали
    char *old_string = buffer_string;
    const char specs_options[] = "diuocsnpXxGgEeFf"; // все возможные спецфктры


    va_list valist_args;           // (...) аргументы летят сюда, в эту структуру
    va_start(valist_args, FORMAT); // 1-ым идёт то что запускается, (да, их надо "запускать") 
                                   // 2-ым идёт переменная из функции после которой начинать искать аргументы

    while(*FORMAT) // пока не дошли до конца форматной строки // "while format is true"
    {
        if (*FORMAT == '%')  // если в форматной строке видим процент, то начинаем обработку
        {
            FORMAT++;        // крутим цикл по всем символам
            struct_sprintf_specs specfctrs = {0}; // заполняем нулями
            specfctrs.number_system = 10;         // десятиричная система по дефолту
            FORMAT = set_specs(FORMAT, &valist_args, &specfctrs); // вызываем set_specs и передаём туда спецы,
                                                                  // строку формата, и указатель на валист.
            // 36 minutes
            while ()

        }

        else                 // если же процента нет, то это просто текст
        {
            *buffer_string = *FORMAT;
            buffer_string++;
        }   
        
    }



    *buffer_string = '\0';         // заполняем нулями?
    va_end(valist_args);           // заканчиваем работу va_list 
    return(buffer_string - old_string); // возвращаем кол-во записанных символов
}

const char *set_specs(const char *FORMAT_A, va_list valist_args_a, struct_sprintf_specs *specs_a)
{
    FORMAT_A = funct_specs_switcher(FORMAT_A, specs_a); // обрабатываем наличие '+-#0 ' (и пробел тож)
    FORMAT_A = funct_process_width(FORMAT_A, valist_args_a, &specs_a->width); // ищем цифру ширины или '*' (до точки)

    if (*FORMAT_A == '.') // ищем точку, для float точности
    {
        specs_a->dot_is_present = 1;
        specs_a->zero = 0; // не может быть одновременно и '.' и '0', поэтому zero обнуляем
        FORMAT_A = FORMAT_A + 1;
        
        // в этом случае запуск поиска ширины произойдёт после '.', поэтому отправляем float_accuracy
        FORMAT_A = funct_process_width(FORMAT_A, valist_args_a, &specs_a->float_accuracy);
        // а вообще это гениальное переиспользование кода!
    }
    // funct_get_length START (можно создать отдельную функцию для этой части)
    if(*FORMAT_A == 'H')
        specs_a->var_length = 'H';
    
    else if (*FORMAT_A == 'h')
        specs_a->var_length = 'h';

    else if(*FORMAT_A == 'L')
        specs_a->var_length = 'L';

    else if (*FORMAT_A == 'l')
        specs_a->var_length = 'l';
    

    if (specs_a->var_length != 0)  // если длинна обычная (тоесть НЕ используется спцфктр %ld, %Ld, %hd, %hf и тд)
        FORMAT_A = FORMAT_A + 1;   // то в конце надо передвинуться на след символ
    // funct_get_length END

    // защита, если funct_process_width сработает с ошибкой (а ваще эта if-ка необяз)
    if(specs_a->width < 0)
    {
        specs_a->width = -specs_a->width;
        specs_a->minus_align_left = 1;
    }

    return FORMAT_A;
}

// переключалка наличия спецификаторов в форматной строке
const char *funct_specs_switcher(const char *FORMAT_B, struct_sprintf_specs *specs_b)
{
    while(FORMAT_B)  // пока переменная FORMAT_B положительна
    {
        if (*FORMAT_B == '+') 
        specs_b->plus_positv_negtv = 1;

        else if (*FORMAT_B == '-') 
        specs_b->minus_align_left = 1;

        else if (*FORMAT_B == '#')
        specs_b->reshetka_hexidecimal = 1;

        else if (*FORMAT_B == ' ')
        specs_b->space = 1;

        else if (*FORMAT_B == '0')
        specs_b->zero = 1;
        
        else         // если форматная строка кончилась, то цикл кончаем
        {
            break;
        }
        FORMAT_B++;  // крутит цикл
    }

    // если одновременно и плюс и пробел
    specs_b->space = (specs_b->space && !specs_b->plus_positv_negtv);

    // если одновременно и ноль и минус
    specs_b->zero = (specs_b->zero && !specs_b->minus_align_left);
    return FORMAT_B;
}

// обрабатываем цифры в форматной строке, типа "sprintf("%14.d", num);" 
const char *funct_process_width(const char *FORMAT_C, va_list *valist_args_b, int *width_from_specs)
{
    *width_from_specs = 0; // по дефолту 0
    if (*FORMAT_C == '*')  // если звёзда, то надо взять ширину строки из первого аргумента
    {                      // например (sprintf("%*d", 69, num);) - в этом примере оно возьмёт 69
        *width_from_specs = va_arg(*valist_args_b, int); // ожидает что первое число будет int
                                                         // и записывает его в наш valist_args
        FORMAT_C++;  // проверяет всю строку получаетс
    }
    
    while (FORMAT_C) // начинает бежать по всей строке
    {
        if ('0' <= *FORMAT_C && *FORMAT_C <= '9') // если символ является цифрой (по ASCII от 48 до 57)
        {
            *width_from_specs = *width_from_specs * 10;  // эт умножение
            *width_from_specs = width_from_specs + *FORMAT_C - '0'; // у нуля по ASCII число 48
            // почему решение именно такое? яхз, там какаят сложная математика связанная с ASCII
            // суть в том что FORMAT эт не int, это char.
        }

        else break; // если же символ не цифра, то брейкаемся.
        FORMAT_C++;
    }
    return FORMAT_C;
}




