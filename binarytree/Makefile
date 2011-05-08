
CC=gcc
CFLAGS=-Wall
EXECUTABLE=binarytree

.PHONY: run
run: binarytree
	@./$(EXECUTABLE)

binarytree: binarytree.c binarytree.h
	$(CC) $(CFLAGS) -o $(EXECUTABLE) binarytree.c

.PHONY: clean
clean:
	@rm -rfv $(EXECUTABLES)
