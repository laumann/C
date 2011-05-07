#include <stdio.h>
#include <stdlib.h>

struct list_ele {
	int data;
	struct list_ele *pointer;
};

struct list_ele *sortfun(struct list_ele*);

int
main(int argc, char** argv)
{
	/* 5, 99, -7*/
	struct list_ele *root, *root_p;

	root = (struct list_ele*)malloc(sizeof(struct list_ele));

	root->data = 5;

	root->pointer = (struct list_ele*)malloc(sizeof(struct list_ele));
	root->pointer->data = 99;

	root->pointer->pointer = (struct list_ele*)malloc(sizeof(struct list_ele));
	root->pointer->pointer->data = -7;
	root->pointer->pointer->pointer = NULL;

	root_p = root;

	for ( ; root_p; root_p = root_p->pointer)
		printf(" %d ->", root_p->data);
	
	printf("\n");

	root = sortfun(root);

	for ( ; root; root = root->pointer)
		printf("Contents: %d", root->data);

	exit(EXIT_SUCCESS);
}

struct list_ele *
sortfun(struct list_ele *root)
{
	int exchange;
	struct list_ele *next_p, *this_p, dummy;

	dummy.pointer = root;
	
	/*
	 * Algorithm: repeatedly scan list, If two items are out of order,
	 * link them the other way around. Stops if full pass is made without
	 * exchange
	 */
	do {
		exchange = 0;
		this_p = &dummy;
		while ( (next_p = this_p->pointer)
			 && next_p->pointer) {
			if (next_p->data < next_p->pointer->data) {
				/* Exchange */
				exchange = 1;
				printf("Exchanging %d and %d\n", next_p->data, next_p->pointer->data);
				this_p->pointer		 = next_p->pointer;
				next_p->pointer 	 = this_p->pointer->pointer;
				this_p->pointer->pointer = next_p;
			}
			printf("next_p->data: %d, this_p->data: %d\n", next_p->data, this_p->data);
		/*	printf("Inner loop\n");*/
		}
	/*	printf("Outer loop\n");*/
	} while (exchange);

	return dummy.pointer;
}
