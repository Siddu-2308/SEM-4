/*
	Course:		CS2130 DSA Lab 
	Semester:	2026 Jan-Apr
	Lab No:		Test 2
	File: 		3
	Aim: 		Implement a modified binary search tree and some associated functions for it.
				Each node of this binary search tree contains an extra field called 'size' that
				should store the number of nodes in the subtree rooted at that node. */

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
    int size; //field to store number of nodes in the subtree rooted at this node
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
		return 0;
	hl = height(x->left);
	hr = height(x->right);
	max = (hl <= hr) ? hr : hl;
	return max + 1;
}

void printTree(BSTree *T, Node *x)
{
	Node *a[MAXNODES], *b[MAXNODES];
	int len, arrempty, fieldsize;
	fieldsize = 4 << (height(T->root));
	if(fieldsize <= 0 || fieldsize > 300)
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
			for(k = 0; k < (fieldsize >> 1) - 2; k++)
			{
				printf(" ");
			}
			if(a[i] != NULL)
			{
				arrempty = 0;
				printf("%2d", a[i]->data);
                if(a[i] == x)
                    printf("*");
				else
					printf("|");
				printf("%1d", a[i]->size);
				b[j++] = a[i]->left;
				b[j++] = a[i]->right;
			}
			else
			{
				printf("    ");
				b[j++] = NULL;
				b[j++] = NULL;
			}
			for(k = 0; k < (fieldsize >> 1) - 2; k++)
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
	/* Task 3a: Copy-paste from bst-1.c */

	return NULL;
}

Node *search(Node *x, int key)
{
	/* Task 3b: Copy-paste from bst-1.c */

	return NULL;
}

void insert(BSTree *T, Node *x)
{
	/* Task 5 (2 marks): This function inserts the node x in the correct position in the binary search tree T (based
	on the value in x->data). You can assume that x->left, x->right, and x->p are all equal to NULL, and
	that x->size = 1. The function should make sure that the size field in all the nodes is
	correct after this operation. */

}

void transplant(BSTree *T, Node *u, Node *v)
{
	/* Helper function which implements the transplant operation on a BST. Note
	 * that the fields of the node v->p are not modified by this procedure. Also, this function
	 * does not modify the size field of any node.*/

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
	/* Task 6 (3 marks): This function should delete the node x from the binary search tree T. You can
	assume that x is not equalto NULL. Do not call free(x). The function should make sure that the size
	field in all the nodes is correct after this operation. */

}

Node *leftmost(Node *x, int key)
{
	/* Task 7a: Return the node containing value key that will occur first in an inorder
	traversal of the tree rooted at x. This procedure should run in time O(h) where h is
	the height of the tree rooted at x. */

    return NULL;
}

Node *rightmost(Node *x, int key)
{
	/* Task 7b (7a + 7b 4 marks): Return the node containing the value 'key' that will occur
	last in an inorder traversal of the tree rooted at x. This procedure should run in time O(h)
	where h is the height of the tree rooted at x. */

	return NULL;
}

int count(Node *x, int key)
{
	/* Task 8 (5 marks): Returns the number of nodes in having their data value equal to key in
	the subtree rooted at x. You will receive only 2 marks if your algorithm runs in time Omega(n),
	where n is the number of nodes in the subtree rooted at x. You will receive full credits if your
	algorithm runs in time O(h), where h is the height of the subtree rooted at x. */

	return 0;
}

int main()
{
	BSTree T;
	Node *n;
	int i;
	init(&T);
	printf("\nBinary search tree (for integers in the range 1-99).\n\n");
	printf("\n\nTask 5 + Task 6 (2 marks + 3 marks)\n-----------------------------------\n\n");
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
                printTree(&T, n);
				printf("\nResulting Tree:\n");
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
			n->data = i;
            n->size = 1;
			printf("\nInserting node with key value %d...", i);
			insert(&T, n);
		}
		printTree(&T, NULL);
	}

	printf("\n\nTask 7 + Task 8 (4 marks + 5 marks)\n-----------------------------------\n\n");
	while(1)
	{
		printf("\nEnter a key value: ");
		scanf("%d", &i);
		if(i == 0)
			break;
		else
		{
			Node *nl, *nr;
			nl = leftmost(T.root, i);
			nr = rightmost(T.root, i);
			if(nl == NULL)
				printf("No node with key value %d in tree.\n", i);
			else
			{
				printf("Leftmost node having key value %d:\n", i);
				printTree(&T, nl);
				printf("Rightmost node having key value %d:\n", i);
				if(nr != NULL)
					printTree(&T, nr);
				printf("Number of nodes having key value %d: %d\n", i, count(T.root, i));
			}
		}
	}

	destroy(&T);
	return 0;
}
