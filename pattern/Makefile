CC=gcc
CFLAGS=-Wall

CFILES=$(wildcard *.c)
HFILES=$(wildcard *.h)

BIN=bin

$(BIN)/pattern: $(CFILES) $(HFILES) | $(BIN)
	$(CC) $(CFLAGS) -o $@ $(CFILES)

$(BIN):
	@mkdir $(BIN)

.PHONY: clean
clean:
	@rm -rfv $(BIN)
