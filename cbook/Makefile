

CC=gcc
CFLAGS=-Wall
EXERCISE4_3=exercise4_3.c exercise4_2.c
PROGRAMS=ex4_3 ex4_4 exp5_1 exp5_3 exp5_12 ex5_5 exp6_2 exp6_14

ex4_3: $(EXERCISE4_3)
	$(CC) $(CFLAGS) -o ex4_3 $(EXERCISE4_3)

ex4_4: exercise4_4.c
	$(CC) $(CFLAGS) -o ex4_4 exercise4_4.c

exp5_1: example5_1.c
	$(CC) $(CFLAGS) -o exp5_1 example5_1.c

exp5_3: example5_3.c
	$(CC) $(CFLAGS) -o exp5_3 example5_3.c

exp5_12: example5_12.c
	$(CC) $(CFLAGS) -o exp5_12 example5_12.c

ex5_5: exercise5_5.c
	$(CC) $(CFLAGS) -o ex5_5 exercise5_5.c

exp6_2: example6_2.c
	$(CC) $(CFLAGS) -o exp6_2 example6_2.c

exp6_14: example6_14.c
	$(CC) $(CFLAGS) -o exp6_14 example6_14.c

ex6_9: exercise6_9.c
	$(CC) $(CFLAGS) -o ex6_9 exercise6_9.c

clean:
	@rm -fv $(PROGRAMS)
