#include <stdio.h>
#include <stdlib.h>

#include "binarytree.h"

/* Tree search algorithm */
struct tree_node *
t_search(struct tree_node *root, int V)
{
	while (root) {
		printf("Looking for %d, looking at %d\n", V, root->data);
		if (root->data == V)
			return root;
		if (root->data < V)
			root = root->right_p;
		else
			root = root->left_p;
	}

	return NULL;
}

/**
 * Insert node into tree. Return values:
 * 0 = success
 * 1 = value already in tree
 * 2 = malloc error
 *
 * Notice how we use a pointer to a pointer to the tree root node.
 */
int
t_insert(struct tree_node **root, int V)
{
	while(*root) {
		if ((*root)->data == V)
			return 1;
		if ((*root)->data > V)
			root = &((*root)->left_p);
		else
			root = &((*root)->right_p);
	}
	if (!(*root = (struct tree_node*)malloc(sizeof(struct tree_node))))
		return 2;
	(*root)->data = V;
	(*root)->left_p = NULL;
	(*root)->right_p = NULL;
	return 0;
}

void
t_walk(struct tree_node *root_p)
{
	if (!root_p)
		return;
	t_walk(root_p->left_p);
	printf(" %d ", root_p->data);
	t_walk(root_p->right_p);
}

int
main(int argc, char** argv)
{
	printf("This is:\t%s\nCompiled on:\t%s %s\n\n", __FILE__, __DATE__, __TIME__);

	struct tree_node *tp, *root_p = 0;
	int i, *np;

	/* 4 2 6 1 3 5 7 */
	int numbers[] = { 4, 2, 6, 1, 3, 5, 7, NULL };

	printf("Inserted order:  4  2  6  1  3  5  7\n\n");

	for (np = &numbers[0]; *np; np++)
		t_insert(&root_p, *np);

	for (i=1; i<9; i++)
		if ( (tp = t_search(root_p, i)) )
			printf("Found %d\n", i);
		else
			printf("Not found, %d\n", i);
	
	t_walk(root_p); printf("\n");
	exit(EXIT_SUCCESS);
}
