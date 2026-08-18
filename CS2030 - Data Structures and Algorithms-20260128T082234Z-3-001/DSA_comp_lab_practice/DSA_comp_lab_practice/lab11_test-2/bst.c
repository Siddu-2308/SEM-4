/*
	Name:		Bhogaraju Shanmukha Sri Krishna
	Roll No:	112201013
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Test 2 | 28/Mar/2024
	Tasks:		3 and 4 (5 points each)
	Aim: 		Implement a insert, and successor operations in a BST
	Definition:	A Binary Search Tree (BST) is a binary tree such that the value
				(key) at every node is more than that of the largest key in
				it's left subtree (if it exists) and less than that of the
				smallest key it's right subtree (if it exists).  Check the
				function is_bst()
	Assume:		All keys to be stored are integers.
				No two keys are the same.
	Inst:		Do not change any function interface
*/

#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc
#include <time.h>	// To seed random number generator
#include <limits.h>	// For INT_MIN

/* 	The structure to store the key and pointers for a single node.
	The same structure also can be treated as the definition of a binary tree
	-	A null pointer is a binary tree (empty tree)
	-	A node with a key and two pointers to two binary trees is a binary tree.
*/
typedef struct Tree {
    int key;
    struct Tree* left;
    struct Tree* right;
} Tree;		

/* Helper Functions */

Tree* create_node(int key, Tree* left, Tree* right) {
/*
	Inputs:
		1. 	Key for the new node to be inserted
		2.	A pointer to be set as the left child
		3.	A pointer to be set as the right child
	Actions:
		1.	Memory required for a new node is allotted.
		2.	The data and the child pointers of the new node are set from the inputs
	Error Response:
		1.	Prints "Error: Memory allocation for new node failed." to stderr if
			malloc fails.	
		2.	Returns NULL if the new node cannot be created
*/
	Tree* new = (Tree *) malloc(sizeof(Tree));
	if(new == NULL) {
		fprintf(stderr, "Error: Memory allocation for new node failed\n");
		return NULL;
		}
	new->key 	= key;
	new->left 	= left;
	new->right 	= right;

	return new;
}

/* Helper function to help good programmers to free the memory allotted for a tree
*/
void free_tree(Tree* t) {
	if (t == NULL)
		return;
	else {
		free_tree(t->left);
		free_tree(t->right);
		free(t);
		return;
	}
}

/* Helper function used by print_tree to get the height of a node
*/
int height(Tree *tree) {
	if (tree == NULL)
		return 0;
	else {
		int hl 	= height(tree->left);
		int hr 	= height(tree->right);
		int hmax = (hl > hr) ? hl : hr;
		return hmax + 1;
	}
}

/* Helper function used by print_tree to print the nodes at a particular level
*/
void print_level(Tree* t, int t_level, int p_level, int height) {
/*
	Inputs:
		1.	Top level node t
		2.	Height of the top level node (t) in the whole binary tree
		3.	Level of the binary tree to be printed
		4.	Height of the whole binary tree
*/
	if(t_level > p_level) {
		fprintf(stderr, "Error in print_level\n");
		return;
		}
	if(t_level < p_level) {
		if (t != NULL)
			print_level(t->left, t_level+1, p_level, height);
		else
			print_level(NULL, t_level+1, p_level, height);

		if (t != NULL)
			print_level(t->right, t_level+1, p_level, height);
		else
			print_level(NULL, t_level+1, p_level, height);
		return;
	}

	// t_level == p_level
	int padding = 1;	// for alignment
	for (int i = p_level; i < height-1; i++)
		padding = padding * 2 + 1;

	// To prefix some space and a line 
	for (int i = 0; i < (padding+1)/2; i++)
		printf("  ");
	for (int i = (padding+1)/2; i < padding; i++)
		printf("__");

	if (t != NULL)
		printf("%2d", t->key);	
	else
		printf("()");	

	// To suffix a line and some space
	for (int i = (padding+1)/2; i < padding; i++)
		printf("__");
	for (int i = 0; i < (padding+1)/2; i++)
		printf("  ");

	printf("  ");
	return;
}

/* Helper function to print a tree in nice format
*/
void print_tree(Tree* t) {
	int h = height(t);
	for(int l = 0; l < h; l++) {
		print_level(t, 0, l, h);
		printf("\n");
		}
	return;
}

/* Helper function used by is_bst
*/
int find_min(Tree* tree){
/*
	Input:  A BST 
	Output: Minimum key in the BST if it is non-empty.
			INT_MAX if the BST is empty.
*/
	if (tree == NULL)
		return INT_MAX;

	while(tree->left != NULL)
		tree = tree->left;

	return tree->key;
}

/* Helper function used by is_bst
*/
int find_max(Tree* tree){
/*
	Input:  A BST 
	Output: Maximum key in the BST if it is non-empty.
			INT_MIN if the BST is empty.
*/
	if (tree == NULL)
		return INT_MIN;

	while(tree->right != NULL)
		tree = tree->right;

	return tree->key;
}

/* Helper function to check if a binary tree is a BST
*/
int is_bst(Tree* t) {
	if (t == NULL)
		return 1;
	if (
		is_bst(t->left) 
		&& is_bst(t->right)
		&& (find_max(t->left) < t->key) 
		&& (find_min(t->right) > t->key)
	)
		return 1;
	return 0;
}

/* Task 3. Insert
	Implement a function to create a new node with the given key and add it to
	a BST such that the resulting binary tree also satisfies the BST property.
	No change is to be made if the given key is already in the BST.
*/
Tree* insert(int key, Tree* tree) {
/*
	Inputs:
		1. 	Key for the new node to be inserted
		2.	A BST 
	Actions:
		1.	If the key is present in the tree, do nothing.
		2.	Else create a node with the received key and insert it at the correct
			position in tree.
		2.	The pointer to the root of the tree is returned (this will change
			only if the insert happens at the root).
	Error Response:
		1.	Prints "Error: Insertion failed." to stderr
		2.	Returns NULL if the actions fail
*/
	// Task 3 Solution
	if(tree == NULL)
		return create_node(key, NULL, NULL);
		
	else if(key < tree->key)
		tree->left = insert(key, tree->left);

	else if(key > tree->key)
		tree->right = insert(key, tree->right);

	
	return tree; // You may have to edit this
}

Tree* search(int key, Tree* tree){
	if(tree == NULL)
		return tree;

	if(key < tree->key){
		return search(key, tree->left);
	}

	else if(key > tree->key){
		return search(key, tree->right);
	}
	else{
		return tree;
	}
}

/* Task 4. Find Successor 
	Implement a function to search for the successor of a given key in a BST
	Successor of a key k is the smallest key in that is larger than k itself.
*/
Tree* succ(int key, Tree* tree) {
/*
	Inputs: A search key and a BST 
	Output:
		1. 	If every node in the tree has a value smaller or equal to key,
			return NULL
		2.	Otherwise, return a pointer to the node which contains the smallest
			value which is larger than the key.
*/
	// Task 4 Solution
	if(find_max(tree) <= key)
		return NULL;
	

	// if(key < tree->key){
	// 	Tree* ptr = tree;
	// 	while(key < ptr->key && ptr->left != NULL){
	// 		if(ptr->left->key < key)
	// 			break;
	// 		ptr = ptr->left;
	// 	}
	// 	return ptr;
	// }
	// else if(key > tree->key){
	// 	Tree* ptr = tree;
	// 	while(key > ptr->key && ptr->right != NULL){
	// 		if(ptr->right->key > key)

	// 			break;
	// 		ptr = ptr->right;
	// 	}
	// 	return ptr;
	// }
	// else{
	// 	Tree* curr = tree;
	// 	if(curr->right != NULL){
	// 		Tree* ptr = curr;
	// 		while(ptr->left != NULL)
	// 			ptr = ptr->left;
	// 		return ptr;
	// 	}
	// 	else{
	// 		return tree;
	// 	}
			
	// }
	for(int i = key; i<=find_max(tree); i++){
		if(search(i, tree) != NULL){
			if(i != key)
				return search(i, tree);
			else
				continue;
		}
	}

}

/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	Tree *t = NULL;
	int key; 
	int nNodes = 10;

	//Test Task 3. Insert
	printf("\nTesting Task 3. Insert\n");
	printf("========================\n\n");

	printf("Inserting 10 two-digit random numbers to an empty tree.\n");
	srand(time(0));		// Seed the random number generator
	t = NULL;

	for (int i = 0; i < nNodes; i++) {
		key = 10 + rand() % 90;
		printf("Inserting %d\n", key);
		t = insert(key, t);
		print_tree(t);
	}

	print_tree(t);
	if(is_bst(t))
		printf("Satisfies BST property\n");

	// Test Task 4. Find Successor
	printf("\nTesting Task 4. Find Successor\n");
	printf("================================\n");

	key = 0;
	Tree* s;
	for (int i = 0; i <= nNodes; i++) {
		s = succ(key, t);
		if (s == NULL){
			printf("There is no one to succeed %d\n", key);
		}
		else {
			// printf("123\n");
			key = s->key;
			printf("%d, ", key);
		}
	}
	printf("\n\n");

	free_tree(t);
	
	return 0;
}


