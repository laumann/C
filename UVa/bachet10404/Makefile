CC 	:= gcc
CFLAGS 	:= -Wall -lm -lcrypt -O2 -pipe -ansi

bachet: main.c
	$(CC) $(CFLAGS) -o $@ $<

test: bachet
	@./bachet < input

clean:
	@rm -v bachet

.PHONY: test clean
