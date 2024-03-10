CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
SPECIAL_FLAGS = -c -g -lm -fprofile-arcs -ftest-coverage
# флаг -lm для math.h (если будет использоватся)
# флаг -c чтоб создать .o файлы, не начиная процесс линковки
# флаг -g юзается для включения отладочной информации, НУЖНО для gcov
# флаг -fprofile-arcs вставляет дополнительный код в .o файлы, НУЖНО для gcov
# флаг -ftest-coverage при компляции генерирует код для проверки кода, НУЖНО для gcov
CFLAGS_CHECK = $(shell pkg-config --cflags check)
CHECK_LIBS= $(shell pkg-config --libs check )

WHAT_SYSTEM = $(shell uname -s)


SRC_FILES=s21_memchr.c \ s21_memcmp.c \ s21_memmove.c \ ... # тут будут все файлы
OBJ_FILES= $(SRC_FILES:.c=.o) # эта линия ищет *.o файлы из SRC_FILES. Но ваще можно вручную прописать


ifeq ($(WHAT_SYSTEM),Linux)
    # Code for Linux
endif

ifeq ($(WHAT_SYSTEM),Darwin) # darwin is MACos somehow. lmao
    # Code for macOS
endif

all: clear s21_string.a test

s21_string.a:
	$(CC) $(FLAGS) $(SRC_FILES) -o $(EXEC_FILE)
	ar rc 
gcov_report:
	# soo, this target should generate a gcov report as html page (HUH?)

clear: clean

clean:
	rm -rf *.out
	rm -rf *.bb
	rm -rf *.bbg
	rm -rf *.da
	rm -rf *.gcno
	rm -rf *.gcda
# флаг -fprofile-arcs создаёт эти .bb .bbg .da файлы для gcov. 
# флаг -ftest-coverage создаёт .gcno .gcda файлы (как я понял). 
	

%.o: %.c s21_string.h
	$(CC) $(FLAGS) -c $< -o $@

test:
#WIP

clangfull: clangn clangi clangn

clangn:
	clang-format -style=Google -n *.c *.h

clangi:
	clang-format -style=Google -i *.c *.h

memtest:
#WIP
	valgrind --tool=memcheck --leak-check=yes #WIP 


# also, use prefix 's21_' for EACH function!
# and, you can't use standard libraries for strings(except for tests)
# and, it is FORBIDDEN to use system errors arrays (what? huh?!)
#          (including sys_nerr, sys_errlist)
# and..
# "Functions must work with z-string made of single-byte characters in ASCII encoding."
# what da hell does that mean? I dunno.

# Part 1 - basic string.h implementation
# Part 2 - half-working sprintf function too
# Part 3 - almost-working sprintf function (with format modifiers)
# Part 4 - sscanf function
# Part 5 - add 5 functions from си шарп (C#)

# sooo, after video thoughts
# 1 - git merge is not scary
# 2 - in src you MUST add header and ".a" file (static library), 
# 3 - add main function ONLY in one file. (verter will fail u if u have multiple mains)
# 4 - u may add html file too
# 5 - also, we use multiple object files cause it will take 3-6 hours to compile a huge project
#     if it's in a single file.
# 6 - use flag '-c' with gcc.. why tho? hmm.. cause "NO LINKING"
# 7 - main concern is structing and compiling of library, and running tests. Not the code itslef (huh? rly?)
# 8 - verter only executes 's21_string.a' target in Makefile
# 9 - DONT USE STRING.H for code (obviously)
# 10 - but use STRING.H for tests. (obviously)
#      soo best course of actions - have 2 header files. First for code, second for tests.
# 11 - hmm, you should write tests first, and then code.. hmm
#      that's weird at first. But it kind-a makes sense...
# 12 - 
# timestamp - 01:02:00
# 

#  Phony is used to force makefile use its targets, not some random file
#  with the same file name.
.PHONY: all clean clear test memtest s21_string.a