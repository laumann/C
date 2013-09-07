#ifndef _REDBLACKTREE_H
#define _REDBLACKTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define RED	1
#define BLACK	0

struct redblack_tree {
	struct rb_node *root;
	int size;
};


struct rb_node {
	short color;	/* 0=BLACK, 1=RED */
	int key;
	void *elm;
	struct rb_node *left;
	struct rb_node *right;
	struct rb_node *parent;
};

int init_tree(struct redblack_tree**);
void tree_insert(struct redblack_tree*, int);
struct rb_node *tree_delete(struct redblack_tree*, struct rb_node*);
struct rb_node *tree_find(struct redblack_tree*, int key);

struct rb_node *tree_maximum(struct redblack_tree*);
struct rb_node *tree_minimum(struct redblack_tree*);
struct rb_node *successor(struct rb_node*);
struct rb_node *predecessor(struct rb_node*);

void in_order_traverse(struct redblack_tree*);
void paran_view(struct redblack_tree*);
void dot(struct redblack_tree*, const char *, const char *, const char *);

#endif/*_REDBLACKTREE_H*/
