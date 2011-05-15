#ifndef _REDBLACKTREE_H
#define _REDBLACKTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define RED	1
#define BLACK	0

struct tree {
	struct node *root;
	int size;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
};


struct node {
	short color;	/* 0=BLACK, 1=RED */
	int data;
	struct node *left_child, *right_child, *parent;
};

void new_tree();
void tree_insert(struct tree*, int);
void in_order_traverse(struct tree*);
void paran_view(struct tree*);

#endif/*_REDBLACKTREE_H*/
