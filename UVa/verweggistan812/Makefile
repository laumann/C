CC := gcc
CFLAGS := -lm -lcrypt -O2 -pipe -ansi
PROGRAM := verweggistan

$(PROGRAM): main.c
	$(CC) $(CFLAGS) -o $@ $<

debug: main.c
	$(CC) $(CFLAGS) -Wall -o $(PROGRAM) $<
	@./$(PROGRAM) < input

test: $(PROGRAM)
	@./$(PROGRAM) < input

clean:
	@rm -v $(PROGRAM)

.PHONY: test clean debug
