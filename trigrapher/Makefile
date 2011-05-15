#
# Trigrapher program:
#
# Given an input (file or stdin) convert all 'special characters' outside C's 96 character alphabet to
# their corresponding trigraphs

CC=gcc
CFLAGS=-Wall
TRIGRAPHER=trigrapher
RM=@rm

$(TRIGRAPHER): $(TRIGRAPHER).c
	$(CC) $(CFLAGS) -o $@ $@.c

clean:
	$(RM) -rv $(TRIGRAPHER)
