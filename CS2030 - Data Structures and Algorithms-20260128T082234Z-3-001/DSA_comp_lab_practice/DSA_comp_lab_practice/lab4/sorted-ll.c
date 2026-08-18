/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		04 | Set ADT on Sorted Link List Data Structure
	Task Set 1:	Sorted Link List Data Structures

	Aim: 		Implement a sorted linked list with some basic functions.
	Assume:		All data to be stored are integers

	Notes: 		
	The sorted linked list data structure is a singly linked list which
	always keeps its elements in a non-decreasing sorted order.
	
	Please note the following comparisons between ordinary LL and sorted LL

	1.	While an ordinary LL may have separate insert_at_start() and
		insert_at_pos() functions, a sorted LL will only have one insert()
		function, which determines the position of insert based on the data.
		The other two functions should NOT be implemented. They will spoil the
		sorted nature of the list.
		
		Implementing this insert() will be your Task 1.

	2.	While delete_at_start() and delete_at_pos() will not affect the sorted
		nature of the list, what is more useful is to have a single delete
		funciton which will search for the first occurence of a data and delete
		it from the list. 
	
		Implementing this delete() will be your Task 2.

	3.	While get_from_start() and get_from_pos() are also harmless. They do
		not serve much of a purpose and hence need not be implemented. The most
		commonly used funciton to read the list will be find().
*/

#include <limits.h>	// For INT_MAX
#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc
#include "sorted-ll.h"	// Custom header file


sortedLL* create_node(int data, sortedLL* next) {
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
	sortedLL* new = (sortedLL *) malloc(sizeof(sortedLL));
	if(new == NULL) {
		fprintf(stderr, "Error: Memory allocation for new node failed\n");
		return NULL;
		}
	new->data = data;
	new->next = next;
	return new;
}

/* Task 1. 
	Implement a function to create a new node with the given data and add 
	it to the correct position in the list based on the given data.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error response have to be as in the comments below.
*/
sortedLL* insert(int data, sortedLL* list) {
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
// Task 1 Solution
	if(!list){
		list = create_node(data, list);
		return list;
	}

	else if(list->data > data){
		list = create_node(data, list);
		return list;
	}

	sortedLL* curr = list;
	sortedLL* prev = NULL;
	while(curr != NULL && curr->data < data){
		prev = curr;
		curr = curr->next;
	}

	if(curr == NULL){
		prev->next = create_node(data, curr);
		// printf("%d\n", prev->data);
	}

	else if(curr->data >= data){
		prev->next = create_node(data, curr);
		// printf("1214\n");
	}
	
	return list; // You may want to delete this.
}

/* Task 2. 
	Implement a function to delete the first occurence of a node with the given
	data in a list (if found)
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error response have to be as in the comments below.
*/
sortedLL* delete(int data, sortedLL* list) {
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
	
	// Task 2 Solution

	if(!list){
		fprintf(stderr, "Error: List empty\n");
		return list;
	}

	else if(list->data > data){
		fprintf(stderr, "Error: Attempt to delete an entry not in the list\n");
		return list;
	}

	sortedLL* curr = list;
	
	while(curr->next != NULL && curr->next->data < data)
		curr = curr->next;

	if(!curr->next){
		fprintf(stderr, "Error: Attempt to delete an entry not in the list\n");
		return list;
	}

	else if(curr->next->data == data){
		sortedLL* temp = curr->next;
		curr->next = curr->next->next;
		free(temp);
	}

	return list; // You may want to delete this

}

int find(int data, sortedLL* list) {
/*
	Inputs
		1. 	The data to search for
		2. 	A list.
	Action
		1. 	Returns the position of the first node with the given data.
		2.	Returns -1 if the given data is not in the list
	Error Response:
*/
	unsigned int pos = 0;
	while(list != NULL) {
		if(list->data == data)
			return pos;
		pos++;
		list = list->next;
	}
	return -1;
}

void print_list(sortedLL *start) {
/*
	Input:	A list
	Actions:
		Prints the data in the linked list from start to end
		in the format:  D0 - D1 - ... - Dn - NULL
*/
	printf("%d - ", start->data);
	if(start->next == NULL){
		printf("NULL\n");
		return;
	}
	else
		print_list(start->next);
}


void delete_list(sortedLL* list) {
/*
	Inputs
		1. A list
	Actions
		1. Frees the memory location for all the nodes in this list
			
*/
	while(list != NULL) {
		delete_list(list->next);
		free(list); 
		return;
	}
	return;
}

