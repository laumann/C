CC=gcc
CFLAGS=-Wall

H_FILES=bswap.h git-compat-util.h progress.h
C_FILES=progress.c use_progress.c

BIN=use_progress
BINDIR=bin

.PHONY: help
help:
	@echo "This progress bar is taken directly from git -- because I like it, and it serves"
	@echo "as a good exercise to see how some C code works. Run:"
	@echo ""
	@echo "  'make example'"
	@echo ""
	@echo "or"
	@echo ""
	@echo "  'make run_example'"
	@echo ""
	@echo "to see an example program."

.PHONY: example
example: $(BINDIR)/$(BIN)

.PHONY: run_example
run_example: | example
	$(BINDIR)/$(BIN)

MAIN=$(BINDIR)/$(BIN)
$(MAIN): $(C_FILES) $(H_FILES) | $(BINDIR)
	$(CC) $(CFLAGS) $(C_FILES) -o $@

$(BINDIR):
	mkdir $(BINDIR)

print: *.c
	lpr -p $?
	touch print

.PHONY: clean
clean:
	@rm -rfv $(BINDIR)
