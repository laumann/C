CC=gcc
CFLAGS=-Wall
EXECUTABLE=binarytree

help:
	@echo "A binary search tree implementation (should probably have been named as such)."
	@echo ""
	@echo "The implementation and the demonstration are contained in the same source file"
	@echo "(which is probably not a good idea). The C source also demonstrates the usage of"
	@echo "the __FILE__, __DATE__ and __TIME__ predefined C entities. Here are the targets:"
	@echo ""
	@echo "    help          Print this help screen (default)."
	@echo "    run           Run the executable (depends on target binarytree)."
	@echo "    binarytree    Build the executable."
	@echo "    clean         Clean the project (removes executable)."

.PHONY: run
run: binarytree
	@./$(EXECUTABLE)

$(EXECUTABLE): binarytree.c binarytree.h
	$(CC) $(CFLAGS) -o $@ binarytree.c

.PHONY: clean
clean:
	@rm -rfv $(EXECUTABLE)
