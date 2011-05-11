#include "redblacktree.h"

int
main()
{
	printf("Constructing new tree... ");
	struct tree *tree;
	int i;

	new_tree(&tree);
     
	printf("Done.\nInserting nodes... ");
	/* 4 2 6 3 1 5 7 */
	
	tree_insert(tree, 4);
	tree_insert(tree, 2);
	tree_insert(tree, 6);
	tree_insert(tree, 3);
	tree_insert(tree, 1);
	tree_insert(tree, 5);
	tree_insert(tree, 7);

	printf("Done.\nTraversing... ");

	in_order_traverse(tree);

	printf("Done.\nParanthetical view: ");

	paran_view(tree);

	printf("Done.\nInserting more nodes... ");

	for (i=9; i<30; i++) {
		tree_insert(tree, i);
	}

	printf("Done.\nTraversing... ");

	in_order_traverse(tree);

	printf("Done.\nInserting nodes in reversed order...");

	for (i=50; i>30; i--) {
		tree_insert(tree, i);
	}

	printf("Done.\nTraversing... ");

	in_order_traverse(tree);

	printf(" Done.\nExiting.\n");
	exit(EXIT_SUCCESS);
}
