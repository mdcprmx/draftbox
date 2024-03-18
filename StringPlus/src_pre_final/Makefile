CC = gcc
USUAL_FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
# SPECIAL_FLAGS = -c -g -lm -fprofile-arcs -ftest-coverage
# флаг -lm для math.h (если будет использоватся)
# флаг -c чтоб создать .o файлы, не начиная процесс линковки
# флаг -g юзается для включения отладочной информации, НУЖНО для gcov
# флаг -fprofile-arcs вставляет дополнительный код в .o файлы, НУЖНО для gcov
# флаг -ftest-coverage при компляции генерирует код для проверки кода, НУЖНО для gcov
GCOV_SPECIAL = -fprofile-arcs -ftest-coverage
TEST_SPECIAL = -lcheck -lpthread -pthread -lm -lrt -lsubunit -lgcov

WHAT_SYSTEM := $(shell uname -s)
# ':=' запускает присваивание переменной сразу при запуске makefile
# в отличии от '=' которое присвает только при вызове. а ваще без разницы

SRC_FILES = $(wildcard s21_*.c) # выберет все файлы расшиерния '.c' начинающиеся на 's21_'
OBJ_FILES = $(wildcard s21_*.o)

all: clean compile_obj s21_string.a test gcov_report

s21_string.a: compile_obj
	ar -rcs s21_string.a $(OBJ_FILES)
	ranlib s21_string.a

compile_obj: 
	gcc -c $(USUAL_FLAGS) $(SRC_FILES)
 
test: s21_string.a
ifeq ($(WHAT_SYSTEM), Linux)
	gcc $(USUAL_FLAGS) test.c $(SRC_FILES) -o zapuskator_testov $(TEST_SPECIAL)
	./zapuskator_testov
else
	gcc $(USUAL_FLAGS) test.c s21_string.a -o zapuskator_testov -lcheck
	./zapuskator_testov
endif
# компилируем тест.си, отправляем ему статик библиотеку нашу, называем запускатором
# -lcheck это подключение библы проверок. -lm библа математики. -lsubunit для передачи резу-тов тестов
# ПОРЯДОК ВАЖЕН! ИМЕННО В ТАКОМ ПОРЯДКЕ эти флаги должны идти, иначе процесс линковки зафейлится (кажется)

gcov_report: test
	pip install gcovr
ifeq ($(WHAT_SYSTEM), Linux)
	gcc $(GCOV_SPECIAL) -fPIC -O0 test.c $(SRC_FILES) -o report.out $(TEST_SPECIAL)
else
	gcc $(GCOV_SPECIAL) -fPIC -O0 test.c $(SRC_FILES) -o report.out -lcheck 
endif
	./report.out
	gcov -f *.gcda
	~/.local/bin/gcovr -r . --exclude-unreachable-branches --html-details -o gcovr_report.html
	firefox gcovr_report.html
# gcov -f указывает где искать эти gcda файлы, в нашем случае прямо в папке где мы есть (по дефолту в другом месте ищет)
#	lcov -c -d . -o cov_rep.info
# lcov эт тестер, а gcov это графическая часть. 
# '-c' говорит что надо собрать данные о покрытии кода
# '-d .' указывает на директорию, тоесть на текущую (.) (точка эт текущая папка)
# bruh. gcovr и gcov это разные утилиты, gcov-ов у нас нету на компах, поэтому юзают gcovr 
# потомучт его установить можно

clear: clean

clean:
	rm -rf *.a
	rm -rf *.out
	rm -rf *.o
	rm -rf *.bb
	rm -rf *.bbg
	rm -rf *.da
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.html
	rm -rf *.css
	rm -rf zapuskator_testov
# флаг -fprofile-arcs создаёт эти .bb .bbg .da файлы для gcov. 
# флаг -ftest-coverage создаёт .gcno .gcda файлы (как я понял). 

memtest: test
	valgrind --track-origins=yes --leak-check=full ./zapuskator_testov
	
clangfull: clangn clangi clangn

clangn:
	clang-format -style=Google -n *.c *.h

clangi:
	clang-format -style=Google -i *.c *.h

# через эту команду устанавливаем gcovr на АРМах пиров, чтоб html файлик работал
install_gcovr:
	pip install gcovr

#  PHONY нужен чтобы наш Makefile запустил свои цели,
#        так как он может запутаться если найдёт файлы с точно такими же названиями
.PHONY: all clean clear test memtest s21_string.a gcov_report compile_obj