#include "redblacktree.h"

static struct node *grandparent(struct node*);
static struct node *uncle(struct node*);
static void insert_case1(struct node*);
static void insert_case2(struct node*);
static void insert_case3(struct node*);
static void insert_case4(struct node*);
static void insert_case5(struct node*);
static void rotate_right(struct node*);
static void rotate_left(struct node*);
static void traverse_i(struct node*);
static void paran_v(struct node*);

/* Our current tree */
static struct tree **tree_p;

void
new_tree(struct tree **t)
{
	*t = (struct tree*)malloc(sizeof(struct tree));
	(*t)->size = 0;
	(*t)->root = NULL;
}

void
tree_insert(struct tree *tree, int data)
{
	struct node *n,	*p;
	tree_p = &tree;

	n = (struct node*)malloc(sizeof(struct node));
	n->color 	= RED;
	n->data 	= data;
	n->left_child 	= NULL;
	n->right_child 	= NULL;
	n->parent	= NULL;

	(*tree_p)->size++;

	if (!((*tree_p)->root)) {
		(*tree_p)->root = n;
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
				printf("\n");
				break;
			}
			p = p->left_child;
		}
		else {
			if (!(p->right_child)) {
				p->right_child = n;
				n->parent = p;
				insert_case1(n);
				printf("\n");
				break;
			}
			p = p->right_child;
		}
	}
} 

void
in_order_traverse(struct tree *tree)
{
	printf("Root is '%d' (size: %d)\n", tree->root->data, tree->size);
	traverse_i(tree->root);
}

static void
traverse_i(struct node *n)
{
	static int depth = 0;
	if (!n)
		return;
	depth++;
	traverse_i(n->left_child);
/*	printf("[%*d%*c]\n", depth, n->data, depth, '\0');*/
	printf(" %d ", n->data);
	traverse_i(n->right_child);
	depth--;
}

void
paran_view(struct tree *tree)
{
	printf(" root=%d ", tree->root->data);	
	paran_v(tree->root);
}

static void
paran_v(struct node *n)
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
insert_case1(struct node *n)
{
	if (!n->parent)
		n->color = BLACK;
	else
		insert_case2(n);
}

static void
insert_case2(struct node *n)
{
	if (n->parent->color == BLACK)
		return;
	else
		insert_case3(n);
}

static void
insert_case3(struct node *n)
{
	struct node *u, *g;

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
insert_case4(struct node *n)
{
	struct node *g;

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
insert_case5(struct node *n)
{
	struct node *g;

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
    Q        P
   / \      / \
  P   c => a   Q
 / \          / \
a   b        b   c

 */
static void
rotate_right(struct node *Q)
{
	printf(" rr ");
	/* The given node (Q) becomes the right child of its left child (P) */
	struct node
		*P =  Q->left_child,
		*b = (Q->left_child) ? Q->left_child->right_child : NULL;

	/* Inform parent of Q of new child - or set new tree root */
	if (Q->parent) {
		if (Q == Q->parent->left_child)
			Q->parent->left_child = P;
		else
			Q->parent->right_child = P;
	}
 	else {
		(*tree_p)->root = P;
	}

	P->parent = Q->parent;
	P->right_child = Q;

	Q->parent = P;
	Q->left_child = b;
}

/*
    |        |
    Q        P
   / \      / \
  P   c <= a   Q
 / \          / \
a   b        b   c

 */
static void
rotate_left(struct node *P)
{
	printf(" rl ");
	struct node
		*Q =  P->right_child,
		*b = (P->right_child) ? P->right_child->left_child : NULL;

	if (P->parent) {
		/* Inform the parent of P that
		   it has a new left or right child */
		if (P == P->parent->left_child)
			P->parent->left_child = Q;
		else
			P->parent->right_child = Q;
	}
	else { /* P was root */
		(*tree_p)->root = Q;
	}

	Q->parent = P->parent;
	Q->left_child = P;

	P->parent = Q;
	P->right_child = b;
}

static struct node *
grandparent(struct node *n)
{
	if (n && n->parent)
		return n->parent->parent;
	else
		return NULL;
}

static struct node *
uncle(struct node *n)
{
	struct node *g = grandparent(n);
	if (!g)
		return NULL;
	if (n->parent == g->left_child)
		return g->right_child;
	else
		return g->left_child;
}
