# Makefile for Thomas Jespersen' "begin" library of C programs (this
# is where it all began)
# 
#

CC	 := gcc
CFLAGS	 := -Wall
OBJECTS	 := hello2.o h.o w.o
PROGRAMS := hello hello2 ager longstring bubble_array trigraph ex1_3 bit bit2\
		gitbit exp4_4 ex4_1 struct\
		login utsname\
		chessboard printchars

TARGETS := hello
TARGETS += hello2
TARGETS += ager
TARGETS += str
TARGETS += ary_begin
TARGETS += exercise1_3
TARGETS += trigraph
TARGETS += bit
TARGETS += bit2
TARGETS += gitbit
TARGETS += example4_4
TARGETS += exercise4_1
TARGETS += struct
TARGETS += login
TARGETS += utsname
TARGETS += chessboard
TARGETS += printchars

# TARGETS	 := hello hello2 ager str ary_begin exercise1_3 trigraph bit bit2\
# 		gitbit example4_4 exercise4_1 struct\
# 		login utsname

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
	@echo "  login          A login program (login)"
	@echo "  utsname        Prints system information using uname() (utsname)"
	@echo "  printchars     Prints characters (printchars)"
	@echo "  chessboard     Print a chess board (chessboard)"
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

ager: ageif.c			# Age determining program
	$(CC) $(CFLAGS) -o ager ageif.c

str: str.c			# Strings
	$(CC) $(CFLAGS) -o longstring str.c

ary_begin: ary_begin.c		# Bubble sort an array
	$(CC) $(CFLAGS) -o bubble_array ary_begin.c

exercise1_3: exercise1_3.c	# Exercise 1.3 from "The C Book"
	$(CC) $(CFLAGS) -o ex1_3 exercise1_3.c

trigraph: trigrapher.c		# Program with trigraphs
	$(CC) $(CFLAGS) -trigraphs -o trigraph trigrapher.c

bit: bit.c
	$(CC) $(CFLAGS) -o bit bit.c

bit2: bit2.c printbits.o
	$(CC) $(CFLAGS) -o bit2 bit2.c printbits.o

gitbit: gitbit.c printbits.o
	$(CC) $(CFLAGS) -o gitbit gitbit.c printbits.o

printbits.o: printbits.c printbits.h
	$(CC) $(CFLAGS) -c printbits.c

example4_4: example4_4.c 	# Example 4.4 from "The C Book"
	$(CC) $(CFLAGS) -o exp4_4 example4_4.c

exercise4_1: exercise4_1.c
	$(CC) $(CFLAGS) -o ex4_1 exercise4_1.c

struct: struct.c
	$(CC) $(CFLAGS) -o $@ $<

login: login.c
	$(CC) $(CFLAGS) -o $@ $<

utsname: utsname.c
	$(CC) $(CFLAGS) -o $@ $<

printchars: printchars.c
	$(CC) $(CFLAGS) -o $@ $<

chessboard: chessboard.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	@rm -rvf *.o *~ $(PROGRAMS)
