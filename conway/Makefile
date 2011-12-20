CC = gcc
CFLAGS = -Wall
RM = rm -rvf

OBJS = conway.o

conway: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	@$(RM) $(OBJS) conway *~

.PHONY: clean