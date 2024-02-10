FLAG = -std=c11 -Wall -Wextra -Werror

start: clean s21_cat test_bash

s21_cat:
	gcc $(FLAG) s21_cat.c -o s21_cat

clean:
	rm -f s21_cat
	rm -f .clang-format

test_python:
	python3 autotest.py

test_bash:
	./cat_test.sh