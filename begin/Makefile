# Makefile for Thomas Jespersen' "begin" library of C programs (this
# is where it all began)
# 
#

CC=gcc
CFLAGS=-Wall
OBJECTS=hello2.o h.o w.o
PROGRAMS=hello hello2 ager longstring bubble_array trigraph ex1_3 bit bit2 gitbit exp4_4 ex4_1 struct
TARGETS=hello hello2 ager str ary_begin exercise1_3 trigraph bit bit2 gitbit example4_4 exercise4_1 struct

# If the user didn't specify anything, they will get some help.
#
help:
	@echo "This is Thomas' beginner's library of C programs. The list of programs is given in the following format:"
	@echo ""
	@echo "  target         description (program name)"
	@echo ""
	@echo "Here is a list of (suggested) targets to make:"
	@echo "  hello          Hello World! (hello)"
	@echo "  hello2         A second hello world (hello2)"
	@echo "  ager           Play of ages (ager)"
	@echo "  str            String play (longstring)"
	@echo "  ary_begin      Bubble sorts an array (bubble_array)"
	@echo "  exercise1_3    Exercise 1.3 from 'The C Book' (ex1_3)"
	@echo "  trigraph       A program with trigraphs (trigraph)"
	@echo "  bit            A bitwise operating program (bit)"
	@echo "  bit2           A clone of 'bit' except it ACTUALLY prints the bit strings (bit2)"
	@echo "  gitbit         Demonstrates git's bits, from git.c (gitbit)"
	@echo "  example4_4     Example 4.4 from 'The C Book' (exp4_4)"
	@echo "  exercise4_1    Exercise 4.1 from 'The C Book' (ex4_1)"
	@echo "  struct         A struct example program (struct)"
	@echo ""
	@echo "Less interesting targets:"
	@echo "  clean          Clean up"
	@echo "  all            Make all targets"

all: $(TARGETS)

# Simple 'Hello, World!' program.
hello: hello.c
	$(CC) $(CFLAGS) -o hello hello.c

# More complex (for learning Makefiles)
hello2: $(OBJECTS)
	$(CC) $(CFLAGS) -o hello2 $(OBJECTS)

hello2.o: hello2.c
	$(CC) $(CFLAGS) -c hello2.c

h.o: h.c
	$(CC) $(CFLAGS) -c h.c

w.o: w.c
	$(CC) $(CFLAGS) -c w.c

# Age determining program
ager: ageif.c
	$(CC) $(CFLAGS) -o ager ageif.c

# Strings
str: str.c
	$(CC) $(CFLAGS) -o longstring str.c

# Bubble sort an array
ary_begin: ary_begin.c
	$(CC) $(CFLAGS) -o bubble_array ary_begin.c

# Exercise 1.3 from "The C Book"
exercise1_3: exercise1_3.c
	$(CC) $(CFLAGS) -o ex1_3 exercise1_3.c

# Program with trigraphs
trigraph: trigrapher.c
	$(CC) $(CFLAGS) -trigraphs -o trigraph trigrapher.c

bit: bit.c
	$(CC) $(CFLAGS) -o bit bit.c

bit2: bit2.c printbits.o
	$(CC) $(CFLAGS) -o bit2 bit2.c printbits.o

gitbit: gitbit.c printbits.o
	$(CC) $(CFLAGS) -o gitbit gitbit.c printbits.o

printbits.o: printbits.c printbits.h
	$(CC) $(CFLAGS) -c printbits.c

# Example 4.4 from "The C Book"
example4_4: example4_4.c
	$(CC) $(CFLAGS) -o exp4_4 example4_4.c

exercise4_1: exercise4_1.c
	$(CC) $(CFLAGS) -o ex4_1 exercise4_1.c

struct: struct.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	@rm -rvf *.o *~ $(PROGRAMS)
