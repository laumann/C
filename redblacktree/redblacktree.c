#include "redblacktree.h"

static struct rb_node *grandparent(struct rb_node*);
static void rb_insert_fixup(struct rb_node*);
static void rotate_right(struct rb_node*);
static void rotate_left(struct rb_node*);
static void traverse_i(struct rb_node*);
static void paran_v(struct rb_node*);

/* Our current tree */
static struct redblack_tree **redblack_tree_p;

struct redblack_tree *
new_tree(void)
{
	struct redblack_tree *t = (struct redblack_tree*)malloc(sizeof(struct redblack_tree));
	t->size = 0;
	t->root = NULL;
	return t;
}

struct rb_node *
new_node(int data)
{
	struct rb_node *n = (struct rb_node*)malloc(sizeof(struct rb_node));
/*	n = { RED, data, NULL, NULL, NULL }; */
	n->color	= RED;
	n->data		= data;
	n->left_child 	=
	n->right_child 	=
	n->parent	= NULL;
	return n;
}

void
tree_insert(struct redblack_tree *tree, int data)
{
	struct rb_node 	*n = new_node(data),
			*y = NULL,
			*x = tree->root;
	
	redblack_tree_p = &tree;

	while (x) {
		y = x;
		if (n->data < x->data)
			x = x->left_child;
		else
			x = x->right_child;
	}
	n->parent = y;

	if (!y)
		(*redblack_tree_p)->root = n;
	else
		if (n->data < y->data)
			y->left_child = n;
		else
			y->right_child = n;

	(*redblack_tree_p)->size++;

	rb_insert_fixup(n);
}

void
rb_insert_fixup(struct rb_node *z)
{
	struct rb_node *g, *y;
	while ( z->parent && z->parent->color == RED && (g = grandparent(z)) ) {
		if (z->parent == g->left_child) {
			y = g->right_child;	/* Uncle */
			if (y && y->color == RED) {
				z->parent->color = y->color = BLACK;
				g->color = RED;
				z = g;
			}
			else {
				if (z == z->parent->right_child) {
					z = z->parent;
					rotate_left(z);
				}
				z->parent->color = BLACK;
				g->color = RED;
				rotate_right(g);
			}
		}
		else {	/* Same as first part with "right" and "left" exchanged */
			y = g->left_child;
			if (y && y->color == RED) {
				z->parent->color = y->color = BLACK;
				g->color = RED;
				z = g;
			}
			else { 
				if (z == z->parent->left_child) {
					z = z->parent;
					rotate_right(z);
				}
				z->parent->color = BLACK;
				g->color = RED;
				rotate_left(g);
			}
		}
	}
	(*redblack_tree_p)->root->color = BLACK;
}

void
in_order_traverse(struct redblack_tree *tree)
{
	printf("Root is '%d' (size: %d)\n", tree->root->data, tree->size);
	traverse_i(tree->root);
}

static void
traverse_i(struct rb_node *n)
{
	static int depth = 0;
	if (!n)
		return;
	depth++;
	traverse_i(n->left_child);
	printf("%d ", n->data);
	traverse_i(n->right_child);
	depth--;
}

void
paran_view(struct redblack_tree *tree)
{
	printf(" root=%d ", tree->root->data);	
	paran_v(tree->root);
}

static void
paran_v(struct rb_node *n)
{
	if (!n) 
		return;
	printf("(");
	printf("%d", n->data);
	paran_v(n->left_child);
	paran_v(n->right_child);
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
static void
rotate_right(struct rb_node *y)
{
	struct rb_node *x = y->left_child;
	y->left_child = x->right_child;
	if (x->right_child) x->right_child->parent = y;
	x->parent = y->parent;
	if (!y->parent)	(*redblack_tree_p)->root = x;
	else 	if (y == y->parent->left_child) y->parent->left_child = x;
		else y->parent->right_child = x;
	x->right_child = y;
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
static void
rotate_left(struct rb_node *x)
{

	struct rb_node *y = x->right_child;
	x->right_child = y->left_child;

	if (y->left_child)
		y->left_child->parent = x;
	
	y->parent = x->parent;

	if (!x->parent)
		(*redblack_tree_p)->root = y;
	else
		if (x == x->parent->left_child)
			x->parent->left_child = y;
		else
			x->parent->right_child = y;
	
	y->left_child = x;
	x->parent = y;
}

static struct rb_node *
grandparent(struct rb_node *n)
{
	if (n && n->parent)
		return n->parent->parent;
	else
		return NULL;
}
