CC = gcc
FLAGS = -Wall -Wextra -Werror -g -std=c11 

# this! just typing "$(*.c)" won't work in this context. You have to type 'wildcard' command too.
SRC_FILES= $(wildcard *.c)
OBJ_FILES= $(wildcard *.o)

all: clear CreateObjFiles LibCompile

# soooo macros '$@' is used to copy name of target in itself.
dancedanceLove:
	echo $@ 
	$(CC) $(FLAGS) $(SRC_FILES) -o $@

# this target creates '.o' files. because -c flag is used
CreateObjFiles:
	gcc -c *.c 

# then this target compiles it to library, using "ar rc" system utility
LibCompile:
	ar rc MyLib.a *.o
# 'ar' - is utility name
# 'rc' - are modes, flags for 'create' and 'replace'

RanLib:
	ranlib MyLib.a



clear: clean

clean:
	rm -rf *.out
	rm -rf *.o
	rm -rf *.a

