/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		03 | Linked Lists
	Task Set:	01 | Singly Linked Lists (sLL)

	Aim: 		Implement a singly linked lists with some basic functions.
	Assume:		All data to be stored are integers
*/

#include <limits.h>	// For INT_MAX
#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc

/*	The singly linked list data structure "sLL" defined in recursive style
	-	A null pointer is a linked list (called the empty list)
	-	A node with data and a pointer to another linked list is a linked list.
*/
typedef struct sLL{
	int 		data;	// The data stored in the node
	struct sLL*	next;	// Pointer to next linked list
} sLL;

sLL* create_node(int data, sLL* next) {
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
	sLL* new = (sLL *) malloc(sizeof(sLL));
	if(new == NULL) {
		fprintf(stderr, "Error: Memory allocation for new node failed\n");
		return NULL;
		}
	new->data = data;
	new->next = next;
	return new;
}

/* Task 1. 
	Implement a function to create a new node with the given data and add it to
	the beginning of the given list and return a pointer to the start of the
	bigger list.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error response have to be as in the comments below.
*/
sLL* insert_at_start(int data, sLL* list) {
/*
	Inputs:
		1. 	Data for the new node to be inserted
		2.	A list
	Actions:
		1.	A new node with the received data is inserted at the head of the
			received list
		2.	The pointer to this new node (which is effectively the new head of
			the list) is returned.
	Error Response:
		1.	Prints "Error: Insertion at start failed." to stderr
		2.	Returns NULL if the new node cannot be created
*/
// Task 1 - Edit one line below to solve Task 1
	sLL* new = create_node(data, list);
	if(new == NULL) {
		fprintf(stderr, "Error: Insertion at start failed\n");
		return NULL;
		}
	else
		return new;
}


/* Task 2. 
	Implement a function to create a new node with the given data and add it to
	the specified position in the given list and return a pointer to the start
	of the bigger list.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error Responses have to be as in the comments below.
	-	Instead of directly using create_node() use insert_at_start() to insert
		the new node at the appropriate position.
*/
sLL* insert_at_pos(int data, sLL* list, unsigned int pos) {
/*
	Inputs:
		1. Data for the new node to be inserted
		2. A list
		3. The position in the list where to insert the new node (0 = start) 
	Actions:
		1.	If position is within range, a new node with the given data is
			inserted to the list at the specified position. 
		2.	The head of the new list is returned. (The head will be different
			from the input list only if the insertion is at the start)
	Error Responses:
		1	If the position is larger than the current length of the list, an
			error message "Error: Position out of range." is printed and a NULL
			pointer is returned.
		2	Returns NULL pointer also if the new node could not be created
*/
// Task 2 Solution
	if(pos == 0){
		list = create_node(data, list);
	}

	else{
		sLL* curr = list;
		int num = pos - 1;
		while(curr != NULL && num){
			curr = curr->next;
			num--;
		}
		if(!num){
			curr->next = create_node(data, curr->next);
		}
		else if(curr == NULL){
			fprintf(stderr, "Error: Position out of range.\n");
			return NULL;
		}
	}

	return list;
}

void print_list(sLL *start) {
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

int get_from_start(sLL* list) {
/*
	Inputs:
		1. A list
	Actions:
		1. Returns the data stored in the first node.
	Error Response:
		1.	Prints an error message "Error: Attempt to ready from empty list."
			to stderr and returns INT_MAX if the list is empty.
*/
	if(list == NULL) {
		fprintf(stderr, "Error: Attempt to ready from empty list.\n");
		return INT_MAX;
		}
	else
		return list->data;
}

/* Task 3. 
	Implement a function to get the data from a node at a given position in a
	given list.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error Responses have to be as in the comments below.
*/
int get_from_pos(sLL* list, unsigned int pos) {
/*
	Inputs
		1. 	A list 
		2. 	Position from which to read the data
	Action
		1.	Returns the data stored in the node at the given position (start = 0).
	Error Responses:
		1.	Prints an error message "Error: Attempt to read outside of the
			list." to stderr and returns INT_MAX if one tries to read from
			outside the index-range of the list
*/
// Task 3 Solution

	if(pos == 0)
		return list->data;

	int num = pos;
	sLL* curr = list;
	while(curr && num){
		curr = curr->next;
		num--;
	}
	if(!curr){
		fprintf(stderr, "Error: Attempt to read outside of the list.\n");
		return INT_MAX;
	}

	else if(!num)
		return curr->data;
	
	

}

/* Task 4. 
	Implement a function to search for a particular data in the given list and
	return the position of the first node in the list which contains that data.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error Responses have to be as in the comments below.
*/
int find(int data, sLL* list) {
/*
	Inputs
		1. 	The data to search for
		2. 	A list.
	Action
		1. 	Returns the position of the first node with the given data.
		2.	Returns -1 if the given data is not in the list
	Error Response:
*/
// Task 4. Solution
	sLL* curr = list;
	int pos = 0;
	while(curr && curr->data != data){
		curr = curr->next;
		pos++;
	}
	
	
	if(!curr){
		fprintf(stderr, "Error: Data not found in the list.\n");
		return -1;
	}

	else if(curr->data = data)
		return pos;

	

}

void delete_list(sLL* list) {
/*
	Inputs
		1. A list
	Actions
		1. Frees the memory location for all the nodes in this list
			
*/
	while(list != NULL) {
		delete_list(list->next);
		free(list); 
	}
}

sLL* delete_first(sLL* list) {
/*
	Inputs
		1. 	A list
	Actions
		1. 	Frees the memory allotted for the start node
		3.	Returns the start pointer to the rest of the list.
	Error Responses:
		1.	Prints an error message "Error: Attempt to delete from and empty
			list." to stderr and returns NULL if the input list is empty.
*/
	if(list == NULL) {
		fprintf(stderr, "Error: Attempt to delete from and empty list.\n");
		return NULL;
	}
	sLL* newList = list->next;
	free(list);
	return newList;
}

/* Task 5. 
	Implement a function to delete a single node from the given list at the
	given position and stitch the list back together.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error Responses have to be as in the comments below.
*/
sLL* delete_at_pos(sLL* list, unsigned int pos) {
/*
	Inputs
		1. 	A list
		2. 	The position of the node to be deleted
	Actions
		1. 	Frees the memory allotted for the node at the specified position
		2.	Links the next pointer of the previous node to 	the next node.
		3.	Returns the start pointer of the list (this may change if the
			first node is deleted)
	Error Responses:
		1.	Prints an error message "Error: Attempt to delete outside of the
			list." to stderr and returns NULL if one tries to delete a node
			outside the index-range of the list.
*/
// Task 5 Solution
	if(pos == 0){
		list = delete_first(list);
		return list;
	}

	sLL* curr = list;
	int num = pos - 1;

	while(curr->next && num){
		curr = curr->next;
		num--;
	}

	if(!curr->next){
		fprintf(stderr, "Error: Attempt to delete outside of the list\n");
		return NULL;
	}

	else if(!num){
		sLL* temp = curr->next;
		curr->next = curr->next->next;
		free(temp);
	}

	return list;

}


/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	unsigned int i;
	sLL *list = NULL, *tempList = NULL;

	// Test for Task 1: insert_at_start()
	printf("Testing Task 1: insert_at_start()\n");
	for(i = 0; i < 10; i++) {
		list = insert_at_start(i, list);
		print_list(list);
	}	
	printf("============================\n");


	// Test for Task 2: insert_at_pos()
	
	printf("Testing Task 2: insert_at_pos()\n");
	for(i = 0; i < 10; i++) {
		list = insert_at_pos(i, list, i);
		print_list(list);
	}
	// Testing insert outside of the range
	tempList = insert_at_pos(22, list, 22);
	if(tempList == NULL) {
		printf("NULL pointer returned.\n");
	}
	printf("============================\n");
	


	// Test for Task 3: get_from_pos()
	
	printf("Testing Task 3: get_from_pos()\n");
	print_list(list);
	for(i = 0; i < 25; i += 4)
		printf("Data at pos %d is %d\n", i, get_from_pos(list, i));
	printf("============================\n");
	

	// Test for Task 4: find()
	
	printf("Testing Task 4: find()\n");
	print_list(list);
	for(i = 0; i < 16; i+=3)
		printf("Position of %d is %d\n", i, find(i, list)); 
	printf("============================\n");
	

	// Test for Task 5: delete_at_pos()
	
	printf("Testing Task 5: delete_at_pos()\n\n");
	print_list(list);
	for(i = 0; i < 20; i += 5) {
		printf("Deleting data (%d) at pos %d\n", get_from_pos(list, i), i);
		list = delete_at_pos(list, i);
		print_list(list);
	}
	// Testing delete outside of the range
	tempList = delete_at_pos(list, i);
	if(tempList == NULL) {
		printf("NULL pointer returned.\n");
	}
	printf("============================\n");
	

	free(list);
	return 0;
}
