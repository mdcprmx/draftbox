`-e`, `-i`, `-v`, `-c`, `-l`, `-n`, `-h`, `-s`, `-f`, `-o`, `-iv`, `-in`


       grep [OPTION...] PATTERNS [FILE...]
       grep [OPTION...] -e PATTERNS ... [FILE...]
       grep [OPTION...] -f PATTERN_FILE ... [FILE...]

-e PATTERNS, --regexp=PATTERNS
        Use PATTERNS as the patterns.  If this option is used multiple times or is combined with the -f (--file) option, search for all patterns given.  This option can be used to protect a pattern beginning with “-”.
        Используйте PATTERN в качестве шаблонов. Если этот параметр используется несколько раз или сочетается с параметром -f (--file), выполняется поиск по всем заданным шаблонам. Эту опцию можно использовать для защиты шаблона, начинающегося с «-».

-i, --ignore-case
        Ignore case distinctions in patterns and input data, so that characters that differ only in case match each other.
        Игнорируйте различия в регистре в шаблонах и входных данных, чтобы символы, отличающиеся только регистром, соответствовали друг другу.

-v, --invert-match
        Invert the sense of matching, to select non-matching lines.
        Инвертируйте смысл совпадения, чтобы выбрать несовпадающие линии.

-c, --count
        Suppress normal output; instead print a count of matching lines for each input file.  With the -v, --invert-match option (see below), count non-matching lines.
        Вывод количество совпадающих строк для каждого входного файла. С помощью опции -v, --invert-match (см. ниже) подсчитайте несовпадающие строки.

-l, --files-with-matches
        Suppress normal output; instead print the name of each input file from which output would normally have been printed.  Scanning each input file stops upon first match.
        Выводит имя каждого входного файла, из которого обычно печатаются выходные данные. Сканирование каждого входного файла прекращается при первом совпадении.

-n, --line-number
        Prefix each line of output with the 1-based line number within its input file.
        Префикс каждой строки вывода с номером строки, отсчитываемым от 1, во входном файле.

-h, --no-filename
        Suppress the prefixing of file names on output.  This is the default when there is only one file (or only standard input) to search.
        Подавить префикс имен файлов при выводе. Это значение по умолчанию, когда для поиска требуется только один файл (или только стандартный ввод).

-s, --no-messages
        Suppress error messages about nonexistent or unreadable files.
        Подавлять сообщения об ошибках о несуществующих или нечитаемых файлах.

-f FILE, --file=FILE
        Obtain patterns from FILE, one per line.  If this option is used multiple times or is combined with the -e (--regexp) option, search for all patterns given.  The empty file contains zero  patterns,  and  therefore  matches
        nothing.
        Получите шаблоны из ФАЙЛА, по одному на строку. Если этот параметр используется несколько раз или сочетается с параметром -e (--regexp), выполняется поиск по всем заданным шаблонам. Пустой файл не содержит шаблонов и, следовательно, соответствует
        ничего.

-o, --only-matching
        Print only the matched (non-empty) parts of a matching line, with each such part on a separate output line.
        Печатайте только совпадающие (непустые) части совпадающей строки, причем каждая такая часть находится в отдельной выходной строке.

