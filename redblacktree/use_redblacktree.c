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
		succ->key,
		predecessor(successor(succ))->key);

	printf("Deleting node (%d). ", successor(succ)->key);

	struct rb_node *del = tree_delete(tree, successor(succ));

	printf("del->key = %d. ", del->key);

	printf("Done.\nNew successor of min: %d (min is %d). ", successor(tree_minimum(tree))->key, tree_minimum(tree)->key);

	printf("Done.\nTraversing... ");

	in_order_traverse(tree);

	printf(" Done. Looking for node with key = 25... ");

	struct rb_node *twentyfive = find(tree, 25);

	printf("%s", twentyfive? "found.\nDeleting..." : "not found.");
/* TODO: Enable the following
	if (twentyfive) {
		del = tree_delete(tree, twentyfive);
	}
*/
	printf("\n Done. Traversing... ");

	in_order_traverse(tree);

	printf(" Done.\nExiting.\n");
	
	in_order_traverse(tree);
	
	printf(" Done.\nExiting.\n");;

	exit(0);
}
