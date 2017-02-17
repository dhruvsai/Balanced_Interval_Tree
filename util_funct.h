//Function to search_node in the tree
#include <bits/stdc++.h>
using namespace std;
#define RED_COLOR		1
#define BLACK_COLOR 	2

// Structure to represent an Inter
struct Interval{
    int lower_bound, higher_bound;
};

//Structure to represent Inter Tree Node
struct node {
	Interval Inter;
	int max;
	
	struct node *left, *right, *p;
	int color;
};


struct node NIL;
struct node * NILPTR = &NIL;

struct node * search_node(struct node * root, Interval i) {
	if (root == NILPTR || (root->Inter.lower_bound == i.lower_bound && root->Inter.higher_bound == i.higher_bound))
		return root;
	if (i.lower_bound < root->Inter.lower_bound)
		return search_node(root->left, i);
	else
		return search_node(root->right, i);
}

struct node * min(struct node * root) {
	while (root->left != NILPTR)
		root = root->left;
	return root;
}

struct node * max(struct node * root) {
	while (root->right != NILPTR)
		root = root->right;
	return root;
}


void rotate_left(struct node * *treeroot, struct node * x) {
	struct node * y = x->right;
	x->right = y->left;
	if (y->left != NILPTR)
		y->left->p = x;
	y->p = x->p;
	if (x->p == NILPTR)
		*treeroot = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
	
	x->max = max(x->left->max , max(x->right->max , x->Inter.higher_bound));
    y->max = max(x->max , max(y->right->max , y->Inter.higher_bound));
}

void rotate_right(struct node * *treeroot, struct node * y) {
	struct node * x = y->left;
	y->left = x->right;
	if (x->right != NILPTR)
		x->right->p = y;
	x->p = y->p;
	if (y->p == NILPTR)
		*treeroot = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
	
	y->max = max(y->left->max , max(y->right->max , y->Inter.higher_bound));
  	x->max = max(x->left->max , max(y->max , x->Inter.higher_bound));
}

void red_black_insert_correction_func(struct node * *treeroot, struct node * z) {
	while (z->p->color == RED_COLOR) {
		if (z->p == z->p->p->left) {
			struct node * y = z->p->p->right;
			if (y->color == RED_COLOR) {
				z->p->color = BLACK_COLOR;
				y->color = BLACK_COLOR;
				z->p->p->color = RED_COLOR;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					rotate_left(treeroot,z);
				}
				z->p->color = BLACK_COLOR;
				z->p->p->color = RED_COLOR;
				rotate_right(treeroot,z->p->p);
			}
		}
		else {
			struct node * y = z->p->p->left;
			if (y->color == RED_COLOR) {
				z->p->color = BLACK_COLOR;
				y->color = BLACK_COLOR;
				z->p->p->color = RED_COLOR;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					rotate_right(treeroot,z);
				}
				z->p->color = BLACK_COLOR;
				z->p->p->color = RED_COLOR;
				rotate_left(treeroot,z->p->p);
			}
		}
	}
	(*treeroot)->color = BLACK_COLOR;
}

void red_black_insert(struct node * *treeroot, Interval I) {
	struct node * Z = (struct node *) malloc(sizeof(struct node));
	Z->Inter = I;
	struct node * y = NILPTR;
	struct node * x = *treeroot;
	while (x != NILPTR) {
		y = x;
		if (Z->Inter.lower_bound < x->Inter.higher_bound)
			x = x->left;
		else
			x = x->right;
	}
	Z->p = y;
	if (y == NILPTR)
		*treeroot = Z;
	else if (Z->Inter.lower_bound < y->Inter.lower_bound)
		y->left = Z;
	else
		y->right = Z;
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED_COLOR;
	
	red_black_insert_correction_func(treeroot,Z);
}

void red_black_transplant(struct node * *treeroot, struct node * u, struct node * v) {
	if (u->p == NILPTR)
		*treeroot = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

void red_black_delete_correction_func(struct node * *treeroot, struct node * x) {
	while (x != *treeroot && x->color == BLACK_COLOR) {
		if (x == x->p->left) {
			struct node * w = x->p->right;
			if (w->color == RED_COLOR) {
				w->color = BLACK_COLOR;
				x->p->color = RED_COLOR;
				rotate_left(treeroot,x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK_COLOR && w->right->color == BLACK_COLOR) {
				w->color = RED_COLOR;
				x = x->p;
			}
			else {
			 	if (w->right->color == BLACK_COLOR) {
					w->left->color = BLACK_COLOR;
					w->color = RED_COLOR;
					rotate_right(treeroot,w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK_COLOR;
				w->right->color = BLACK_COLOR;
				rotate_left(treeroot,x->p);
				x = *treeroot;
			}
		}
		else {
			struct node * w = x->p->left;
			if (w->color == RED_COLOR) {
				w->color = BLACK_COLOR;
				x->p->color = RED_COLOR;
				rotate_right(treeroot,x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK_COLOR && w->right->color == BLACK_COLOR) {
				w->color = RED_COLOR;
				x = x->p;
			}
			else {
				if (w->left->color == BLACK_COLOR) {
					w->right->color = BLACK_COLOR;
					w->color = RED_COLOR;
					rotate_left(treeroot,w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK_COLOR;
				w->left->color = BLACK_COLOR;
				rotate_right(treeroot,x->p);
				x = *treeroot;
			}
		}
	}
	x->color = BLACK_COLOR;
}

void red_black_delete(struct node * *treeroot, Interval i) {
	struct node * Z = search_node(*treeroot, i);
	if (Z == NILPTR) {
		printf("Node to be deleted not found\n");
		return;
	}
	struct node * y = Z;
	int yoc = y->color;
	struct node * x;
	if (Z->left == NILPTR) {
		x = Z->right;
		red_black_transplant(treeroot,Z,Z->right);
	}
	else if (Z->right == NILPTR) {
		x = Z->left;
		red_black_transplant(treeroot,Z,Z->left);
	}
	else {
		y = min(Z->right);
		yoc = y->color;
		x = y->right;
		if (y->p == Z)
			x->p = y;
		else {
			red_black_transplant(treeroot,y,y->right);
			y->right = Z->right;
			y->right->p = y;
		}
		red_black_transplant(treeroot,Z,y);
		y->left = Z->left;
		y->left->p = y;
		y->color = Z->color;
	}
	if (yoc == BLACK_COLOR)
		red_black_delete_correction_func(treeroot,x);
}


// A utility function to check if given two Inters overlap
bool doOverlap(Interval i1, Interval i2){
    if (i1.lower_bound <= i2.higher_bound && i2.lower_bound <= i1.higher_bound)
        return true;
    return false;
}

// The main function that search_nodees a given Inter i in a given Inter Tree.
Interval Overlap_Search_node(struct node * treeroot, Interval i){
    // Base Case, tree is empty
    if (treeroot == NULL) return {INT_MIN, INT_MIN};
 
    // If given Inter overlaps with root
    if (doOverlap(treeroot->Inter, i))
        return treeroot->Inter;
 
    // If left child of root is present and max of left child is greater than
    //  or equal to given Inter, then i may overlap with an Inter is left subtree
    if (treeroot->left != NULL && treeroot->left->max >= i.lower_bound)
        return Overlap_Search_node(treeroot->left, i);
 
    // Else Inter can only overlap with right subtree
    return Overlap_Search_node(treeroot->right, i);
}
