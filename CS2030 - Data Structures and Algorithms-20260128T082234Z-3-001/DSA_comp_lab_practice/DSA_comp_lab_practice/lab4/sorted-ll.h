/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Use: 		header file for sorted-ll.c
*/

// A protection to ensure that a header file is not included multiple times.

#ifndef SortedLL_H
#define SortedLL_H

/*	"sortedLL" defined in recursive style
	-	A null pointer is a linked list (called the empty list)
	-	A node with data and a pointer to another linked list is a linked list.
*/
typedef struct sortedLL{
	int 				data;	// The data stored in the node
	struct sortedLL*	next;	// Pointer to next linked list
} sortedLL;

sortedLL* create_node(int data, sortedLL* next); 
/*
	Inputs:
		1. 	Data for the new node to be inserted
		2.	A pointer to be set as the next pointer of the new node
	Actions:
		1.	Memory required for a new node is allotted.
		2.	The data and the next pointer of the new node are set from the inputs
	Error Response:
		1.	Prints "Error: Memory allocation for new node failed." to stderr if
			malloc fails.	
		2.	Returns NULL if the new node cannot be created
*/

sortedLL* insert(int data, sortedLL* list);
/*
	Inputs:
		1. 	Data for the new node to be inserted
		2.	A list
	Actions:
		1.	A new node is created with the received data is inserted to the
			list at a position such that the resulting list remains sorted.
		2.	The head of the new list is returned. (The head will be different
			from the input list only if the insertion happens at the start)
	Error Response:
		1.	Prints "Error: Insertion at start failed." to stderr
		2.	Returns NULL if the new node cannot be created
*/

sortedLL* delete(int data, sortedLL* list);
/*
	Inputs
		1. 	The data to delete
		2. 	A list
	Actions
		1.	Searches for the first occurence of data in the list
		2.	If found deletes it from the list, frees its memory and the 
			returns the starting pointer to the modified list. This pointer
			will be different from list only if the first node gets deleted.
		3.	If not found, it prints an error message and returns list
	Error Responses:
		1.	Prints an error message "Error: Attempt to delete an entry not in
			the list." to stderr.
*/

int find(int data, sortedLL* list);
/*
	Inputs
		1. 	The data to search for
		2. 	A list.
	Action
		1. 	Returns the position of the first node with the given data.
		2.	Returns -1 if the given data is not in the list
	Error Response:
*/

void print_list(sortedLL *start);
/*
	Input:	A list
	Actions:
		Prints the data in the linked list from start to end
		in the format:  D0 - D1 - ... - Dn - NULL
*/

void delete_list(sortedLL* list);
/*
	Inputs
		1. A list
	Actions
		1. Frees the memory location for all the nodes in this list
			
*/

#endif
