
CC=gcc
CFLAGS=-Wall
C_SRC=use_redblacktree.c redblacktree.c
C_HDRS=redblacktree.h

use_redblacktree: $(C_SRC) $(C_HDRS)
	$(CC) $(CFLAGS) -o use_redblacktree use_redblacktree.c redblacktree.c

.PHONY: clean
clean:
	@rm -fv use_redblacktree *~ *.swp
