CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
SRC_FILE = *.c
EXEC_FILE = 
UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    # Code for Linux

endif
ifeq ($(UNAME_S),Darwin)
    # Code for macOS

endif

all: clear s21_grep

s21_string.a:
	$(CC) $(FLAGS) $(SRC_FILE) -o ($EXEC_FILE)

gcov_report:
	# soo, this target should generate a gcov report as html page (HUH?)

clear: clean

clean:
	rm -rf *.out

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
# and, you can't use standard libraries (except for tests)
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

.PHONY all clean clear test memtest s21_string.a


