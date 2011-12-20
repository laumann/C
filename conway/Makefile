CC = gcc
CFLAGS = -Wall
LFLAGS = -lncurses
RM = rm -rvf

OBJS = conway.o

conway: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $< $(LFLAGS)

clean:
	@$(RM) $(OBJS) conway *~

.PHONY: clean