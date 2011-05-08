#include <stdio.h>
#include <stdlib.h>

struct list_element {
	int data;
	struct list_element *next_p, *prev_p;
};

int
l_delete(struct list_element **root, int key)
{
	/* Use pointer to root */
	struct list_element *doomed, *current = *root;
	short delete = 0;

	for ( ; current ; ) {
		if (current->data == key) {
			if (!current->prev_p) {
				*root = current->next_p;
				(*root)->prev_p = NULL;
			}
			else if (!current->next_p) {
				current->prev_p->next_p = NULL;
			}
			else {
				current->prev_p->next_p = current->next_p;
				current->next_p->prev_p = current->prev_p;
			}
			doomed = current;
			delete = 1;
		}
		current = current->next_p;
		if (delete) {
			free(doomed);
			delete = 0;
		}
	}
	return 0;
}

void
l_insert(struct list_element **root, int data)
{
	struct list_element *new = (struct list_element*)malloc(sizeof(struct list_element));

	while ((*root)->next_p) 
		root = &(*root)->next_p;
	
	/* Reached end - allocate */
	(*root)->next_p = new;
	
	/* Init */
	new->next_p = NULL;
	new->prev_p = *root;
	new->data = data;
}

void
l_print(struct list_element *root)
{
	while (root) {
		printf("%d ", root->data);
		root = root->next_p;
	}
	printf("\n");
}

void
l_print_reverse(struct list_element *root)
{
	/* Find last, then follow prev_p back */
	while (root->next_p) root = root->next_p;
	while (root) {
		printf("%d ", root->data);
		root = root->prev_p;
	}
	printf("\n");
}

int
main()
{
	struct list_element *root;

	/* Init */
	root = (struct list_element*)malloc(sizeof(struct list_element));
	root->next_p = root->prev_p = NULL;
	root->data = 4;
	
	/* 4 2 6 1 5 3 7 */
	l_insert(&root, 2);
	l_insert(&root, 6);
	l_insert(&root, 1);
	l_insert(&root, 5);
	l_insert(&root, 3);
	l_insert(&root, 6);
	l_insert(&root, 7);

	printf("Print:         "); l_print(root);
	printf("Reverse print: "); l_print_reverse(root);

	l_delete(&root, 6); /* Delete element in middle (twice) */
	printf("Print after delete (6): "); l_print(root);

	l_delete(&root, 4); /* Delete first */
	printf("Print after delete (4): "); l_print(root);

	l_delete(&root, 7); /* Delete last */
	printf("Print after delete (7): "); l_print(root);

	exit(EXIT_SUCCESS);
}
