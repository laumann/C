CC = gcc
CFLAGS = -Wall -DDEBUG
RM = rm -fv

OBJS=tdebug.o debug.o
HDRS=debug.h

test: $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	$(RM) *~ *.o test

.PHONY: clean