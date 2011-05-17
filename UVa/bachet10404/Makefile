CC := gcc
CFLAGS := -Wall

bachet: main.c
	$(CC) $(CFLAGS) -o $@ $<

test: bachet
	@./bachet < input

clean:
	@rm -v bachet

.PHONY: test clean
