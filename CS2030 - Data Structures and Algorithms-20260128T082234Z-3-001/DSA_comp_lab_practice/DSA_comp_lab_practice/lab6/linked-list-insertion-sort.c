/*
	Course:	CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 6 | 22/Feb/2024
	Tasks:		1,2,3
	
	Aim: 		1. Implement insertion Sort on a singly linked list
			
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



/* Task 1: Implement a function to delete the next node (if it is not NULL) of a given node. 
		It returns the value stored in the next node or -1 if the next node is NULL.
*/
int get_next(sLL* node) {
	if(node->next != NULL){
		sLL* temp = node->next;
		int key = temp->data;
		node->next = temp->next;
		// free(temp);
		return key;
	}
	
	return -1;

} 
/* Task 2: Implement a function that takes as input 
	(1) a pointer to a partially sorted linked list (intial portion of the list is sorted), 
	(2) data, and 
	(3) an index indicating the position till which the list is sorted. 
   It inserts the data in the appropriate position of the sorted initial part. 
*/
sLL* compare_and_insert(sLL* list, int data, int sorted_till){
/*
     Inputs
     		1) list- a pointer to a linked list 
			2) data - data 
			3) sorted_till - an index to the list
     		The list is sorted from 0-th index to sorted-till index
     Action
     		Create a new node with data and 
			insert the node into the list so that 
			the list is sorted till the sorted-till+1-th index. 
			Return the head pointer of the new list.
     		
*/
	sLL* curr = list;
	while(sorted_till--){
		if(data >= curr->next->data)
			curr = curr->next;
		
		else{
			// printf("%d\n", 44);
			break;
		}
	}
	curr->next = create_node(data, curr->next);
	
	return list;
	
}



/* Task 3: Implement Insertion Sort using the functions get_next() and compare_and_insert()
*/
sLL* insertion_sort(sLL* list){
/*
	Inputs
		Pointer to a list.
	Action
		-	Sorts the list in a non-decreasing order using only get_next() and compare_and_insert()
		-	Return a pointer to the start of the sorted list.
*/
// Task 3. Solution
	if(list->next == NULL)
		return list;
	
	
	int i = 1; // sorted_till

	sLL* curr = list;
	sLL* next = list->next;
	while(next != NULL){
		if(next->data >= curr->data){
			curr = curr->next;
			next = next->next;
			i++;
			continue;
		}
		// print_list(list);	
		// printf("%d\n", i);
		int key = get_next(curr);
		list = compare_and_insert(list, key, i);
		// curr = next;
		next = next->next;
		i++;
	}
	return list;
}


int main() {
	int i, next_data;
	#define TEST_SIZE 12
	//int test[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9}; // Fun task: Guess the pattern.
	//int test[] = {7, 1, 4, 1, 5, 9, 2, 6, 8, 3, 5, 9};
	int test[] = {1, 1, 1, 5, 9, 8, 3, 9, 5, 1, 1, 1}; //To be used for Task 2
	sLL *list = NULL, *temp_list = NULL;


	printf("\nPopulating the test list \n");
	printf("========================\n");
	for(i = 0; i < TEST_SIZE; i++) {
		list = insert_at_start(test[i], list);
		print_list(list);
	}
		
/*       Test   Test 1*/
	printf("\nTesting Task 1: get_next()\n");
	printf("==========================\n");
	print_list(list);
	temp_list = list;
	for(i=0; i<=5; i++){
		temp_list=temp_list->next;
	}
	next_data = get_next(temp_list);
	printf("Data of next node = %d \n", next_data);
	print_list(list);
	
	
/*       Test   Test 2*/
	printf("\nTesting Task 1: compare_and_insert()\n");
	printf("==========================\n");
	print_list(list);
	list = compare_and_insert(list,1,4);
	print_list(list);
	list = compare_and_insert(list,2,5);
	print_list(list);
	list = compare_and_insert(list,10,6);
	print_list(list);

	
	
/*       Test   Test 3*/
	printf("\nTesting Task 3: insertion_sort()\n");
	printf("==========================\n");
	list = insertion_sort(list);
	print_list(list);


	// delete_list(list);
	return 0;
}
