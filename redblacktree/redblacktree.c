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

static void print_nil_or_not(char*, struct rb_node*);
static void dump_node(struct rb_node*);

/* NIL node */
static struct rb_node __NIL = { BLACK, 0, NULL, NULL, NULL, NULL };
static const struct rb_node *NIL = &__NIL;
#define nil	(struct rb_node*)NIL

#define ALLOC_TREE	(struct redblack_tree*)malloc(sizeof(struct redblack_tree))
#define ALLOC_NODE	(struct rb_node*)malloc(sizeof(struct rb_node))
#define OK		1
#define FAIL		0

/* functions */

int
init_tree(struct redblack_tree **t)
{
	*t = ALLOC_TREE;
	if (!*t)
		return FAIL;
	(**t).size = 0;
	(**t).root = nil;
	printf("NIL: %p\n", NIL);
	return OK;
}

void
tree_insert(struct redblack_tree *T, int key)
{
	struct rb_node *z = ALLOC_NODE; 
	struct rb_node *y = nil;
	struct rb_node *x = T->root;

	z->key = key;
	
	while (x != NIL) {
		y = x;
		x = (z->key < x->key) ? x->left	: x->right;
	}

	z->parent = y;

	if (y == NIL)
		T->root = z;
	else {
		if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
	}

	z->left = nil;
	z->right = nil;
	z->color = RED;

	T->size++;

	rb_insert_fixup(T, z);
	printf("---\n");
}

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

static void
rb_insert_fixup(struct redblack_tree *T, struct rb_node *z)
{
	struct rb_node *g, *y;
	dump_node(z);
	dump_node(z->parent);
	while (z->parent->color == RED) {	/* parent is never null */
		g = grandparent(z);
		dump_node(g);
		if (z->parent == g->left) {
			y = g->right;	/* Uncle */
			if (y->color == RED) {
				printf("Case 1: coloring z's parent BLACK and grandparent(z)\n");
				z->parent->color = BLACK;
				y->color = BLACK;
				g->color = RED;
				z = g;
			}
			else {
				if (z == z->parent->right) {
					printf("Case 2: Setting z = p[z] and left rotating on z\n");
					z = z->parent;
					rotate_left(T, z);
					g = grandparent(z);	/* New grand parent */
				}
				printf("Case 3: Coloring p[z] BLACK, g RED and rotating on ");
				z->parent->color = BLACK;
				g->color = RED;
				rotate_right(T, g);
			}
		}
		else {	/* Same as first part with "right" and "left" exchanged */
			y = g->left;
			if (y->color == RED) {
				printf("Case 1: coloring z's parent BLACK and grandparent(z)\n");
				z->parent->color = BLACK;
				y->color = BLACK;
				g->color = RED;
				z = g;
			}
			else { 
				if (z == z->parent->left) {
					printf("Case 2: Setting z = p[z] and right rotating on z\n");
					z = z->parent;
					rotate_right(T, z);
					g = grandparent(z);
				}
				printf("Case 3: Coloring p[z] BLACK, g RED and left rotating on grandparent(z)\n");
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
	for ( ; x != NIL && x->key != key; x = (key < x->key) ? x->left : x->right)
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
	if (n == NIL)
		return;
	depth++;
	traverse_i(n->left);
	printf("%d ", n->key);
	traverse_i(n->right);
	depth--;
}

static int indent = 4;
#define BLANK	" "

static void
dotty(struct rb_node *n, FILE *fp)
{
	/* Declare node */
	fprintf(fp, "%*sn%d [label=\"%d\",color=%s,fontcolor=white,style=filled, shape=circle, width=0.5, fixedsize=true,fontname=Palatino];\n",
		indent, BLANK, n->key, n->key, (n->color == BLACK) ? "black" : "red");

	if (n->left != NIL) {
		dotty(n->left, fp);
		fprintf(fp, "%*sn%d -- n%d;\n", indent, BLANK, n->key, n->left->key);
	}

	if (n->right != NIL) {
		dotty(n->right, fp);
		fprintf(fp, "%*sn%d -- n%d;\n", indent, BLANK, n->key, n->right->key);
	}
}

/* Write a dot graph of the tree to file */
void
dot(struct redblack_tree *tree, const char *name, const char *file, const char *mode)
{
	FILE *fp;
	
	if (tree->root == NIL)	/* No tree - don't write anything! */
		return;

	printf("Writing tree to file '%s'\n", file);
	fp = fopen(file, (mode) ? "a" : mode);
	if (!fp)
		return;
	
	fprintf(fp, "graph %s {\n", name);
	dotty(tree->root, fp);
	fprintf(fp, "}\n");

	if (fclose(fp))
		printf("Error closing file %s\n (%d)", file, errno);
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
	if (n == NIL) 
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
	if (x->right != NIL)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == NIL)
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

	if (y->left != NIL)
		y->left->parent = x;
	
	y->parent = x->parent;

	if (x->parent == NIL)
		t->root = y;
	else
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	
	y->left = x;
	x->parent = y;
}

static inline struct rb_node *
grandparent(struct rb_node *n)
{
	if (n != NIL && n->parent != NIL)
		return n->parent->parent;
	else
		return nil;
}

/*
 * TODO: Case where z has two children does not work properly.
 * Question: When y is set to successor(z), how come that y is returned?
 *		Shouldn't it be z (or a copy of z) that's returned?
 
        5
         \
	  8   <-- we will delete '8'
	 / \
	7   9

  z = 8
  y = successor(8) = 9 		# because 8 has two children...
  x = left[y] OR right[y]	# both are null (9 has no children)
  				# - non-NIL child of y (NIL if y has no children)

  but what happens to 7?


 */
struct rb_node *
tree_delete(struct redblack_tree *T, struct rb_node *z)
{
	struct rb_node *y, *x;
	fprintf(stderr, "Deleting %d ", z->key); dump_node(z);

	/* Three cases - no children, one child or two children */

	y = (z->left == NIL || z->right == NIL)
		? z
		: successor(z);

	print_nil_or_not("y", y);

	x = (y->left != NIL)	/* x should be the sibling of y */
		? y->left
		: y->right;
	
	print_nil_or_not("x", x);

	/* case: x is null... */

	x->parent = y->parent;
	
	if (y->parent == NIL)
		T->root = x;
	else {
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	
	if (y != z) { /* true <=> z has two children */
		z->key = y->key;
		/* Copy y's satellite data into z */
	}
	
	if (y->color == BLACK)
		rb_delete_fixup(T, x);

	T->size--;
	printf("Removed: "); dump_node(y);
	return y;
}

/*
 * TODO: Write code that tests this...
 *
     9
    / \
   7   10	x = NIL w/parent pointing to 10

		- x is a left child
		w = right NIL of 10

		NIL is NOT red
 */
static void
rb_delete_fixup(struct redblack_tree *T, struct rb_node *x)
{
	printf("rb_delete_fixup: x = %d\n", x->key );

	struct rb_node *w;
	while (x != T->root && x->color == BLACK) {
		/* x is a left child */
		if (x == x->parent->left) {
			w = x->parent->right;
			printf("w = "); dump_node(w);
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotate_left(T, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rotate_right(T, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rotate_left(T, x->parent);
				x = T->root;
			}
		}
		else {	/* Same as above, but "right" and "left" exchanged */		
			w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotate_right(T, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					rotate_left(T, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
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
	if (t->root != NIL)
		return f(t->root);
	return nil;
}

struct rb_node *
successor(struct rb_node *x)
{
	if (x->right != NIL)
		return min(x->right);
	struct rb_node *y = x->parent;
	while (y != NIL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

struct rb_node *
predecessor(struct rb_node *x)
{
	if (x->left != NIL)
		return max(x->left);
	struct rb_node *y = x->parent;
	while (y != NIL && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

static inline struct rb_node *
min(struct rb_node *x)
{
	for (; x->left != NIL; x = x->left)
		;
	return x;
}

static inline struct rb_node *
max(struct rb_node *x)
{
	for (; x->right != NIL; x = x->right)
		;
	return x;
}

static void
print_nil_or_not(char *name, struct rb_node *obj)
{
	if (obj != NIL)
		fprintf(stderr, "%s is %d\n", name, obj->key);
	else
		fprintf(stderr, "%s is NIL\n", name);
}
