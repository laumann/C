CC	:= gcc
CFLAGS	:= -Wall
RM	:= rm -rf

OBJECTS = main.o yamlparser.o

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

main.o:
yamlparser.o: yamlparser.h

clean:
	$(RM) main $(OBJECTS)

.PHONY: clean
