CC=gcc
CFLAGS=-Wall
H_FILES=bswap.h git-compat-util.h progress.h
C_FILES=progress.c use_progress.c
BIN=use_progress

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

example: $(C_FILES) $(H_FILES)
	$(CC) $(CFLAGS) -o $(BIN) $(C_FILES)

run_example: example
	./$(BIN)

.PHONY: clean
clean:
	@rm -v $(BIN)
