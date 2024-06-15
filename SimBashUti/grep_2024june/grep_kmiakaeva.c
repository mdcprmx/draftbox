#include "grep_kmiakaeva.h"

// ну argc и argv это дефолтная тема, с ними всё понятно
int main(int argc, char *argv[]) {
  
  // calloc скорее всего обязательно использовать, мы же со строками работаем
  // а в строках знак 0 это ещё и знак конца строки
  char *pattern = (char *)calloc(SIZE, sizeof(char));

  // создаём структуру с ФЛАГАМИ и заполняем нулями
  Flags flags = {false};

  // струкртура параметров грэпа, можно было бы реализовать через переменные
  // но через струкртуру по идее удобнее
  Params params = {false, false, 0, 0};

  // проверка на правильный ввод
  // тоесть если юзер ввёл просто "grep" или "grep needle" то аргументов рил слишком мало
  if (argc < 2) {
    fprintf(stderr, "Missing arguments\n");

    // прикольная реализация флага ошибки, прям в структуре!
    params.error = true;
  } else {

    // если же аргументов как минимум три (например ввод такой "grep needle haystack.txt")
    // то начинается наша логика грэпа. 
    // Сначала запускается парсер флагов
    check_flags(argc, argv, &flags, &params, &pattern);
  }

  if (!params.error) {
    if (!flags.f && !flags.e) {
      add_pattern(&pattern, argv[optind++]);
    }

    if (argc - optind > 1) params.multifile = true;

    for (int i = optind; i < argc; i++) {
      process_file(flags, &params, argv[i], pattern);
    }
  } else {
    fprintf(stderr, "Usage: ./s21_grep [flag] [pattern] [file]\n");
  }

  free(pattern);

  return params.error;
}

void check_flags(int argc, char *argv[], Flags *flags, Params *params,
                 char **pattern) {
  int option;

  // почему тут двоеточия после флагов "e:" и "f:"?
  // потомучто флаги 'e' и 'f' ТРЕБУЮТ аргумента
  // в то время как остальным флагам аргументы не нужны, поэтому и двоеточий у них нет
  // если что прост читай "man grep" в bashe
  while ((option = getopt(argc, argv, "e:ivclnhsf:o")) != -1 &&
         !(params->error)) {

    // Что делает флаг 'e'?
    // Позволяет искать несколько паттернов в файле
    // пример: 
    //    "grep -e love -e dance -e needle newspaper.txt"
    //    в данном вызове греп будет искать строчки со словами "love", "dance", "needle" в файле "newspaper.txt"
    if (option == 'e') {
      flags->e = true;

      // функция добавления паттерна. 
      // optarg это индекс аргумента который идёт после флага с двоеточием
      add_pattern(pattern, optarg);

      // i, ignore case
      // данный флаг заставляет игнорить строчные/заглавные буквы
      // поиск происходит независимо от заглавности И в Паттерне, И В Файле
    } else if (option == 'i') {
      flags->i = true;

      // v, invert match
      // инверсия паттерна. Тоесть греп ищет все строки где НЕТ указанного паттерна
      // по сути работает как "!" в си =)
    } else if (option == 'v') {
      flags->v = true;

      // c, count
      // заместо поиска и вывода, выводит сколько раз искомый паттерн был найден 
      // в каждом из файлов. По сути прост выводит число заместо строчки
      // пример:
      //    grep dance file.txt -c
      //    в ответ grep просто напишет сколько раз слово "dance" встречается в "file.txt"
    } else if (option == 'c') {
      flags->c = true;

      // l, files with matches
      // заменяет обычный вывод; заместо этого пишет в каком файле было найдено совпадение
      // например:
      //    grep needle file.txt file2.txt news.txt book.txt randomthing.txt haystack.txt bruhhh.txt
      // вывод будет просто:
      //    haystack.txt
      // так как в файле "haystack.txt" есть слово "needle"
    } else if (option == 'l') {
      flags->l = true;

      // n, line number
      // добавляет номер строки на которой было найдено совпадение, и саму строку тоже
      // работает почти как обычный вызов grep-a, но цифорки добавляет
    } else if (option == 'n') {
      flags->n = true;

      // h, no filename
      // при поиске в нескольких файлах, grep обычно в своём выводе выводит и имя файла
      // в котором нашёл совпадение. Этот флаг выключает вывод названия файла
      // (но только если поиск идёт в нескольких файлах, если файл один то "h" уже типа работает)
      // (так как если файл один, то очевидно что он нашёл паттерн в этом же файле)
    } else if (option == 'h') {
      flags->h = true;

      // s, no messages
      // не выводит ошибки на экран, типа такие:
      //    grep: 1.txt: No such file or directory
      // просто убирает их
    } else if (option == 's') {
      flags->s = true;

      // f, from file
      // берёт паттерны из файла а не через ввод. пример:
      //    grep -f needles.txt haystack.txt 
      // каждую строку берёт как целый паттерн при этом
    } else if (option == 'f') {
      flags->f = true;
      params->files_count++;
      process_file_pattern(params, pattern, optarg);

      // o, only matching
      // принтит не всю строку, а только искомое слово
      // (tbh, этот флаг какбудто не имеет смысла.. ну ладн)
    } else if (option == 'o') {
      flags->o = true;
    } else {
      params->error = true;
    }
  }

  if (flags->l) {
    flags->c = false, flags->n = false, flags->o = false;
  }

  if (flags->c) {
    flags->n = false, flags->o = false;
  }

  if (optind >= argc || argv[optind][0] == '-' || strlen(argv[optind]) == 0) {
    params->error = true;
  }
}

void process_file_pattern(Params *params, char **pattern, char *optarg) {
  FILE *file = fopen(optarg, "r");

  if (file != NULL) {
    char *line = NULL;
    size_t length = 0;

    while ((getline(&line, &length, file)) != -1) {
      add_pattern(pattern, line);
    }

    free(line);
    fclose(file);
  } else {
    params->error = true;
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", optarg);
  }
}

void add_pattern(char **pattern, char *line) {
  char *copy_line = malloc(strlen(line) + 10);
  strcpy(copy_line, line);

  if (copy_line[0] == '\0' || copy_line[0] == '\n') {
    strcpy(copy_line, "$");
  }

  replace_linebreak(&copy_line);

  static size_t buffer = SIZE;
  while (strlen(*pattern) + strlen(line) + 10 > buffer) {
    buffer *= 2;
    *pattern = (char *)realloc(*pattern, buffer * sizeof(char));
  }

  sprintf(*pattern + strlen(*pattern), "%s\\(%s\\)", *pattern[0] ? "\\|" : "",
          copy_line);

  free(copy_line);
}

void replace_linebreak(char **line) {
  int last_index = (int)strlen(*line) - 1;
  if ((*line)[last_index] == '\n') (*line)[last_index] = '\0';
}

void process_file(Flags flags, Params *params, const char *filename,
                  char *pattern) {
  FILE *file = fopen(filename, "r");

  if (file != NULL) {
    regex_t regex;

    regex_compile(flags, params, &regex, pattern);

    if (!params->error && !(flags.o && flags.v)) {
      if (flags.o) {
        process_flag_o(flags, params, file, &regex, filename);
      } else {
        process_file_lines(flags, params, file, &regex, filename);
      }
    }

    regfree(&regex);
    fclose(file);
  } else if (!flags.s) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
  }
}

void regex_compile(Flags flags, Params *params, regex_t *regex, char *pattern) {
  if (regcomp(regex, pattern, flags.i ? REG_ICASE : 0)) {
    params->error = true;
    fprintf(stderr, "Error compiling regex\n");
  }
}

void process_flag_o(Flags flags, Params *params, FILE *file, regex_t *regex,
                    const char *filename) {
  regmatch_t match;
  char *line = NULL;
  size_t length = 0;
  int line_count = 0, status;

  while ((getline(&line, &length, file)) != -1) {
    line_count++;

    replace_linebreak(&line);

    char *copy_line = strdup(line);
    char *original_copy_line = copy_line;

    while (((status = regexec(regex, copy_line, 1, &match, REG_NOTEOL)) == 0) &&
           strlen(copy_line)) {
      if (match.rm_so == match.rm_eo) {
        copy_line++;
        continue;
      }

      if (params->multifile && !flags.h) printf("%s:", filename);
      if (flags.n) printf("%d:", line_count);
      printf("%.*s\n", (int)match.rm_eo - (int)match.rm_so,
             copy_line + match.rm_so);

      copy_line += match.rm_eo;
    }

    free(original_copy_line);
    original_copy_line = NULL;
  }

  free(line);
  line = NULL;
}

void process_file_lines(Flags flags, Params *params, FILE *file, regex_t *regex,
                        const char *filename) {
  char *line = NULL;
  size_t length = 0;
  int line_count = 0, match_count = 0;

  while ((getline(&line, &length, file)) != -1) {
    line_count++;

    replace_linebreak(&line);

    int status = regexec(regex, line, 0, NULL, 0);

    if (!status ^ flags.v) {
      if (flags.l) {
        printf("%s\n", filename);
        break;
      }

      match_count++;

      if (!flags.c) {
        if (params->multifile && !flags.h) printf("%s:", filename);
        if (flags.n) printf("%d:", line_count);
        printf("%s\n", line);
      }
    }
  }

  if (flags.c) {
    if (params->multifile && !flags.h) printf("%s:", filename);
    printf("%d\n", match_count);
  }

  free(line);
  line = NULL;
}