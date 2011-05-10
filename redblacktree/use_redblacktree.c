#include "redblacktree.h"

int
main()
{
	printf("Constructing new tree... ");
	struct tree *tree;
	int i;

	new_tree(&tree);
     
	printf("Done.\nInserting nodes... ");

	for (i=1; i<8; i++) {
		tree_insert(tree, i);
	}
	/* 4 2 6 3 1 5 7 */

	for (i=8; i<30; i++) {
		tree_insert(tree, i);
	}

	printf("Done.\nTraversing... ");

	in_order_traverse(tree);

	printf("Done.\n Paranthetical view: ");

	paran_view(tree);

	printf("Done.\nExiting.\n");
	exit(EXIT_SUCCESS);
}
