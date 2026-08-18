#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 4000

struct node;
typedef struct node
{
	int data;
	int h;
	struct node *left;
	struct node *right;
	struct node *p;
} Node;

typedef struct
{
	Node *root;
} BSTree;

void init(BSTree *T)
{
	T->root = NULL;
}

int height(Node *x)
{
	if(x == NULL)
		return 0;
	else
		return x->h;
}

void printTree(BSTree *T)
{
	Node *a[MAXNODES], *b[MAXNODES];
	int len, arrempty, fieldsize;
	fieldsize = 1 << height(T->root);
	a[0] = T->root;
	arrempty = 0;
	len = 1;
	while(!arrempty)
	{
		int i, j;
		arrempty = 1;
		printf("\n\n");
		j = 0;
		for(i = 0; i < len; i++)
		{
			int k;
			for(k = 0; k < fieldsize - 1; k++)
			{
				printf(" ");
			}
			if(a[i] != NULL)
			{
				arrempty = 0;
				printf("%2d", a[i]->data);
				b[j++] = a[i]->left;
				b[j++] = a[i]->right;
			}
			else
			{
				printf("  ");
				b[j++] = NULL;
				b[j++] = NULL;
			}
			for(k = 0; k < fieldsize - 1; k++)
			{
				printf(" ");
			}
		}
		len = len << 1;
		fieldsize = fieldsize >> 1;
		for(i = 0; i < len; i++)
		{
			a[i] = b[i];
		}
	}
	printf("\n");
}

void destroyNode(Node *x)
{
	if(x == NULL)
		return;
	destroyNode(x->left);
	destroyNode(x->right);
	free(x);
}

void destroy(BSTree *T)
{
	destroyNode(T->root);
	T->root = NULL;
}

void inorder(Node *x)
{ //
	if(x == NULL)
		return;//
	inorder(x->left);
	printf("%d ", x->data);
	inorder(x->right);
}

Node *minimum(Node *x)
{
	while(x->left != NULL)
		x = x->left;
	return x;
}

Node *maximum(Node *x)
{
	while(x->right != NULL)
		x = x->right;
	return x;
}

Node *search(Node *x, int key)
{
	while(x != NULL && x->data != key)
	{
		if(key < x->data)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

void updateheight(Node *x) 
{
	/* Helper function that updates the field x->h based on height(h->left) and
	 * height(x->right) */

	int hl, hr;
	if(x == NULL)
		return;
	hl = height(x->left);
	hr = height(x->right);
	if (hl < hr)
    	x->h = hr + 1; 
	else
    	x->h = hl + 1;	
}

void transplant(BSTree *T, Node *u, Node *v) 
{
	/* Helper function which implements the transplant operation on a BST. Note
	 * that the fields of the node  v->p are not modified by this procedure. */

	if(u->p == NULL)
		T->root = v;
	else
	{
		if(u == u->p->left)
			u->p->left = v;
		else
			u->p->right = v;
	}
	if(v != NULL)
		v->p = u->p;
}

void rotateright(BSTree *T, Node *x)
{
	/* Task 1a: Implement the Rotate-Right function for an AVL tree T on node x. Assume that neither x nor x->left are NULL.*/
	Node *y=x->left;
	x->left = y->right;

    if (y->right != NULL)
        y->right->p = x;

    transplant(T, x, y);

    y->right = x;
    x->p = y;

    updateheight(x);
    updateheight(y);
}

void rotateleft(BSTree *T, Node *x)
{
	/* Task 1b: Implement the Rotate-Left function for an AVL tree T on node x. Assume that neither x nor x->right are NULL.*/
	Node *y=x->right;
	x->right=y->left;

	if(y->left!=NULL){
		y->left->p=x;
	}

	transplant(T,x,y);

	y->left=x;
	x->p=y;

	updateheight(x);
	updateheight(y);
}

void fixup(BSTree *T, Node *x)
{
	/* Task 2: Given an AVL tree T and a node x in it such that both the left
	 * and right subtrees of x satisfy the AVL property. Modify the tree (if
	 * required) so that the subtrees rooted at x as well the ancestors of x,
	 * all satisfy the AVL property.*/
	while(x != NULL)
    {
        updateheight(x);

        int bf = height(x->left) - height(x->right);

        if(bf > 1)
        {  //left case
            if(height(x->left->left) >= height(x->left->right))
            {
                rotateright(T, x);          // LL
            }
            else
            {
                rotateleft(T, x->left);     // LR step1
                rotateright(T, x);          // LR step2
            }
        }

        else if(bf < -1)
        {	//right case 
            if(height(x->right->right) >= height(x->right->left))
            {
                rotateleft(T, x);           // RR
            }
            else
            {
                rotateright(T, x->right);   // RL step1
                rotateleft(T, x);           // RL step2
            }
        }

        x = x->p;
    }
}

void insert(BSTree *T, Node *x) {
	/* Task 3: This function should insert the node x in the correct position
	 * in T and modify T so that it satisfies the AVL property. You may refer
	 * to the insert function you wrote last week. You can assume that x->left,
	 * x->right and x->p  are all equal to NULL, and that x->h is equal to 1.
	 * */
	Node *cur = T->root;
    Node *parent = NULL;

    // find position
    while(cur != NULL)
    {	//save parent
        parent = cur;
        if(x->data < cur->data)
            cur = cur->left;
        else
            cur = cur->right;
    }

    // attach node to parent
    x->p = parent;
	//attach parent to node
    if(parent == NULL)
        T->root = x;
    else if(x->data < parent->data)
        parent->left = x;
    else
        parent->right = x;

    // restore AVL property
    fixup(T, parent);

}

void delete(BSTree *T, Node *z) {
	/* Task 4: This function should deletw the node x from the AVL tree T and
	 * modify T so that it satisfies the AVL property. You may refer to the
	 * delete function you wrote last week. You can assume that x is not equal
	 * to NULL. Do not call free(x). */
	Node *y;

    if(z->left == NULL)
    {
        y = z->p;
        transplant(T, z, z->right);
    }

    else if(z->right == NULL)
    {
        y = z->p;
        transplant(T, z, z->left);
    }

    else
    {
        Node *s = minimum(z->right);

        if(s->p != z)
        {
            y = s->p;   
            transplant(T, s, s->right);
            s->right = z->right;
            s->right->p = s;
        }
        else
        {
            y = s;
        }

        transplant(T, z, s);
        s->left = z->left; 
        s->left->p = s;
    }

    fixup(T, y);
}

int main()
{
	BSTree T;
	Node *n;
	int i;
	init(&T);
	printf("\nBinary search tree (for integers in the range 1-99).\n\n");
	while(1)
	{
		printf("Enter key value to insert or delete (+x inserts x, -x removes x, zero terminates): ");
		scanf("%d", &i);
		if(i == 0)
			break;
		if(i < 0)
		{
			i = -i;
			n = search(T.root, i);
			if(n == NULL)
			{
				printf("Key %d not found in tree.\n", i);
				continue;
			}
			else
			{
				printf("\nRemoving node with key value %d...", i);
				delete(&T, n);
				free(n);
			}
		}
		else
		{
			Node *n;
			n = (Node *) malloc(sizeof(Node));
			n->left = NULL;
			n->right = NULL;
			n->p = NULL;
			n->h = 1;
			n->data = i;
			printf("\nInserting node with key value %d...", i);
			insert(&T, n);
		}
		printTree(&T);
	}
	printf("\nInorder traversal: ");
	inorder(T.root);
	printf("\n");
	destroy(&T);
	return 0;
}
