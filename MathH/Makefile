CC = gcc
USUAL_FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
GCOV_SPECIAL = -fprofile-arcs -ftest-coverage
LINUX_TEST_SPECIAL = -lcheck -lpthread -pthread -lm -lrt -lsubunit -lgcov
# -lcheck это подключение библы проверок. -lm библа математики. -lsubunit для передачи резу-тов тестов
# SPECIAL_FLAGS = -c -g -lm -fprofile-arcs -ftest-coverage
# флаг -lm для math.h (если будет использоватся)
# флаг -c чтоб создать .o файлы, не начиная процесс линковки
# флаг -g юзается для включения отладочной информации, НУЖНО для gcov
# флаг -fprofile-arcs вставляет дополнительный код в .o файлы, НУЖНО для gcov
# флаг -ftest-coverage при компляции генерирует код для проверки кода, НУЖНО для gcov

WHAT_SYSTEM := $(shell uname -s)
# ':=' запускает присваивание переменной сразу при запуске makefile
# в отличии от '=' которое присвает только при вызове. а ваще без разницы

SRC_FILES = $(wildcard s21_*.c) # выберет все файлы расшиерния '.c' начинающиеся на 's21_'
OBJ_FILES = $(wildcard s21_*.o)

all: clean compile_obj s21_string.a test gcov_report

compile_obj: 
	gcc -c $(USUAL_FLAGS) $(SRC_FILES)
 
s21_string.a: compile_obj
	ar -rcs s21_string.a $(OBJ_FILES)
	ranlib s21_string.a
	rm -rf $(OBJ_FILES)


test: s21_string.a
ifeq ($(WHAT_SYSTEM), Darwin)
	gcc $(USUAL_FLAGS) test.c s21_string.a -o zapuskator_testov -lcheck
	./zapuskator_testov
else
	gcc $(USUAL_FLAGS) test.c $(SRC_FILES) -o zapuskator_testov $(LINUX_TEST_SPECIAL)
	./zapuskator_testov
endif

gcov_report: test
	pip install gcovr
ifeq ($(WHAT_SYSTEM), Darwin)
	gcc $(GCOV_SPECIAL) -fPIC -O0 test.c $(SRC_FILES) -o report.out -lcheck 
else
	gcc $(GCOV_SPECIAL) -fPIC -O0 test.c $(SRC_FILES) -o report.out $(LINUX_TEST_SPECIAL)
endif
	./report.out
	gcov -f *.gcda
	~/.local/bin/gcovr -r . --exclude-unreachable-branches --html-details -o gcovr_report.html
	firefox gcovr_report.html

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

memtest: test
	valgrind --track-origins=yes --leak-check=full ./test_executor
	
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
# .PHONY: all clean clear test memtest s21_string.a gcov_report compile_obj