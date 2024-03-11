CC = gcc
USUAL_FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
SPECIAL_FLAGS = -c -g -lm -fprofile-arcs -ftest-coverage
# флаг -lm для math.h (если будет использоватся)
# флаг -c чтоб создать .o файлы, не начиная процесс линковки
# флаг -g юзается для включения отладочной информации, НУЖНО для gcov
# флаг -fprofile-arcs вставляет дополнительный код в .o файлы, НУЖНО для gcov
# флаг -ftest-coverage при компляции генерирует код для проверки кода, НУЖНО для gcov
CFLAGS_CHECK = $(shell pkg-config --cflags check)
CHECK_LIBS = $(shell pkg-config --libs check )

WHAT_SYSTEM = $(shell uname -s)

SRC_FILES = $(wildcard s21_*.c) # выберет все файлы расшиерния '.c' начинающиеся на 's21_'
OBJ_FILES = $(wildcard s21_*.o)

ifeq ($(WHAT_SYSTEM),Linux)
    # Code for Linux
endif

ifeq ($(WHAT_SYSTEM),Darwin) # Darwin это эппл
    # Code for macOS
endif

all: clear s21_string.a test

s21_string.a:
	$(CC) $(USUAL_FLAGS) $(SPECIAL_FLAGS) $(SRC_FILES) -o $(EXEC_FILE)
	ar rcs 

gcov_report:
# WIP

clear: clean

clean:
	rm -rf *.out
	rm -rf *.o
	rm -rf *.bb
	rm -rf *.bbg
	rm -rf *.da
	rm -rf *.gcno
	rm -rf *.gcda
# флаг -fprofile-arcs создаёт эти .bb .bbg .da файлы для gcov. 
# флаг -ftest-coverage создаёт .gcno .gcda файлы (как я понял). 

test:
#WIP

memtest:
#WIP
	valgrind --tool=memcheck --leak-check=yes #WIP 

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
.PHONY: all clean clear test memtest s21_string.a