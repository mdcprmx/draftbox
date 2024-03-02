CC = gcc
FLAGS = -Wall -Wextra -Werror -g -c -std=c11 -pedantic $(shell pkg-config --cflags check) # needed for check.h library
EXEC_FILE = 
WHAT_SYSTEM = $(shell uname -s)

SRC_FILES=s21_memchr.c \ s21_memcmp.c \ s21_memmove.c \ ... # and the list goes on
CHECK_LIBS= $(shell pkg-config --libs check )
OBJ_FILES= $(SRC_FILES:.c=.o) #this line searches for .o files that were in SRC_FILES


ifeq ($(WHAT_SYSTEM),Linux) 
    # Code for Linux
endif
ifeq ($(WHAT_SYSTEM),Darwin) # darwin is MACos somehow. lmao
    # Code for macOS
endif

all: clear s21_string.a

s21_string.a:
	$(CC) $(FLAGS) $(SRC_FILES) -o $(EXEC_FILE)

gcov_report:
	# soo, this target should generate a gcov report as html page (HUH?)

clear: clean

clean:
	rm -rf *.out

%.o: %.c s21_string.h
	$(CC) $(FLAGS) -c $< -o $@

test:
	chmod +x *.sh
	#ADD STUFF TO ME LATER

clangfull: clangn clangi clangn

clangn:
	clang-format -style=Google -n *.c *.h

clangi:
	clang-format -style=Google -i *.c *.h

memtest:
	valgrind --tool=memcheck --leak-check=yes $(EXEC_FILE) 


# also, use prefix 's21_' for EACH function!
# and, you can't use standard libraries for strings(except for tests)
# and, it is FORBIDDEN to use system errors arrays (what? huh?!)
#          (including sys_nerr, sys_errlist)
# and..
# "Functions must work with z-string made of single-byte characters in ASCII encoding."
# what da hell does that mean? I dunno.
# sooo... let's start this

# Part 1 - basic string.h implementation
# Part 2 - half-working sprintf function too
# Part 3 - almost-working sprintf function (with format modifiers)
# Part 4 - sscanf function
# Part 5 - huh? it just says "add special string processing functions"
#		   BUT WHAT IS THIS?! BRRRRRRRRRRUAAAAAAAAAAAAAAAAAAAH

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


.PHONY: all clean clear test memtest s21_string.a