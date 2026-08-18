/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		03 | Linked Lists
	Task Set:	2 | Doubly Linked Lists (dLL)

	Aim: 		Implement a doubly linked list with some basic functions.
	Assume:		All data to be stored are integers
*/

#include <limits.h>	// For INT_MAX
#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc

/* 	Unlike a singly linked list, it is not easy to define a doubly linked
	list in a recursive style. So we need two stucts - 
		(a) One struct for node, which holds the data and two pointers - 
			one to the next node and one to the previous node.
		(b)	One struct for the list itself - which contains two pointers -
			one to the fist node in the list and one to the last.
	When implementing a dLL the following two additional functionalities
	(one transparent one opaque) are needed to make a dLL useful.
		(a) insert_at_pos(), get_from_pos(), and delete_at_pos() functions
			should accept negative integers also as position argument. 
			-1 : last node (tail), -2 is previous to -1 and so on.
		(b) if the given position is negative, the list should be traversed
			backwards from the tail. This speeds up data access in the 
			second half of large lists 
*/
typedef struct node{
	int 			data;	// The data stored in the node
	struct node*	prev;	// Pointer to previous node
	struct node*	next;	// Pointer to next node
} node;

typedef struct dLL{
	struct node*	head;	// Pointer to first node in the list
	struct node*	tail;	// Pointer to last node in the list
} dLL;

node* create_node(int data, node *next, node *prev) {
/*
	Inputs:
		1. 	Data for the new node to be inserted
		2.	A node pointer to be set as the next pointer of the new node
		2.	A node pointer to be set as the prev pointer of the new node
	Actions:
		1.	Memory required for a new node is allotted.
		2.	The data and the two pointers of the new node are set from the inputs
	Error Response:
		1.	Prints "Error: Memory allocation for new node failed." to stderr if
			malloc fails.	
		2.	Returns NULL if the new node cannot be created
*/
	node* new = (node *) malloc(sizeof(node));
	if(new == NULL) {
		fprintf(stderr, "Error: Memory allocation for new node failed\n");
		return NULL;
		}
	new->data = data;
	new->next = next;
	new->prev = prev;
	return new;
}

dLL* create_dLL(node *head, node *tail) {
/*
	Inputs:
		2.	A pointer to the head of the list (NULL is allowed)
		2.	A pointer to the tail of the list (NULL is allowed)
	Actions:
		1. 	A new dLL struct with the given head and tail is returned
*/
	dLL* list = (dLL *) malloc(sizeof(dLL));
	if(list == NULL) {
		fprintf(stderr, "Error: Memory allocation for dLL failed\n");
		return NULL;
		}
	list->head = head;
	list->tail = tail;
	return list;
}


/* Task 6. 
	Copy all the functions (including main) that you have in simple-linked-list.c
	here and edit all the COMMENTS to reflect the changes needed.
*/

/* Task 7. 
	Edit the code inside of each function to implement the functionality on doubly
	linked lists. You can assume that position indices will still be non-negative.
	Hence you need to do forward traversal for this Task. (Negative indices and
	reverse traversals is the next Task.
*/

/* 
	Task 8. Allow negative indices and implement reverse traversal for them.
	(a) insert_at_pos(), get_from_pos(), and delete_at_pos() functions
		should accept negative integers also as position argument. 
		-1 : last node (tail), -2 is previous to -1 and so on.
	(b) if the given position is negative, the list should be traversed
		backwards from the tail. This speeds up data access in the 
		second half of large lists 
	(c) Modify the Testing loops for these functions in main to test for
		negative indices also.
*/

/* 	This main() only contains stuff to test the data structures
	Replace this with the main from simple-linked-list.c
*/
int main() {

	node 	*new = create_node(10, NULL, NULL);
	dLL	 	*list = create_dLL(new, new);

	printf("%d\n", new->data);
	printf("%d\n", list->head->data);
	printf("%d\n", list->tail->data);

	return 0;
}
