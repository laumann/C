

CC=gcc
CFLAGS=-Wall
EXERCISE4_3=exercise4_3.c exercise4_2.c
PROGRAMS=ex4_3 ex4_4 exp5_1 exp5_3 exp5_4 exp5_6 exp5_12 exp5_14 exp5_16 ex5_5 exp6_2 exp6_7 exp6_14 ex6_9 use_sinecosine

all: $(PROGRAMS)

ex4_3: $(EXERCISE4_3)
	$(CC) $(CFLAGS) -o ex4_3 $(EXERCISE4_3)

ex4_4: exercise4_4.c
	$(CC) $(CFLAGS) -o ex4_4 exercise4_4.c

# Chapter 5, examples
exp5_1: example5_1.c
	$(CC) $(CFLAGS) -o exp5_1 example5_1.c

exp5_3: example5_3.c
	$(CC) $(CFLAGS) -o exp5_3 example5_3.c

exp5_4: example5_4.c
	$(CC) $(CFLAGS) -o exp5_4 example5_4.c

exp5_6: example5_6.c
	$(CC) $(CFLAGS) -o exp5_6 example5_6.c

exp5_12: example5_12.c
	$(CC) $(CFLAGS) -o exp5_12 example5_12.c

exp5_14: example5_14.c
	$(CC) $(CFLAGS) -o exp5_14 example5_14.c

exp5_16: example5_16.c
	$(CC) $(CFLAGS) -o exp5_16 example5_16.c

# Chapter 5, exercises
ex5_5: exercise5_5.c
	$(CC) $(CFLAGS) -o ex5_5 exercise5_5.c

# Chapter 6, examples
exp6_2: example6_2.c
	$(CC) $(CFLAGS) -o exp6_2 example6_2.c

exp6_7: example6_7.c
	$(CC) $(CFLAGS) -o exp6_7 example6_7.c

exp6_14: example6_14.c
	$(CC) $(CFLAGS) -o exp6_14 example6_14.c

ex6_9: exercise6_9.c
	$(CC) $(CFLAGS) -o ex6_9 exercise6_9.c

# My own programs
use_sinecosine: sinecosine.c sinecosine.h use_sinecosine.c
	$(CC) $(CFLAGS) -o use_sinecosine use_sinecosine.c sinecosine.c

clean:
	@rm -fv $(PROGRAMS)
