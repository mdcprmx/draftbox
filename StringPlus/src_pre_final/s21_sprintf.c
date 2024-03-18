#include "s21_sprintf_lib.h"

void s21_sprintf(char *buffer, const char *format, ...) {
  va_list args;
  va_start(args, format);  // Инициализация списка аргументов

  // Цикл обработки всего форматируемого текста
  while (*format) {
    if (*format != '%') {
      *buffer = *format;  // Добавляем символ в буффер
      buffer++;           // Увеличиваем адрес буффера
      format++;  // Переходим к следующему символу формата
      continue;
    }
    // Пропускаем символ %
    format++;
    flags opt = {0};
    struct_specfrs specs = {0};
    int ch = 0;

    // Флаги
    while (*format == '-' || *format == '+' || *format == ' ' ||
           *format == '#' || *format == '0') {
      if (*format == '-') {
        opt.minus_align_left = 1;   // Флаг выравнивания по левому краю
      } else if (*format == '+') {
        opt.plus_show_sign = 1;     // Флаг показа знака
      } else if (*format == ' ') {
        opt.fill_w_space = 1;       // Флаг заполнения пробелами
      } else if (*format == '#') {
        opt.reshetka_hexidcml = 1;  // Флаг добавления префикса
      } else if (*format == '0') {
        opt.fill_w_nulls = 1;       // Флаг заполнения нулями
      }
      format++;
    }
    if (opt.plus_show_sign && opt.fill_w_space) opt.plus_show_sign = 0;
    if (opt.fill_w_nulls && opt.minus_align_left) opt.minus_align_left = 0;

    // Ширина
    format = main_get_width(format, &specs.width, &args);

    // Точность
    specs.float_accuracy = 0;
    if (*format == '.') {
      specs.dot = 1;
      format += 1;
      format = main_get_width(format, &specs.float_accuracy, &args);
    }

    // Длина
    if (*format == 'L')
      specs.length = 'L';
    else if (*format == 'l')
      specs.length = 'l';
    else if (*format == 'h')
      specs.length = 'h';
    if (specs.length != 0) format += 1;

    if (specs.width < 0) {
      specs.width = -specs.width;
      opt.minus_align_left = 1;
    }

    // Спецификатор
    switch (*format) {
      case 'c':
        specs.c = (char)va_arg(args, int);
        buffer = main_print_char(buffer, specs.c, opt, specs, &ch);
        break;
      case 'd':
        specs.number_system = 10;
        buffer = main_print_int(buffer, &args, opt, specs);
        break;
      case 'f':
        buffer = main_print_float(buffer, &args, opt, specs);
        break;
      case 's':
        buffer = main_print_string(buffer, &args, opt, specs);
        break;
      case 'u':
        buffer = main_print_Uint(buffer, &args, opt, specs);
        break;
      case '%':
        buffer = main_print_char(buffer, '%', opt, specs, &ch);
        break;
      case 'e':
        specs.e_small = 1;
        buffer = main_print_float(buffer, &args, opt, specs);
        break;
      case 'E':
        specs.E_big = 1;
        specs.is_upper_case = 1;
        buffer = main_print_float(buffer, &args, opt, specs);
        break;
      case 'x':
        specs.x = 1;
        specs.number_system = 16;
        buffer = main_print_hex(buffer, &args, opt, specs);
        break;
      case 'X':
        specs.X = 1;
        specs.number_system = 16;
        specs.is_upper_case = 1;
        buffer = main_print_hex(buffer, &args, opt, specs);
        break;
      case 'o':
        specs.o = 1;
        specs.number_system = 8;
        buffer = main_print_octal(buffer, &args, opt, specs);
        break;
      case 'p':
        specs.ptr = 1;
        buffer = main_print_ptr(buffer, &args, opt, specs);
        break;
      case 'i':
        specs.number_system = 10;
        buffer = main_print_int(buffer, &args, opt, specs);
        break;
    }
    if (ch == 1) break;
    format++;
  }
  *buffer = '\0';  // Добавляем завершающий нуль символ для завершения строки
  va_end(args);  // Завершаем работу со списком аргументов
}

// принтим символ
char *main_print_char(char *buffer, char sym, flags opt, struct_specfrs specs,
                  int *ch) {
  while (specs.width - 1 > 0 && !opt.minus_align_left) {
    *buffer = ' ';
    buffer++;
    specs.width--;
  }
  if (sym != 0) {
    *buffer = sym;
    buffer++;
    while (specs.width - 1 > 0 && opt.minus_align_left) {
      *buffer = ' ';
      buffer++;
      specs.width--;
    }
  } else {
    *ch = 1;
  }
  return buffer;
}

// принтим строку %s 
char *main_print_string(char *buffer, va_list *args, flags opt, struct_specfrs specs) {
  char *ptr = buffer;
  char *str = va_arg(*args, char *);
  if (str) {
    int tmp = specs.width, i = 0;
    if ((s21_size_t)specs.width < s21_strlen(str))
      specs.width = s21_strlen(str);
    int space = specs.width - s21_strlen(str);
    if (specs.float_accuracy == 0 && !specs.dot) specs.float_accuracy = specs.width;
    if (specs.float_accuracy != 0 && specs.float_accuracy < tmp)
      space = tmp - specs.float_accuracy;
    while (space && !opt.minus_align_left) {
      *buffer = ' ';
      buffer++;
      space--;
    }
    while (*str != '\0') {
      if (!specs.float_accuracy) break;
      *buffer = *str;
      buffer++;
      str++;
      i++;
      specs.float_accuracy--;
    }
    while (space && opt.minus_align_left) {
      *buffer = ' ';
      buffer++;
      space--;
    }
  } else {
    if (specs.width > 6) {
      int space = specs.width - 6;
      while (space && !opt.minus_align_left) {
        *buffer = ' ';
        buffer++;
        space--;
      }
      buffer = s21_memcpy(buffer, "(null)", 6);
      buffer += 6;
      while (space && opt.minus_align_left) {
        *buffer = ' ';
        buffer++;
        space--;
      }
    } else {
      buffer = s21_memcpy(buffer, "(null)", 6);
      buffer += 6;
    }
  }
  if (ptr) ptr = buffer;
  return ptr;
}

// принтим целое число %d или %i
char *main_print_int(char *buffer, va_list *args, flags opt, struct_specfrs specs) {
  long int num = 0;
  if (specs.length == 'l') {
    num = (long int)va_arg(*args, long int);
  } else if (specs.length == 'h') {
    num = (short)va_arg(*args,
                        int);  //должно быть: num = (short)va_arg(*args, short);
  } else {
    num = (int)va_arg(*args, int);
  }
  s21_size_t size_to_decimal = get_size_to_decimal(&specs, &opt, num);
  char *temp = malloc(sizeof(char) * size_to_decimal);
  if (temp) {
    int i = int_to_string(num, temp, specs, size_to_decimal, opt);
    for (int j = i - 1; j >= 0; j--) {
      *buffer = temp[j];
      buffer++;
    }
    while (i < specs.width) {
      *buffer = ' ';
      buffer++;
      i++;
    }
  }
  if (temp) free(temp);
  return buffer;
}

// принтим дробное число %f
char *main_print_float(char *buffer, va_list *args, flags opt, struct_specfrs specs) {
  long double num = 0;
  if (specs.length == 'L') {
    num = va_arg(*args, long double);
  } else
    num = va_arg(*args, double);

  s21_size_t size_to_double = get_size_to_double(&specs, &opt, num);
  char *temp = malloc(sizeof(char) * size_to_double);
  if (temp) {
    int i = float_to_string(num, temp, specs, size_to_double, opt);
    for (int j = i - 1; j >= 0; j--) {
      *buffer = temp[j];
      buffer++;
    }
    while (i < specs.width) {
      *buffer = ' ';
      buffer++;
      i++;
    }
  }
  if (temp) free(temp);
  return buffer;
}

// принтим необрезанное целое число %u
char *main_print_Uint(char *buffer, va_list *args, flags opt,
                      struct_specfrs specs) {
  unsigned long int num = 0;
  if (specs.length == 'l') {
    num = (unsigned long int)va_arg(*args, unsigned long int);
  } else if (specs.length == 'h') {
    num = (unsigned short)va_arg(
        *args, unsigned int);  //должно быть: num = (short)va_arg(*args, short);
  } else {
    num = (unsigned int)va_arg(*args, unsigned int);
  }
  s21_size_t size_to_unsigned = get_size_to_unsigned(&specs, &opt, num);
  char *temp = malloc(sizeof(char) * size_to_unsigned);
  if (temp) {
    int i = unsigned_to_string(num, temp, specs, size_to_unsigned, opt);
    for (int j = i - 1; j >= 0; j--) {
      *buffer = temp[j];
      buffer++;
    }
    while (i < specs.width) {
      *buffer = ' ';
      buffer++;
      i++;
    }
  }
  if (temp) free(temp);
  return buffer;
}

// принтим HEXADECIMAL, 16 ричное чилсо
char *main_print_hex(char *buffer, va_list *args, flags opt, struct_specfrs specs) {
  unsigned long int num = 0;
  if (specs.length == 'l') {
    num = (unsigned long int)va_arg(*args, unsigned long int);
  } else if (specs.length == 'h') {
    num = (unsigned short)va_arg(
        *args, unsigned int);  //должно быть: num = (short)va_arg(*args, short);
  } else {
    num = (unsigned int)va_arg(*args, unsigned int);
  }
  s21_size_t size_to_unsigned = get_size_to_unsigned(&specs, &opt, num);
  char *temp = malloc(sizeof(char) * size_to_unsigned);
  if (temp) {
    int i = hex_to_string(num, temp, specs, size_to_unsigned, opt);

    for (int j = i - 1; j >= 0; j--) {
      *buffer = temp[j];
      buffer++;
    }
    while (i < specs.width) {
      *buffer = ' ';
      buffer++;
      i++;
    }
  }
  if (temp) free(temp);
  return buffer;
}

// принтим OCTADECIMAL, 8-ричное число
char *main_print_octal(char *buffer, va_list *args, flags opt, struct_specfrs specs) {
  unsigned long int num = 0;
  if (specs.length == 'l') {
    num = (unsigned long int)va_arg(*args, unsigned long int);
  } else if (specs.length == 'h') {
    num = (unsigned short)va_arg(
        *args, unsigned int);  //должно быть: num = (short)va_arg(*args, short);
  } else {
    num = (unsigned int)va_arg(*args, unsigned int);
  }
  s21_size_t size_to_unsigned = get_size_to_unsigned(&specs, &opt, num);
  char *temp = malloc(sizeof(char) * size_to_unsigned);
  if (temp) {
    int i = octal_to_string(num, temp, specs, size_to_unsigned, opt);
    for (int j = i - 1; j >= 0; j--) {
      *buffer = temp[j];
      buffer++;
    }
    while (i < specs.width) {
      *buffer = ' ';
      buffer++;
      i++;
    }
  }
  if (temp) free(temp);
  return buffer;
}

// принтим указатель
char *main_print_ptr(char *buffer, va_list *args, flags opt, struct_specfrs specs) {
  unsigned long int num = (unsigned long int)va_arg(*args, unsigned long int);
  specs.number_system = 16;
  opt.reshetka_hexidcml = 1;
  specs.is_upper_case = 0;

  s21_size_t size_to_unsigned = get_size_to_unsigned(&specs, &opt, num);
  char *temp = malloc(sizeof(char) * size_to_unsigned);
  if (temp) {
    int i = hex_to_string(num, temp, specs, size_to_unsigned, opt);
    for (int j = i - 1; j >= 0; j--) {
      *buffer = temp[j];
      buffer++;
    }
    while (i < specs.width) {
      *buffer = ' ';
      buffer++;
      i++;
    }
  }
  if (temp) free(temp);
  return buffer;
}

// получаем ширину
const char *main_get_width(const char *format, int *width, va_list *args) {
  if (*format == '*') {
    *width = va_arg(*args, int);
    format++;
  }
  while (format) {
    if ('0' <= *format && *format <= '9') {
      *width *= 10;
      *width += *format - '0';
    } else
      break;
    format++;
  }
  return format;
}

// число в чар, для 16-ричной
char get_num_char(int num, int is_upper_case) {
  char flag = '0';
  switch (num) {
    case 10:
      flag = (char)('a' - is_upper_case * 32);
      break;
    case 11:
      flag = (char)('a' - is_upper_case * 32);
      break;
    case 12:
      flag = (char)('a' - is_upper_case * 32);
      break;
    case 13:
      flag = (char)('a' - is_upper_case * 32);
      break;
    case 14:
      flag = (char)('a' - is_upper_case * 32);
      break;
    case 15:
      flag = (char)('a' - is_upper_case * 32);
      break;
  }
  if (0 <= num && num <= 9) flag = (char)(num + 48);
  return flag;
}

// кастим инту в стрингу, преобразуем
int int_to_string(long int num, char *buffer, struct_specfrs specs,
                  s21_size_t size_to_decimal, flags opt) {
  int i = 0;
  long int n = num;
  int flag = 0;

  // обработка отрицательных чисел
  if (num < 0) {
    flag = 1;
    n = -n;
  }

  // если число = 0
  if ((num == 0 && (specs.float_accuracy || specs.width || opt.fill_w_space)) ||
      (num == 0 && !specs.float_accuracy && !specs.width && !opt.fill_w_space &&
       !specs.dot)) {
    if (specs.dot && specs.float_accuracy == 0) {
      char sym = ' ';
      buffer[i] = sym;
      i++;
      size_to_decimal--;
      n /= 10;
    } else {
      char sym = n % 10 + '0';
      buffer[i] = sym;
      i++;
      size_to_decimal--;
      n /= 10;
    }
  }

  // Если число != 0
  while (n && buffer && size_to_decimal) {
    char sym = get_num_char(n % specs.number_system, specs.is_upper_case);
    buffer[i] = sym;
    i++;
    size_to_decimal--;
    n /= 10;
  }
  if (flag) n = -n;
  if (specs.float_accuracy - i > 0) {
    specs.float_accuracy -= i;
    opt.fill_w_nulls = 1;
  } else
    flag = 1;

  // Если у нас нет места для нулей
  if (size_to_decimal == 1 && opt.fill_w_nulls == 1 && specs.flag_to_size == 1)
    opt.fill_w_nulls = 0;

  // Обработка флага 0
  while (opt.fill_w_nulls && buffer && (size_to_decimal - specs.flag_to_size > 0) &&
         (specs.float_accuracy || flag)) {
    if ((size_to_decimal == 1 && specs.flag_to_size == 1)) break;
    if (specs.dot && specs.float_accuracy < specs.width) {
      if (specs.float_accuracy == 0) break;
    }
    buffer[i] = '0';
    i++;
    size_to_decimal--;
    specs.float_accuracy--;
  }

  // Обработка флагов +/-/пробел
  if (opt.fill_w_space && num >= 0 && size_to_decimal) {
    buffer[i] = ' ';
    i++;
    size_to_decimal--;
  }

  if (num < 0 && size_to_decimal) {
    buffer[i] = '-';
    i++;
    size_to_decimal--;
  }
  if (num >= 0 && opt.plus_show_sign && size_to_decimal) {
    buffer[i] = '+';
    i++;
    size_to_decimal--;
  }

  // Обработка ситуации, когда осталось свободное место
  if (size_to_decimal > 0 && opt.minus_align_left == 0) {
    while (size_to_decimal != 0 && buffer) {
      buffer[i] = ' ';
      i++;
      size_to_decimal--;
    }
  }
  return i;
}

// кастим дробное число в строку, преобразуем крч
int float_to_string(long double num, char *buffer, struct_specfrs specs,
                    s21_size_t size_to_double, flags opt) {
  long double n = num;
  int i = 0;
  int flag = 0;
  int exp = 0;
  int flag_e = 0;
  long long int int_part = 0;
  long double float_part = 0;

  if (isnan(num)) {
    buffer[i++] = 'n';
    buffer[i++] = 'a';
    buffer[i++] = 'n';
    return i;
  }
  if (num == INFINITY || num == -INFINITY) {
    buffer[i++] = 'f';
    buffer[i++] = 'n';
    buffer[i++] = 'i';
    if (num == -INFINITY) buffer[i++] = '-';
    return i;
  }

  if (specs.e_small || specs.E_big) {
    if (n != 0) {
      while (n >= 10.0 || n <= -10.0) {
        n /= 10.0;
        exp++;
      }
      while (n < 1.0 && n > -1.0) {
        n *= 10.0;
        exp++;
        flag_e = 1;
      }
    }
    int_part = (int)n;
    float_part = n - int_part;
  } else {
    int_part = (long long int)n;
    float_part = n - int_part;
  }

  // Если число < 0
  if (num < 0) {
    int_part = -int_part;
    float_part = -float_part;
    flag = 1;
  }

  // Преобразование дробной части числа в строку
  if (specs.e_small || specs.E_big) {
    if (exp < 10) {
      while (exp != 0) {
        char sym = exp % 10 + '0';
        buffer[i++] = sym;
        exp /= 10;
        size_to_double--;
      }
      buffer[i++] = '0';
      size_to_double--;
      if (num == 0) {
        buffer[i++] = '0';
        size_to_double--;
      }
    } else {
      while (exp != 0) {
        char sym = exp % 10 + '0';
        buffer[i++] = sym;
        exp /= 10;
        size_to_double--;
      }
    }
    if (!flag_e) {
      buffer[i++] = '+';
      size_to_double--;
    } else {
      buffer[i++] = '-';
      size_to_double--;
      exp = -exp;
    }
  }

  if (specs.e_small) {
    buffer[i++] = 'e';
    size_to_double--;
  }
  if (specs.E_big) {
    buffer[i++] = 'E';
    size_to_double--;
  }

  if (!specs.dot) specs.float_accuracy = 6;

  if (num != 0) {
    if (specs.dot && specs.float_accuracy == 0) {
    } else {
      int check_zero = 0;
      for (int t = 0; t < specs.float_accuracy; t++) {
        float_part *= 10;
        if ((int)float_part == 0) {
          check_zero = 1;
        }
      }

      long long int fractional_part = roundl(float_part);
      while (fractional_part > 0) {
        buffer[i++] = '0' + fractional_part % 10;
        fractional_part /= 10;
        size_to_double--;
      }
      if (check_zero && float_part) {
        buffer[i++] = '0' + fractional_part % 10;
        size_to_double--;
      }
      if (float_part == 0) {
        for (int t = 0; t < specs.float_accuracy; t++) {
          buffer[i++] = '0' + (int)float_part;
          size_to_double--;
        }
      }
    }
  } else {
    for (int t = 0; t < specs.float_accuracy; t++) {
      buffer[i++] = '0' + (int)n;
      size_to_double--;
    }
  }

  if (specs.dot && specs.float_accuracy == 0 && !opt.reshetka_hexidcml) {
  } else {
    buffer[i++] = '.';
    size_to_double--;
  }

  if (specs.dot && specs.float_accuracy == 0) {
    if ((float_part * 10) > 4) int_part += 1;
  }

  if ((int_part == 0 && (specs.float_accuracy || specs.width || opt.fill_w_space)) ||
      (int_part == 0 && !specs.float_accuracy && !specs.width && !opt.fill_w_space)) {
    char sym = int_part % 10 + '0';
    buffer[i] = sym;
    i++;
    size_to_double--;
    int_part /= 10;
  }

  // Преобразование целой части числа в строку
  while (int_part && buffer && size_to_double) {
    char sym = int_part % 10 + '0';
    buffer[i] = sym;
    i++;
    size_to_double--;
    int_part /= 10;
  }

  if (specs.float_accuracy - i > 0) {
    specs.float_accuracy -= i;
    opt.fill_w_nulls = 1;
  } else
    flag = 1;

  // Если у нас нет места для нулей
  if (size_to_double == 1 && opt.fill_w_nulls == 1 && specs.flag_to_size == 1)
    opt.fill_w_nulls = 0;

  // Обработка флага 0
  while (opt.fill_w_nulls && buffer && (size_to_double - specs.flag_to_size > 0) &&
         (specs.float_accuracy || flag)) {
    if ((size_to_double == 1 && specs.flag_to_size == 1)) break;
    buffer[i] = '0';
    i++;
    size_to_double--;
    specs.float_accuracy--;
  }

  // Обработка флагов +/пробел
  if (opt.fill_w_space && num >= 0 && size_to_double) {
    buffer[i] = ' ';
    i++;
    size_to_double--;
  }
  if (num < 0 && size_to_double) {
    buffer[i] = '-';
    i++;
    size_to_double--;
  }
  if (num >= 0 && opt.plus_show_sign && size_to_double) {
    buffer[i] = '+';
    i++;
    size_to_double--;
  }

  // Обработка ситуации, когда осталось свободное место
  if (size_to_double > 0 && opt.minus_align_left == 0) {
    while (size_to_double != 0 && buffer) {
      buffer[i] = ' ';
      i++;
      size_to_double--;
    }
  }
  return i;
}

// кастим Uint в стрингу, bruh
int unsigned_to_string(unsigned long int num, char *buffer, struct_specfrs specs,
                       s21_size_t size_to_unsigned, flags opt) {
  int i = 0;
  int flag = 0;
  unsigned long int n = num;

  if ((opt.reshetka_hexidcml && specs.number_system == 8))
    specs.flag_to_size = 1;
  else if (opt.reshetka_hexidcml && specs.number_system == 16)
    specs.flag_to_size = 2;

  // Если число = 0
  if ((num == 0 && (specs.float_accuracy || specs.width || opt.fill_w_space)) ||
      (num == 0 && !specs.float_accuracy && !specs.width && !opt.fill_w_space &&
       !specs.dot)) {
    if (specs.dot && specs.float_accuracy == 0) {
      char sym = ' ';
      buffer[i] = sym;
      i++;
      size_to_unsigned--;
      n /= 10;
    } else {
      char sym = n % 10 + '0';
      buffer[i] = sym;
      i++;
      size_to_unsigned--;
      n /= 10;
    }
  }

  // Если число != 0
  while (n && buffer && size_to_unsigned) {
    char sym = n % 10 + '0';
    buffer[i] = sym;
    i++;
    size_to_unsigned--;
    n /= 10;
  }
  if (flag) n = -n;
  if (specs.float_accuracy - i > 0) {
    specs.float_accuracy -= i;
    opt.fill_w_nulls = 1;
  } else
    flag = 1;

  // Если у нас нет места для нулей
  if (size_to_unsigned == 1 && opt.fill_w_nulls == 1 && specs.flag_to_size == 1)
    opt.fill_w_nulls = 0;

  // Обработка флага 0
  while (opt.fill_w_nulls && buffer &&
         (size_to_unsigned - specs.flag_to_size > 0) &&
         (specs.float_accuracy || flag)) {
    if ((size_to_unsigned == 1 && specs.flag_to_size == 1)) break;
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
    specs.float_accuracy--;
  }

  // Обработка #/o/x/X
  if (opt.reshetka_hexidcml && specs.number_system == 8) {
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
  } else if (opt.reshetka_hexidcml && specs.number_system == 16 && specs.is_upper_case) {
    buffer[i] = 'X';
    i++;
    size_to_unsigned--;
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
  } else if (opt.reshetka_hexidcml && specs.number_system == 16 && !specs.is_upper_case) {
    buffer[i] = 'x';
    i++;
    size_to_unsigned--;
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
  }

  // Обработка ситуации, когда осталось свободное место
  if (size_to_unsigned > 0 && opt.minus_align_left == 0) {
    while ((size_to_unsigned - specs.flag_to_size > 0) && buffer) {
      buffer[i] = ' ';
      i++;
      size_to_unsigned--;
    }
  }

  return i;
}

// кастим 8-ричное число в стрингу
int octal_to_string(unsigned long int num, char *buffer, struct_specfrs specs,
                    s21_size_t size_to_unsigned, flags opt) {
  char octal_digits[] = "01234567";
  int i = 0;
  int flag = 0;

  if ((opt.reshetka_hexidcml && specs.number_system == 8)) specs.flag_to_size = 1;

  if (num == 0) {
    buffer[i++] = '0';
    size_to_unsigned--;
  } else {
    while (num != 0) {
      buffer[i++] = octal_digits[num % 8];
      num = num / 8;
      size_to_unsigned--;
    }
  }
  if (specs.float_accuracy - i > 0) {
    specs.float_accuracy -= i;
    opt.fill_w_nulls = 1;
  } else
    flag = 1;

  // Если у нас нет места для нулей
  if (size_to_unsigned == 1 && opt.fill_w_nulls == 1 && specs.flag_to_size == 1)
    opt.fill_w_nulls = 0;

  // Обработка флага 0
  while (opt.fill_w_nulls && buffer &&
         (size_to_unsigned - specs.flag_to_size > 0) &&
         (specs.float_accuracy || flag)) {
    if ((size_to_unsigned == 1 && specs.flag_to_size == 1)) break;
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
    specs.float_accuracy--;
  }

  // Обработка #/o/x/X
  if (opt.reshetka_hexidcml && specs.number_system == 8) {
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
  } else if (opt.reshetka_hexidcml && specs.number_system == 16 && specs.is_upper_case) {
    buffer[i] = 'X';
    i++;
    size_to_unsigned--;
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
  } else if (opt.reshetka_hexidcml && specs.number_system == 16 && !specs.is_upper_case) {
    buffer[i] = 'x';
    i++;
    size_to_unsigned--;
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
  }

  // Обработка ситуации, когда осталось свободное место
  if (size_to_unsigned > 0 && opt.minus_align_left == 0) {
    while ((size_to_unsigned - specs.flag_to_size > 0) && buffer) {
      buffer[i] = ' ';
      i++;
      size_to_unsigned--;
    }
  }
  return i;
}

// кастим 16-ричное в стрингу
int hex_to_string(unsigned long int num, char *buffer, struct_specfrs specs,
                  s21_size_t size_to_unsigned, flags opt) {
  char hex_digits[] = "0123456789abcdef";
  if (specs.is_upper_case) s21_strncpy(hex_digits, "0123456789ABCDEF", 16);
  int i = 0;
  int flag = 0;

  if (num == 0 && (!specs.dot && !specs.float_accuracy == 0)) {
    buffer[i++] = '0';
    size_to_unsigned--;
  }

  while (num != 0) {
    buffer[i] = hex_digits[num % 16];
    num = num / 16;
    i++;
    size_to_unsigned--;
  }

  if (specs.float_accuracy - i > 0) {
    specs.float_accuracy -= i;
    opt.fill_w_nulls = 1;
  } else
    flag = 1;

  // Если у нас нет места для нулей
  if (size_to_unsigned == 1 && opt.fill_w_nulls == 1 && specs.flag_to_size == 1)
    opt.fill_w_nulls = 0;

  // Обработка флага 0
  while (opt.fill_w_nulls && buffer &&
         (size_to_unsigned - specs.flag_to_size > 0) &&
         (specs.float_accuracy || flag)) {
    if ((size_to_unsigned == 1 && specs.flag_to_size == 1)) break;
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
    specs.float_accuracy--;
  }
  // Обработка #/o/x/X
  if (opt.reshetka_hexidcml && specs.number_system == 8) {
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
  } else if (opt.reshetka_hexidcml && specs.number_system == 16 && specs.is_upper_case) {
    buffer[i] = 'X';
    i++;
    size_to_unsigned--;
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
  } else if (opt.reshetka_hexidcml && specs.number_system == 16 && !specs.is_upper_case) {
    buffer[i] = 'x';
    i++;
    size_to_unsigned--;
    buffer[i] = '0';
    i++;
    size_to_unsigned--;
  }
  // Обработка ситуации, когда осталось свободное место
  if (size_to_unsigned > 0 && opt.minus_align_left == 0) {
    while ((size_to_unsigned - specs.flag_to_size > 0) && buffer) {
      buffer[i] = ' ';
      i++;
      size_to_unsigned--;
    }
  }
  return i;
}

// получаем размер буфера для малока, целое число
s21_size_t get_size_to_decimal(struct_specfrs *specs, flags *opt, long int num) {
  long int n = num;
  s21_size_t count = 0;

  if (n < 0) n = -n;
  while (n > 0) {
    n /= 10;
    count++;
  }

  if (n == 0 && count == 0 &&
      (specs->float_accuracy || specs->width || opt->fill_w_space || opt->plus_show_sign)) {
    count++;
  }
  if ((s21_size_t)specs->float_accuracy > count) count = specs->float_accuracy;
  if (opt->fill_w_space || opt->plus_show_sign || num < 0) {
    specs->flag_to_size = 1;
    count++;
  }

  if ((s21_size_t)specs->width > count) count = specs->width;
  if (count == 0 && n == 0 && !specs->float_accuracy && !specs->width &&
      !opt->fill_w_space && !specs->dot)
    count++;
  if (specs->dot && specs->float_accuracy == 0 && num == 0) count--;
  return count;
}

// получаем размер буфера для маллока, дробное число
s21_size_t get_size_to_double(struct_specfrs *specs, flags *opt, long double num) {
  long double n = num;
  s21_size_t count = 0;
  int exp = 0;
  long int exponent = 0;
  long double mantissa = 0;

  if (specs->e_small || specs->E_big) {
    if (n != 0) {
      while (n >= 10.0 || n <= -10.0) {
        n /= 10.0;
        exp++;
      }
      while (n < 1.0 && n > -1.0) {
        n *= 10.0;
        exp--;
      }
    }
    if (exp < 100 && exp > -100) {
      count += 4;
    } else {
      while (exp != 0) {
        exp /= 10;
        count++;
      }
      count += 2;
    }
  }

  exponent = (long int)n;
  mantissa = n - exponent;

  if (num < 0) {
    exponent = -exponent;
  }

  if (exponent == 0) count++;
  while (exponent > 0) {
    exponent /= 10;
    count++;
  }

  if ((specs->g_small || specs->G_big) && ((long)(mantissa * 100000) == 0)) {
  } else {
    if (specs->dot && specs->float_accuracy == 0 && !opt->reshetka_hexidcml) {
    } else {
      count++;  // Точка
    }
    if (!specs->dot) {
      if (fabs((double)mantissa) < 0.000001 && (specs->g_small || specs->G_big))
        count--;
      else {
        for (int i = 0; i < 6; i++) {
          mantissa *= 10;
          count++;
        }
      }
    } else {
      if (fabs((double)mantissa) < 0.000001 && (specs->g_small || specs->G_big))
        count--;
      else {
        for (int i = 0; i < specs->float_accuracy; i++) {
          mantissa *= 10;
          count++;
        }
      }
    }
  }
  if (n == 0 && count == 0 &&
      (specs->float_accuracy || specs->width || opt->fill_w_space)) {
    count++;
  }
  if (opt->fill_w_space || opt->plus_show_sign || num < 0) {
    specs->flag_to_size = 1;
    count++;
  }

  if ((s21_size_t)specs->width > count) count = specs->width;
  if ((s21_size_t)specs->float_accuracy > count && (!specs->g_small && !specs->G_big))
    count = specs->float_accuracy;

  if (count == 0 && n == 0 && !specs->float_accuracy && !specs->width &&
      !opt->fill_w_space && !specs->dot)
    count++;
  if ((specs->g_small || specs->G_big) && num == 0) count = 1;
  if (specs->g_small || specs->G_big) {
    if (!specs->width) count = 7;
  }
  return count;
}

// получаем размер буфера для неотрезанного инта
s21_size_t get_size_to_unsigned(struct_specfrs *specs, flags *opt,
                                unsigned long int num) {
  unsigned long int n = num;
  s21_size_t count = 0;
  if (specs->number_system == 8) {
    while (n > 0) {
      n /= 8;
      count++;
    }
  } else if (specs->number_system == 16) {
    while (n > 0) {
      n /= 16;
      count++;
    }
  } else {
    while (n > 0) {
      n /= 10;
      count++;
    }
  }
  if (specs->ptr) count += 2;
  if (n == 0 && count == 0 &&
      (specs->float_accuracy || specs->width || opt->fill_w_space)) {
    count++;
  }
  if ((s21_size_t)specs->width > count) count = specs->width;
  if ((s21_size_t)specs->float_accuracy > count) count = specs->float_accuracy;
  if (opt->fill_w_space || opt->plus_show_sign) {
    specs->flag_to_size = 1;
    count++;
  }

  if (count == 0 && n == 0 && !specs->float_accuracy && !specs->width &&
      !opt->fill_w_space && !specs->dot)
    count++;

  if (opt->reshetka_hexidcml && ((s21_size_t)specs->float_accuracy < count)) {
    if (specs->o) count++;
  }
  if (opt->reshetka_hexidcml && (specs->x || specs->X)) count += 2;
  return count;
}

