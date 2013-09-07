#include "redblacktree.h"

static const char out[] = "rbdel.dot";

int main(int argc, char *argv[])
{
	struct redblack_tree *tree;

	init_tree(&tree);

	/* insert 4, 3, 5 gives */

	/*
	      5
	     / \
	    2   8
	   / \ / \
	  1  3 7  9 => 5 2 8 1 3 7 9
	*/

	int numbers[] = { 5, 2, 8, 1, 3, 7, 9, 4, 10, 11, (int)NULL };
	int *n = numbers;
	for (; *n ;)
		tree_insert(tree, *n++);
	
	printf("Inserted numbers\n");

	/* Print - Should be (5(2(1)(3))(8(7)(9))) */
	paran_view(tree);
	printf("\n");

	dot(tree, "init", out, "w");

	tree_delete(tree, tree_find(tree, 1));
	paran_view(tree);
	printf("\n");

	dot(tree, "del1", out, "a");

	tree_delete(tree, tree_find(tree, 8));
	paran_view(tree);
	printf("\n");

	dot(tree, "del8", out, "a");

	/* Last test: Delete the root! */
	tree_delete(tree, tree->root);
	dot(tree, "delroot", out, "a");

	return 0;
}
