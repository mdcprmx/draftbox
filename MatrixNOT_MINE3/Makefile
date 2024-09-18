CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
GFLAGS=
LFLAGS= -lcheck -lsubunit -lm

LIB=s21_matrix.a

EXEC=s21_test

SOURCES=$(wildcard s21_matrix/*.c)
OBJECTS=$(SOURCES:.c=.o)

TEST_SOURCES=$(wildcard s21_test_matrix/*.c)
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)

.PHONY: clean test gcov_report

all: s21_matrix.a

$(EXEC): clean $(TEST_OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o $(EXEC) -L. $(LIB) $(LFLAGS)

test: LFLAGS+=-lgcov
test: GFLAGS+=--coverage
test: clean $(EXEC)
	./$(EXEC)

s21_test_matrix/%.o: s21_test_matrix/%.c
	$(CC) $(CFLAGS) -c $< -o $@

s21_matrix/%.o: s21_matrix/%.c
	$(CC) $(CFLAGS) $(GFLAGS) -c $< -o $@

s21_matrix.a: $(OBJECTS)
	ar -rcs $(LIB) $(OBJECTS)

gcov_report: test
	mkdir s21_report
	~/.local/bin/gcovr -r . --html --html-details -o s21_report/s21_matrix.html
	open ./s21_report/s21_matrix.html

clean:
	rm -f $(EXEC)
	rm -f *.a **/*.o
	rm -f **/*.gcno **/*.gcda **/*.gcov
	rm -rf s21_report

check:
	clang-format   -i **/*.c **/*.h *.c *.h
	

val: $(EXEC)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all  ./$(EXEC)

open:
	xdg-open s21_report/s21_matrix.html

