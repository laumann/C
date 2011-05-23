#include "redblacktree.h"

int
main()
{
	printf("Constructing new tree... ");
	struct redblack_tree *tree = new_tree();
	int i;

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

	printf(" Done.\nSuccessor of min: ");

	struct rb_node *min = tree_minimum(tree), *succ;
	succ = successor(min);

	printf("%d. Done.\nPredecessor of successor's successor: %d. Done.\n",
		succ->data,
		predecessor(successor(succ))->data);

	printf("Deleting node (%d). ", succ->data);

	struct rb_node *del = tree_delete(tree, succ);

	printf("del->data = %d. ", del->data);

	printf("Done.\nNew successor of min: %d (min is %d). ", successor(tree_minimum(tree))->data, tree_minimum(tree)->data);

	printf("Done.\nTraversing... ");

	in_order_traverse(tree);

	printf(" Done.\nExiting.\n");

	exit(0);
}
