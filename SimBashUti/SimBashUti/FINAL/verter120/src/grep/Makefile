CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE -pedantic
SRC_FILE = s21_grep.c

all: clear s21_grep

s21_grep:
	$(CC) $(FLAGS) $(SRC_FILE) -o s21_grep

clean: clear

clear:
	rm -rf s21_grep *.out

test:
	chmod +x grep_test.sh
	./grep_test.sh

clangfull: clangn clangi clangn

clangn:
	clang-format -style=Google -n *.c *.h

clangi:
	clang-format -style=Google -i *.c *.h

memtest:
	valgrind --tool=memcheck --leak-check=yes ./s21_grep -e a test_cache/1.txt
