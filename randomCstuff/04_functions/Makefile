CC_W_FLAGS = gcc -Werror -Wextra -Werror -pedantic -std=c99
SRC = pract.c
EXEC_NAME = practice.out

all: clean
	rm -rf $(EXEC_NAME)
	$(CC_W_FLAGS) $(SRC) -o $(EXEC_NAME)
	./$(EXEC_NAME)

clear: clean

clean:
	@rm -rf *.out
	@rm -rf *.o
