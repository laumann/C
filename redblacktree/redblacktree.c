#include "redblacktree.h"

/* (static) Prototype declarations */

static struct rb_node *grandparent(struct rb_node*);
static struct rb_node *tree_search(struct rb_node*, int);

static void rb_insert_fixup(struct redblack_tree*, struct rb_node*);
static void rb_delete_fixup(struct redblack_tree*, struct rb_node*);
static void rotate_right(struct redblack_tree*, struct rb_node*);
static void rotate_left(struct redblack_tree*, struct rb_node*);

static struct rb_node *min(struct rb_node*);
static struct rb_node *max(struct rb_node*);
static struct rb_node *call_if_root(struct redblack_tree*, struct rb_node *(*f)(struct rb_node*));

static void traverse_i(struct rb_node*);
static void paran_v(struct rb_node*);

/* static void dump_node(struct rb_node*); */

/* NIL node */
static struct rb_node __NIL = {BLACK, 0, NULL, NULL, NULL, NULL};
static const struct rb_node *NIL = &__NIL;
#define nil	(struct rb_node*)NIL

#define ALLOC_TREE	(struct redblack_tree*)malloc(sizeof(struct redblack_tree))
#define ALLOC_NODE	(struct rb_node*)malloc(sizeof(struct rb_node))
#define OK		1
#define FAIL		0

/* functions */

int init_tree(struct redblack_tree **t)
{
	*t = ALLOC_TREE;
	if (!*t)
		return FAIL;
	(**t).size = 0;
	(**t).root = nil;
	return OK;
}

void tree_insert(struct redblack_tree *T, int key)
{
	struct rb_node *z = ALLOC_NODE; 
	struct rb_node *y = nil;
	struct rb_node *x = T->root;

	z->key = key;
	
	while (x != nil) {
		y = x;
		x = (z->key < x->key) ? x->left	: x->right;
	}
	z->parent = y;

	if (y == nil)
		T->root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;

	z->left = nil;
	z->right = nil;
	z->color = RED;

	T->size++;

	rb_insert_fixup(T, z);
}

/*
static void
dump_node(struct rb_node *x)
{
	if (x == NIL)
		printf("NIL ");
	printf("%p { %s, %d, ", x, (x->color == BLACK) ? "BLACK" : "RED", x->key);
	
	if (x->left == NIL) printf("(nil), ");
	else printf("%p, ", x->left);
	
	if (x->right == NIL) printf("(nil), ");
	else printf("%p, ", x->right);

	if (x->parent == NIL) printf("(nil) }\n");
	else printf("%p }\n", x->left);
}
*/

static void rb_insert_fixup(struct redblack_tree *T, struct rb_node *z)
{
	struct rb_node *g, *y;
	while (z->parent->color == RED) {	/* parent is never null */
		g = grandparent(z);
		if (z->parent == g->left) {
			y = g->right;	/* Uncle */
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				g->color = RED;
				z = g;
			} else {
				if (z == z->parent->right) {
					z = z->parent;
					rotate_left(T, z);
					g = grandparent(z);	/* New grand parent */
				}
				z->parent->color = BLACK;
				g->color = RED;
				rotate_right(T, g);
			}
		} else {	/* Same as first part with "right" and "left" exchanged */
			y = g->left;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				g->color = RED;
				z = g;
			} else { 
				if (z == z->parent->left) {
					z = z->parent;
					rotate_right(T, z);
					g = grandparent(z);
				}
				z->parent->color = BLACK;
				g->color = RED;
				rotate_left(T, g);
			}
		}
	}
	T->root->color = BLACK;
}

struct rb_node *tree_find(struct redblack_tree *tree, int key)
{
	return tree_search(tree->root, key);
}

static struct rb_node *tree_search(struct rb_node *x, int key)
{
	for ( ; x != nil && x->key != key; x = (key < x->key) ? x->left : x->right)
		;
	return x;
}

void in_order_traverse(struct redblack_tree *tree)
{
	printf("Root is '%d' (size: %d)\n", tree->root->key, tree->size);
	traverse_i(tree->root);
}

static void traverse_i(struct rb_node *n)
{
	static int depth = 0;
	if (n == nil)
		return;
	depth++;
	traverse_i(n->left);
	printf("%d ", n->key);
	traverse_i(n->right);
	depth--;
}

static void dotty(struct rb_node *n, FILE *fp)
{
	/* Declare node */
	fprintf(fp, "    n%d [label=\"%d\",color=%s,fontcolor=white,style=filled, shape=circle, width=0.5, fixedsize=true,fontname=Palatino];\n",
		n->key, n->key, (n->color == BLACK) ? "black" : "red");

	if (n->left != nil) {
		dotty(n->left, fp);
		fprintf(fp, "    n%d -- n%d;\n", n->key, n->left->key);
	}

	if (n->right != nil) {
		dotty(n->right, fp);
		fprintf(fp, "    n%d -- n%d;\n", n->key, n->right->key);
	}
}

/* Write a dot graph of the tree to file */
void dot(struct redblack_tree *tree, const char *name, const char *file, const char *mode)
{
	FILE *fp;
	
	if (tree->root == nil)	/* No tree - don't write anything! */
		return;

/*	printf("Writing tree to file '%s'\n", file);	*/
	fp = fopen(file, (mode) ? "a" : mode);
	if (!fp)
		return;
	
	fprintf(fp, "graph %s {\n", name);
	dotty(tree->root, fp);
	fprintf(fp, "}\n");

	if (fclose(fp))
		printf("Error closing file %s\n (%d)", file, errno);
}

void paran_view(struct redblack_tree *tree)
{
	printf(" root=%d ", tree->root->key);	
	paran_v(tree->root);
}

static void paran_v(struct rb_node *n)
{
	if (n == nil)
		return;
	printf("(");
	printf("%d", n->key);
	paran_v(n->left);
	paran_v(n->right);
	printf(")");
}

/*
    |        |
    y        x
   / \      / \
  x   c => a   y
 / \          / \
a   b        b   c

 */
static void rotate_right(struct redblack_tree *t, struct rb_node *y)
{
	struct rb_node *x = y->left;
	y->left = x->right;
	if (x->right != nil)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == nil)
		t->root = x;
	else 
		if (y == y->parent->left)
			y->parent->left = x;
		else 
			y->parent->right = x;
	x->right = y;
	y->parent = x;
}

/*
    |        |
    y        x
   / \      / \
  x   c <= a   y
 / \          / \
a   b        b   c

 */
static void rotate_left(struct redblack_tree *t, struct rb_node *x)
{
	struct rb_node *y = x->right;
	x->right = y->left;

	if (y->left != nil)
		y->left->parent = x;
	
	y->parent = x->parent;

	if (x->parent == nil)
		t->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	
	y->left = x;
	x->parent = y;
}

static inline struct rb_node *grandparent(struct rb_node *n)
{
	return (n == nil || n->parent == nil) ? nil : n->parent->parent;
}

struct rb_node *tree_delete(struct redblack_tree *t, struct rb_node *z)
{
	struct rb_node *y, *x;

	y = (z->left == nil || z->right == nil)
		? z
		: successor(z);

	x = (y->left != nil)
		? y->left
		: y->right;
	
	x->parent = y->parent;
	
	if (y->parent == nil)
		t->root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	
	if (y != z) { /* true <=> z has two children */
		z->key = y->key;
		/* Copy y's satellite data into z */
	}
	
	if (y->color == BLACK)
		rb_delete_fixup(t, x);

	t->size--;
	return y;
}

/*
 * TODO Write code that thoroughly tests this (all the various cases)
 */
static void rb_delete_fixup(struct redblack_tree *t, struct rb_node *x)
{
	struct rb_node *w;
	while (x != t->root && x->color == BLACK) {
		/* x is a left child */
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotate_left(t, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rotate_right(t, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rotate_left(t, x->parent);
				x = t->root;
			}
		} else {	/* Same as above, but "right" and "left" exchanged */
			w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotate_right(t, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					rotate_left(t, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rotate_right(t, x->parent);
				x = t->root;
			}
		}
	}
	x->color = BLACK;
}

struct rb_node *tree_maximum(struct redblack_tree* t)
{
	return call_if_root(t, &max);
}

struct rb_node *tree_minimum(struct redblack_tree* t)
{
	return call_if_root(t, &min);
}

struct rb_node *call_if_root(struct redblack_tree* t, struct rb_node *(*f)(struct rb_node*))
{
	if (t->root != nil)
		return f(t->root);
	return nil;
}

struct rb_node *successor(struct rb_node *x)
{
	if (x->right != nil)
		return min(x->right);

	struct rb_node *y = x->parent;
	while (y != nil && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

struct rb_node *predecessor(struct rb_node *x)
{
	if (x->left != nil)
		return max(x->left);

	struct rb_node *y = x->parent;
	while (y != nil && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

static inline struct rb_node *
min(struct rb_node *x)
{
	for (; x->left != nil; x = x->left)
		;
	return x;
}

static inline struct rb_node *
max(struct rb_node *x)
{
	for (; x->right != nil; x = x->right)
		;
	return x;
}

