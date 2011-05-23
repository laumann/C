#include "redblacktree.h"

static struct rb_node *grandparent(struct rb_node*);
static struct rb_node *uncle(struct rb_node*);
static void insert_case1(struct rb_node*);
static void insert_case2(struct rb_node*);
static void insert_case3(struct rb_node*);
static void insert_case4(struct rb_node*);
static void insert_case5(struct rb_node*);
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

void
tree_insert(struct redblack_tree *tree, int data)
{
	struct rb_node *n, *p;
	redblack_tree_p = &tree;

	n = (struct rb_node*)malloc(sizeof(struct rb_node));
	n->color 	= RED;
	n->data 	= data;
	n->left_child 	= NULL;
	n->right_child 	= NULL;
	n->parent	= NULL;

	(*redblack_tree_p)->size++;

	if (!((*redblack_tree_p)->root)) {
		(*redblack_tree_p)->root = n;
		insert_case1(n);
		return;
	}

	p = tree->root;
	for (;;) {
		if (n->data < p->data) {
			if (!(p->left_child)) {
				p->left_child = n;
				n->parent = p;
				insert_case1(n);
				break;
			}
			p = p->left_child;
		}
		else {
			if (!(p->right_child)) {
				p->right_child = n;
				n->parent = p;
				insert_case1(n);
				break;
			}
			p = p->right_child;
		}
	}
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

static void
insert_case1(struct rb_node *n)
{
	if (!n->parent)
		n->color = BLACK;
	else
		insert_case2(n);
}

static void
insert_case2(struct rb_node *n)
{
	if (n->parent->color == BLACK)
		return;
	else
		insert_case3(n);
}

static void
insert_case3(struct rb_node *n)
{
	struct rb_node *u, *g;

	u = uncle(n);

	if (u && (u->color == RED)) {
		n->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insert_case1(g);
		return;
	}
	else 
		insert_case4(n);
}

static void
insert_case4(struct rb_node *n)
{
	struct rb_node *g;

	g = grandparent(n);

	if ((n == n->parent->right_child) && (n->parent == g->left_child)) {
		rotate_left(n->parent);
		n = n->left_child;
	}
	else if ((n == n->parent->left_child) && (n->parent == g->right_child)) {
		rotate_right(n->parent);
		n = n->right_child;
	}
	insert_case5(n);
}

static void
insert_case5(struct rb_node *n)
{
	struct rb_node *g;

	g = grandparent(n);
	
	n->parent->color = BLACK;
	g->color = RED;
	
	if ((n == n->parent->left_child) && (n->parent == g->left_child))
		rotate_right(g);
	else
		rotate_left(g);
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
	if (x->right_child)
		x->right_child->parent = y;
	x->parent = y->parent;
	if (!y->parent)
		(*redblack_tree_p)->root = x;
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

static struct rb_node *
uncle(struct rb_node *n)
{
	struct rb_node *g = grandparent(n);
	if (!g)
		return NULL;
	if (n->parent == g->left_child)
		return g->right_child;
	else
		return g->left_child;
}
