#include "redblacktree.h"

/* (static) Prototype declarations */

static struct rb_node *grandparent(struct rb_node*);
static struct rb_node *new_node(int);
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
new_node(int key)
{
	struct rb_node *n = (struct rb_node*)malloc(sizeof(struct rb_node));
	n->color	= RED;
	n->key		= key;
	n->left 	=
	n->right 	=
	n->parent	= NULL;
	return n;
}

void
tree_insert(struct redblack_tree *T, int key)
{
	struct rb_node 	*n = new_node(key),
			*y = NULL,
			*x = T->root;
	
	while (x) {
		y = x;
		if (n->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	n->parent = y;

	if (!y)
		T->root = n;
	else
		if (n->key < y->key)
			y->left = n;
		else
			y->right = n;

	T->size++;

	rb_insert_fixup(T, n);
}

static void
rb_insert_fixup(struct redblack_tree *T, struct rb_node *z)
{
	struct rb_node *g, *y;
	while ( z->parent && z->parent->color == RED && (g = grandparent(z))) {
		if (z->parent == g->left) {
			y = g->right;	/* Uncle */
			if (y && y->color == RED) {
				z->parent->color = y->color = BLACK;
				g->color = RED;
				z = g;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					rotate_left(T, z);
				}
				z->parent->color = BLACK;
				g->color = RED;
				rotate_right(T, g);
			}
		}
		else {	/* Same as first part with "right" and "left" exchanged */
			y = g->left;
			if (y && y->color == RED) {
				z->parent->color = y->color = BLACK;
				g->color = RED;
				z = g;
			}
			else { 
				if (z == z->parent->left) {
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

struct rb_node *
find(struct redblack_tree *tree, int key)
{
	return tree_search(tree->root, key);
}

static struct rb_node *
tree_search(struct rb_node *x, int key)
{
	for ( ; x && x->key != key; x = (key < x->key) ? x->left : x->right)
		;
	return x;
}

void
in_order_traverse(struct redblack_tree *tree)
{
	printf("Root is '%d' (size: %d)\n", tree->root->key, tree->size);
	traverse_i(tree->root);
}

static void
traverse_i(struct rb_node *n)
{
	static int depth = 0;
	if (!n)
		return;
	depth++;
	traverse_i(n->left);
	printf("%d ", n->key);
	traverse_i(n->right);
	depth--;
}

void
paran_view(struct redblack_tree *tree)
{
	printf(" root=%d ", tree->root->key);	
	paran_v(tree->root);
}

static void
paran_v(struct rb_node *n)
{
	if (!n) 
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
static void
rotate_right(struct redblack_tree *t, struct rb_node *y)
{
	struct rb_node *x = y->left;
	y->left = x->right;
	if (x->right)
		x->right->parent = y;
	x->parent = y->parent;
	if (!y->parent)
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
static void
rotate_left(struct redblack_tree *t, struct rb_node *x)
{
	struct rb_node *y = x->right;
	x->right = y->left;

	if (y->left)
		y->left->parent = x;
	
	y->parent = x->parent;

	if (!x->parent)
		t->root = y;
	else
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	
	y->left = x;
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

/*
 * TODO: Case where z has two children does not work properly.
 * Question: When y is set to successor(z), how come that y is returned?
 *		Shouldn't it be z (or a copy of z) that's returned?
 */
struct rb_node *
tree_delete(struct redblack_tree *T, struct rb_node *z)
{
	struct rb_node *y, *x;
	fprintf(stderr, "Deleting %d\n", z->key);

	/* Three cases - no children, one child or two children */

	if (z->left && z->right) 				{
		fprintf(stderr, "Getting succ(%d) = ", z->key);
		y = successor(z);
		fprintf(stderr, "%d\n", y->key);			}
	else
		y = z; /* z has one or no children */

	print_null_or_not("y", y);

	if (y->left)
		x = y->left;
	else
		x = y->right;

	print_null_or_not("x", x);

	if (x)
		x->parent = y->parent;
	
	if (!y->parent)
		T->root = x;
	else
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	
	if (y != z) { /* z has two children */
		fprintf(stderr, "y != z\n");
		z->key = y->key;
		z->left = y->left;
		z->right = y->right;
		z->parent = y->parent;
	}
	
	if (y->color == BLACK) {
		fprintf(stderr, "\nFixing delete!\n");
		rb_delete_fixup(T, x);
	}
	T->size--;
	return y;
}

/*
 * TODO: Write code that tests this...
 */
static void
rb_delete_fixup(struct redblack_tree *T, struct rb_node *x)
{
	struct rb_node *w;
	while (x != T->root && x->color == BLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (!w) break;
			if (/*!!*/ w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotate_left(T, x->parent);
				w = x->parent->right;
			}
			if (/*!!*/ w->left && w->left->color == BLACK &&
				w->right && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else {	if (w->right && w->right->color == BLACK && w->left) {
					w->left->color = RED;
					rotate_right(T, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				if (w->right) w->right->color = BLACK;
				rotate_left(T, x->parent);
				x = T->root;
			}
		}
		else {	/* Same as above, but "right" and "left" exchanged */
			w = x->parent->left;
			if (!w) break;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotate_right(T, x->parent);
				w = x->parent->left;
			}
			if (w->left && w->left->color == BLACK
				&& w->right && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else {	if (w->left && w->left->color == BLACK && w->right) {
					w->right->color = RED;
					rotate_left(T, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				if (w->left) w->left->color = BLACK;
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
	if (x->right)
		return min(x->right);
	struct rb_node *y = x->parent;
	while (y && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

struct rb_node *
predecessor(struct rb_node *x)
{
	if (x->left)
		return max(x->left);
	struct rb_node *y = x->parent;
	while (y && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

static struct rb_node *
min(struct rb_node *x)
{
	while (x->left)
		x = x->left;
	return x;
}

static struct rb_node *
max(struct rb_node *x)
{
	while (x->right)
		x = x->right;
	return x;
}

static void
print_null_or_not(char *name, struct rb_node *obj)
{
	if (obj)
		fprintf(stderr, "%s is %d\n", name, obj->key);
	else
		fprintf(stderr, "%s is null\n", name);
}
