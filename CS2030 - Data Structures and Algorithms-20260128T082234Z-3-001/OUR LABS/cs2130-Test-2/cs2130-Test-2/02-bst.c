/*
	Course:		CS2130 DSA Lab 
	Semester:	2026 Jan-Apr
	Lab No:		Test 2
	File: 		2
	Aim: 		Implement a binary search tree data structure and the insert, delete, search and
				minimum functions for it.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 4000

struct node;
typedef struct node
{
	int data;
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
	int max, hl, hr;
	if(x == NULL)
		return -1;
	hl = height(x->left);
	hr = height(x->right);
	max = (hl <= hr) ? hr : hl;
	return max + 1;
}

void printTree(BSTree *T)
{
	Node *a[MAXNODES], *b[MAXNODES];
	int len, arrempty, fieldsize;
	fieldsize = 1 << (height(T->root) + 2);
	if(fieldsize <= 0 || fieldsize > 200)
	{
		printf("\nTree too high to print.\n");
		return;
	}
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
			for(k = 0; k < (fieldsize >> 1) - 1; k++)
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
			for(k = 0; k < (fieldsize >> 1) - 1; k++)
			{
				printf(" ");
			}
		}
		len = len << 1;
		fieldsize = fieldsize >> 1;
		if(fieldsize <= 0 || len <= 0)
		{
			printf("\nTree too high to print.\n");
			return;
		}
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

Node *minimum(Node *x)
{
	/* Task 3a (1 mark): This function should return a pointer to the node that will be visited first by an
	inorder	traversal of the subtree rooted at x. You can assume that x is not NULL. */

	return NULL;
}

Node *search(Node *x, int key)
{
	/* Task 3b (1 mark): If there exists a node having the value key in its data field in the subtree rooted
	at the node x, then this function should return the pointer to such a node. If no such node exists, the
	function should return NULL. */

	return NULL;
}

void insert(BSTree *T, Node *x)
{
	/* Task 3c (2 marks): This function inserts the node x in the correct position in the binary search tree
	T (based on the value in x->data). You can assume that x->left, x->right, and x->p are all equal to NULL. */

}

void transplant(BSTree *T, Node *u, Node *v)
{
	/* Helper function which implements the transplant operation on a BST. Note
	 * that the fields of the node v->p are not modified by this procedure. */

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

void delete(BSTree *T, Node *x)
{
	/* Task 4 (4 marks): This function should delete the node x from the binary search tree T.
	You can assume that x is not equal to NULL. Do not call free(x). */

}

int main()
{
	BSTree T;
	Node *n;
	int i;
	init(&T);
	printf("\nBinary search tree (for integers in the range 1-99).\n\n");
	printf("Task 1a (2 marks)\n-----------------\nEnter some values to be inserted into the tree (terminate with 0):");

	while(1)
	{
		Node *n;
		printf("Enter key value to insert: ");
		scanf("%d", &i);
		if(i == 0)
			break;
		n = (Node *) malloc(sizeof(Node));
		n->left = NULL;
		n->right = NULL;
		n->data = i;
		n->p = NULL;
		printf("\nInserting node with key value %d...", n->data);
		insert(&T, n);
	}

	printTree(&T);

	printf("\nTask 1b + 1c (1 + 1 marks):\n-------------------------\n");
	while(1)
	{
		Node *n;
		printf("\nEnter a key value to search for: ");
		scanf("%d", &i);
		if(i == 0)
			break;
		n = search(T.root, i);
		if(n != NULL)
		{
			printf("\nKey %d found in tree.", i);
			printf("\nMinimum value in subtree: %d", minimum(n)->data);
		}
		else
		{
			printf("\nKey %d not found in tree.", i);
		}
	}
	printf("\n\nTask 2 (4 marks):\n-----------------\n");
	while(1)
	{
		printf("\nEnter key value to insert or delete (+x inserts x, -x removes x, zero terminates): ");
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
			n->data = i;
			n->p = NULL;
			printf("\nInserting node with key value %d...", i);
			insert(&T, n);
		}
		printTree(&T);
	}

	destroy(&T);
	return 0;
}
