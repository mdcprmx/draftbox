CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
SRC_FILE = s21cat_v3_final.c

all: clear s21_cat

s21_cat:
	$(CC) $(FLAGS) $(SRC_FILE) -o s21cat.out

clean:
	clear

clear:
	rm -rf s21_cat *.out

testing:


check:
	clangn clangi clangn

clangn:
	clang-format -style=Google -n *.c *.h

clangi:
	clang-format -style=Google -i *.c *.h