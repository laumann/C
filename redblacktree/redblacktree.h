#ifndef _REDBLACKTREE_H
#define _REDBLACKTREE_H

#include <stdio.h>
#include <stdlib.h>

#define RED	1
#define BLACK	0

struct redblack_tree {
	struct rb_node *root;
	int size;
};


struct rb_node {
	short color;	/* 0=BLACK, 1=RED */
	int data;
	struct rb_node *left_child, *right_child, *parent;
};

struct redblack_tree *new_tree();
void tree_insert(struct redblack_tree*, int);
void in_order_traverse(struct redblack_tree*);
void paran_view(struct redblack_tree*);

#endif/*_REDBLACKTREE_H*/
