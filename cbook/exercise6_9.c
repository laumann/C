#include <stdio.h>
#include <stdlib.h>

struct list_element {
	int data;
	struct list_element *next_p, *prev_p;
};

int
l_delete(struct list_element **root, int key)
{
	struct list_element *obsolete, *dummy;
	struct list_element **it = root;

	/* Scan the list */
	while (*it) {
		printf("In loop: %d\n", (*it)->data);
		if ((*it)->data == key) {
			/* Delete! */
			printf("Deleting %d, next_p=%d, prev_p=%d\n",
				(*it)->data, (*it)->next_p->data, (*it)->prev_p->data);
			dummy = (*it)->next_p;

			dummy->prev_p /* (*it) */ = (*it)->prev_p;
		/*	(*it)->next_p->prev_p = (*it)->prev_p;*/
			(*it)->prev_p->next_p = dummy /*(*it)->next_p*/;

			obsolete = *it;
			it = &dummy;
			free(obsolete);
			continue;
			
			/**it = pp;  Set it to previous node - will be incremented to next_p in following step */
		}
		it = &(*it)->next_p;
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

	l_delete(&root, 6);
	printf("Print after delete: "); l_print(root);

	exit(EXIT_SUCCESS);
}
