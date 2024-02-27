CC = gcc
FLAGS = -Wall -Wextra -Werror -g -std=c11 

# this! just typing "$(*.c)" won't work. You have to type 'wildcard' command too.
SRC_FILES= $(wildcard *.c)
OBJ_FILES= $(wildcard *.o)

all: clear lib

lib:
	$(CC) $(FLAGS) $(SRC_FILES) -o $(OBJ_FILES)

# soooo macros '$@' is used to copy name of target in itself.
dancedanceLove:
	echo $@ 
	$(CC) $(FLAGS) $(SRC_FILES) -o $@

clear: clean

clean:
	rm -rf *.out
