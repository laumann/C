#include "redblacktree.h"

int main()
{
	struct redblack_tree *tree;
	const char out[] = "bigtree.dot";
	int i;

	init_tree(&tree);

	/* 4 2 6 3 1 5 7 */
	
	tree_insert(tree, 4);
	tree_insert(tree, 2);
	tree_insert(tree, 6);
	tree_insert(tree, 3);
	tree_insert(tree, 1);
	tree_insert(tree, 5);
	tree_insert(tree, 7);

	in_order_traverse(tree);
	paran_view(tree);
	printf("\n");

	dot(tree, "a", out, "w");
	
	for (i=9; i<30; i++)
		tree_insert(tree, i);

	in_order_traverse(tree);
	printf("\n");

	dot(tree, "b", out, "a");

	for (i = 50; i > 30; i--)
		tree_insert(tree, i);

	in_order_traverse(tree);
	printf("\n");

	dot(tree, "c", out, "w");

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
	dot(tree, "del3", out, "a");

	printf(" Done. Looking for node with key = 25... ");

	struct rb_node *twentyfive = tree_find(tree, 25);

	printf("%s", twentyfive ? "found.\nDeleting..." : "not found.");
	
	if (twentyfive)
		del = tree_delete(tree, twentyfive);

	del = tree_delete(tree, tree_find(tree, 5));

	dot(tree, "del5", out, "a");

	tree_delete(tree, tree_find(tree, 12));
	dot(tree, "del12", out, "a");

	tree_delete(tree, tree_find(tree, 1));
	dot(tree, "del1", out, "a");

	tree_delete(tree, tree_find(tree, 4));
	dot(tree, "del4", out, "a");
	
	tree_delete(tree, tree_find(tree, 9));
	dot(tree, "del9", out, "a");

	tree_delete(tree, tree_find(tree, 23));

	dot(tree, "del23", out, "a");

	printf("\n Done. Traversing... ");

	in_order_traverse(tree);

	printf(" Done.\nExiting.\n");;

	exit(0);
}
