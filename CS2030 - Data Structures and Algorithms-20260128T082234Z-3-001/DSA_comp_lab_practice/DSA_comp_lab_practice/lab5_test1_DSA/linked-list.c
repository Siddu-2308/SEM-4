/*
	Name:		Bhogaraju Shanmukha Sri Krishna
	Roll No:	112201013
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Test 1 | 15/Feb/2024
	Tasks:		3, 4, 5 (5 points each)
	
	Aim: 		1. Implement a singly linked list and some basic funcitons
				2. Implement selection sort of a singly linked list
	Assume:		All data to be stored are of type int
*/

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
	else {
		new->data = data;
		new->next = next;
		return new;
	}
}

void print_list(sLL *start) {
/*
	Input:	A list
	Actions:
		Prints the data in the linked list from start to end
		in the format:  D0 - D1 - ... - Dn - NULL
*/
	if(start == NULL){
		printf("NULL\n");
		return;
	}
	else {
		printf("%d - ", start->data);
		print_list(start->next);		// Recursion
	}
}

//	A good programmer frees any memory that she doesn't need
void delete_list(sLL* list) {
/*
	Inputs
		1. A list
	Actions
		1. Frees the memory location for all the nodes in this list
			
*/
	while(list != NULL) {
		delete_list(list->next);		// Recursion
		free(list); 
	}
}

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
	sLL* new = create_node(data, list);
	if(new == NULL) {
		fprintf(stderr, "Error: Insertion at start failed\n");
		return NULL;
		}
	else
		return new;
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
	else {
		sLL* newList = list->next;
		free(list);
		return newList;
	}
}


/* Task 3. 
	Implement a function to delete a single node at a specified position in the
	given list and stitch the list back together.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error Responses have to be as in the comments below.
*/
sLL* delete_at_pos(sLL* list, int pos) {
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
		1.	Prints an error message 
			"Error: Attempt to delete a node outside the list." 
			to stderr and returns NULL if one tries to delete a node outside
			the index-range of the list.
*/
// Task 3 Solution
	if(pos == 0)
		return delete_first(list);
	else{
		sLL* curr = list;
		for(int i=1; i<pos; i++){
			curr = curr->next;
			if(curr == NULL){
				fprintf(stderr, "Error: Attempt to delete a node outside the list.\n");
				return list;
			}
		}
		// free(curr->next);
		if(curr->next != NULL){
			curr->next = curr->next->next;
			return list;
		}
		else{
			fprintf(stderr, "Error: Attempt to delete a node outside the list.\n");
			return list;
		}
	}
	
}

/*	A struct to hold the position and data of a node in an sLL */
typedef struct nodeInfo{
	int pos;	// The position of a node in a list
	int data;	// The data in that node
} nodeInfo;

/* Task 4. 
	Implement a function to find the node with a minimum value in a linked
	list. The function should return a structure of type nodeInfo (not a
	pointer to it) defined above.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error Responses have to be as in the comments below.
*/
int find(sLL* list, int data){
	int pos = 0;
	if(data == list->data){
		return pos;
	}
	else{
		sLL* curr = list;
		while(data != curr->data){
			curr = curr->next;
			if(curr == NULL){
				return -1;
			}
			pos++;
		}
		return pos;
	}
}

nodeInfo find_min(sLL* list) {
/*
	Inputs
		A list.
	Action
		Returns the nodeInfo of the node with a minimum value in the list
		-	If the minimum value occurs at multiple places, then return the
			nodeInfo for the first position containing the minimum.
	Error Response:
		-	Returns nodInfo node with pos = -1 if the list is empty
*/
// Task 4. Solution
	nodeInfo minNode;
	if(list == NULL){
		minNode.pos = -1;
		minNode.data = 0;
		return minNode;
	}

	sLL* curr = list;
	int min = list->data;
	// int pos = 0;
	minNode.pos = 0;
	while(curr != NULL){
		if(curr->data < min){
			min = curr->data;
		}
		curr = curr->next;
	}
	// minNode.pos = pos;
	minNode.data = min;
	minNode.pos = find(list, min);
	
	return minNode;
}

/* Task 5. 
	Implement a selection sort algorithm to sort a singly linked list.
	-	Use only find_min(), delete_from_pos() and insert_at_start()
	-	Do not change the function interface given below.
	-	Inputs and Actions have to be as in the comments below.
*/

sLL* selection_sort(sLL* list) {
/*
	Inputs
		A list.
	Action
		-	Sorts the list in a non-decreasing order using only find_min(),
			delete_from_pos() and insert_at_start()
		-	Return a pointer to the start of the sorted list.
*/
// Task 5. Solution
	
	if(list == NULL){
		return list;
	}
	else{
		nodeInfo node = find_min(list);
		list = selection_sort(delete_at_pos(list, node.pos));
		list = insert_at_start(node.data, list);
		return list;
	}
	

	// sLL* curr = list;
	// nodeInfo node = find_min(list);
	// while(curr != NULL){
	// 	list = insert_at_start(node.data, delete_at_pos(list, node.pos));
	// 	curr = curr->next;
	// 	node = find_min(curr);
	// 	// printf("%d", node.data);
	// }

	// return list;
}


/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	int i;
	#define TEST_SIZE 12
	int test[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9}; // Fun task: Guess the pattern.
	sLL *list = NULL, *tempList = NULL;
	nodeInfo node;

	printf("\nPopulating the test list \n");
	printf("========================\n");
	for(i = 0; i < TEST_SIZE; i++) {
		list = insert_at_start(test[i], list);
		print_list(list);
	}	

	
	// Test for Task 3: delete_at_pos()
	printf("\nTesting Task 3: delete_at_pos()\n");
	printf("================================\n");
	for(i = 0; i < TEST_SIZE; i+=2) {
		printf("Deleting from position %d.\n", i);
		list = delete_at_pos(list, i);
		print_list(list);
	}	
	
	// Test for Task 4: find_min()

	// Repopulate the list
	list = NULL;
	printf("\nRepopulating the test list \n");
	for(i = 0; i < TEST_SIZE; i++) {
		list = insert_at_start(test[i], list);
	}	
	print_list(list);

	printf("\nTesting Task 4: find_min()\n");
	printf("==============================\n");
	while (1) {
		print_list(list);
		node	= find_min(list);
		if(node.pos == -1) {
			printf("List is empty.\n");
			break;
		}
		printf("Minimum value %d is at position %d.\n", node.data, node.pos);
		printf("Deleting %d at position %d.\n", node.data, node.pos);
		list = delete_at_pos(list, node.pos);
	}
	
	// Test for Task 5: selection_sort()
	// Repopulate the list
	free(list);
	printf("\nRepopulating the test list \n");
	for(i = 0; i < TEST_SIZE; i++) {
		list = insert_at_start(test[i], list);
	}	
	print_list(list);

	printf("\nTesting Task 5: selection_sort()\n");
	printf("==========================\n");
	
	list = selection_sort(list);
	print_list(list);

	

	free(list);
	return 0;
}
