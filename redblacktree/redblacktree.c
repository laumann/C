#include "redblacktree.h"

/* (static) Prototype declarations */

static struct rb_node *grandparent(struct rb_node*);
static struct rb_node *new_node(int);

static void rb_insert_fixup(struct redblack_tree*, struct rb_node*);
static void rb_delete_fixup(struct redblack_tree*, struct rb_node*);
static void rotate_right(struct redblack_tree*, struct rb_node*);
static void rotate_left(struct redblack_tree*, struct rb_node*);

static struct rb_node *min(struct rb_node*);
static struct rb_node *max(struct rb_node*);
static struct rb_node *call_if_root(struct redblack_tree*, struct rb_node *(*f)(struct rb_node*));

static void traverse_i(struct rb_node*);
static void paran_v(struct rb_node*);

static void print_null_or_not(char*, struct rb_node*);

/* functions */

struct redblack_tree *
new_tree(void)
{
	struct redblack_tree *t = (struct redblack_tree*)malloc(sizeof(struct redblack_tree));
	t->size = 0;
	t->root = NULL;
	return t;
}

static struct rb_node *
new_node(int data)
{
	struct rb_node *n = (struct rb_node*)malloc(sizeof(struct rb_node));
	n->color	= RED;
	n->data		= data;
	n->left_child 	=
	n->right_child 	=
	n->parent	= NULL;
	return n;
}

void
tree_insert(struct redblack_tree *T, int data)
{
	struct rb_node 	*n = new_node(data),
			*y = NULL,
			*x = T->root;
	
	while (x) {
		y = x;
		if (n->data < x->data)
			x = x->left_child;
		else
			x = x->right_child;
	}

	n->parent = y;

	if (!y)
		T->root = n;
	else
		if (n->data < y->data)
			y->left_child = n;
		else
			y->right_child = n;

	T->size++;

	rb_insert_fixup(T, n);
}

static void
rb_insert_fixup(struct redblack_tree *T, struct rb_node *z)
{
	struct rb_node *g, *y;
	while ( z->parent && z->parent->color == RED && (g = grandparent(z))) {
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
					rotate_left(T, z);
				}
				z->parent->color = BLACK;
				g->color = RED;
				rotate_right(T, g);
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
					rotate_right(T, z);
				}
				z->parent->color = BLACK;
				g->color = RED;
				rotate_left(T, g);
			}
		}
	}
	T->root->color = BLACK;
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
rotate_right(struct redblack_tree *t, struct rb_node *y)
{
	struct rb_node *x = y->left_child;
	y->left_child = x->right_child;
	if (x->right_child)
		x->right_child->parent = y;
	x->parent = y->parent;
	if (!y->parent)
		t->root = x;
	else 
		if (y == y->parent->left_child)
			y->parent->left_child = x;
		else 
			y->parent->right_child = x;
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
rotate_left(struct redblack_tree *t, struct rb_node *x)
{
	struct rb_node *y = x->right_child;
	x->right_child = y->left_child;

	if (y->left_child)
		y->left_child->parent = x;
	
	y->parent = x->parent;

	if (!x->parent)
		t->root = y;
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

struct rb_node *
tree_delete(struct redblack_tree *T, struct rb_node *z)
{
	struct rb_node *y, *x;
	fprintf(stderr, "Deleting %d\n", z->data);

	if (z->left_child && z->right_child)
		y = successor(z);
	else
		y = z;

	print_null_or_not("y", y);

	if (y->left_child)
		x = y->left_child;
	else
		x = y->right_child;

	print_null_or_not("x", x);

	if (x)
		x->parent = y->parent;
	
	if (!y->parent)
		T->root = x;
	else
		if (y == y->parent->left_child)
			y->parent->left_child = x;
		else
			y->parent->right_child = x;
	
	if (y != z) { /* z has two children */
		fprintf(stderr, "y != z\n");
		z->data = y->data;
		z->left_child = y->left_child;
		z->right_child = y->right_child;
		z->parent = y->parent;
	}
		
	if (y->color == BLACK) {
		fprintf(stderr, "\nFixing delete!\n");
		rb_delete_fixup(T, x);
	}
	T->size--;
	return y;
}

static void
rb_delete_fixup(struct redblack_tree *T, struct rb_node *x)
{
	struct rb_node *w;
	while (x != T->root && x->color == BLACK) {
		if (x == x->parent->left_child) {
			w = x->parent->right_child;
			if (!w) break;
			if (/*!!*/ w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotate_left(T, x->parent);
				w = x->parent->right_child;
			}
			if (/*!!*/ w->left_child && w->left_child->color == BLACK &&
				w->right_child && w->right_child->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else {	if (w->right_child && w->right_child->color == BLACK && w->left_child) {
					w->left_child->color = RED;
					rotate_right(T, w);
					w = x->parent->right_child;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				if (w->right_child) w->right_child->color = BLACK;
				rotate_left(T, x->parent);
				x = T->root;
			}
		}
		else {	/* Same as above, but "right" and "left" exchanged */
			w = x->parent->left_child;
			if (!w) break;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotate_right(T, x->parent);
				w = x->parent->left_child;
			}
			if (w->left_child && w->left_child->color == BLACK
				&& w->right_child && w->right_child->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else {	if (w->left_child && w->left_child->color == BLACK && w->right_child) {
					w->right_child->color = RED;
					rotate_left(T, w);
					w = x->parent->left_child;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				if (w->left_child) w->left_child->color = BLACK;
				rotate_right(T, x->parent);
				x = T->root;
			}
		}
	}
	x->color = BLACK;
}

struct rb_node *
tree_maximum(struct redblack_tree* t)
{
	return call_if_root(t, &max);
}

struct rb_node *
tree_minimum(struct redblack_tree* t)
{
	return call_if_root(t, &min);
}

struct rb_node *
call_if_root(struct redblack_tree* t, struct rb_node *(*f)(struct rb_node*))
{
	if (t->root)
		return f(t->root);
	return NULL;
}

struct rb_node *
successor(struct rb_node *x)
{
	if (x->right_child)
		return min(x->right_child);
	struct rb_node *y = x->parent;
	while (y && x == y->right_child) {
		x = y;
		y = y->parent;
	}
	return y;
}

struct rb_node *
predecessor(struct rb_node *x)
{
	if (x->left_child)
		return max(x->left_child);
	struct rb_node *y = x->parent;
	while (y && x == y->left_child) {
		x = y;
		y = y->parent;
	}
	return y;
}

static struct rb_node *
min(struct rb_node *x)
{
	while (x->left_child)
		x = x->left_child;
	return x;
}

static struct rb_node *
max(struct rb_node *x)
{
	while (x->right_child)
		x = x->right_child;
	return x;
}

static void
print_null_or_not(char *name, struct rb_node *obj)
{
	fprintf(stderr, "%s is %s\n", name, obj? "not null" : "null");
}
