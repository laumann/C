
CC=gcc
CFLAGS=-Wall -O2
LIB=redblacktree.c
HDRS=redblacktree.h

all: use_redblacktree rbdel

use_redblacktree: use_redblacktree.c $(LIB) $(HDRS)
	@echo "Building 'use_redblacktree'"
	$(CC) $(CFLAGS) -o $@ $< $(LIB)

rbdel: rbdel.c $(LIB) $(HDRS)
	@echo "Building 'rbdel'"
	$(CC) $(CFLAGS) -o $@ $< $(LIB)

%.ps: %.dot
	dot -q -Tps -o$@ $<

clean: clean-graphs
	@rm -fv use_redblacktree rbdel *~ *.swp

clean-graphs:
	@rm -fv *.ps *.dot

.PHONY: clean clean-graphs
