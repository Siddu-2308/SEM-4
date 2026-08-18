/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		04 | Set ADT on Sorted Link List Data Structure
	Task Set 2:	Set ADT using Sorted Link List Data Structures

	Aim: 		Implement a set ADT over sorted linked list with the functions to
				a)	create an empty set (= empty list = null pointer)
				b)	add an element to a set
				c)	remove an element to a set
				d)	create a new set as the union of two given sets
				e)	create a new set as the intersection of two given sets
				f)	create a new set as the set difference of two given sets
				g)	create a new set as the symmetric difference of two given sets
				
	Assume:		All data to be stored are integers
*/

#include <limits.h>	// For INT_MAX
#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc
#include "sorted-ll.h"

typedef sortedLL set;		// A set is a sorted LL under the hood 

void print_set(set* S) {
/*
	Input:	A set
	Actions:
		Prints the numbers in the set in the format {2, 3, 5}
*/
	printf("{");
	while(S != NULL) {
		printf("%d", S->data);
		if(S->next != NULL)
			printf(", ");
		S = S->next;
	}
	printf("}\n");
	return;
}

set* empty_set() {
	return NULL;
}

void free_set(set *S) {
	delete_list(S);
}

/* Task 3. 
	Implement a function to add a new item to a set
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error response have to be as in the comments below.
*/
set* add(int item, set* S) {
/*
	Inputs:
		1. 	An integer
		2.	A set
	Actions:
		1.	Using the find() function of the sorted LL, check if the item is already
			in the list.
		2.	If the item is already in the set, then nothing is changed and the
			original set pointer is returned.
		3.	If the item is not in the list, it is added to the list (using the
			insert() funciton of the sorted LL. The head of the new list is
			returned. (The head will be different from the input list only if
			the added item is the new smallest item)
*/
	// Task 3 Solution
	int pos = find(item, S);
	if(pos == -1){
		S = insert(item, S);
	}


	return S;
}

/* Task 4. 
	Implement a function to remove an item from a set
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error response have to be as in the comments below.
*/
set* rem(int item, set* S) { // the name remove is already used by a funciton in stdio.h
/*
	Inputs:
		1. 	An integer
		2.	A set
	Actions:
		1.	Using the find() function of the sorted LL, check if the item is already
			in the list.
		2.	If the item is already in the set, then remove it using the delete()
			function of the sorted LL.
		3.	If the item is not in the list do nothing and return the original
			set pointer is returned.
*/
	// Task 4 Solution
	int pos = find(item, S);
	if(pos != -1){
		S = delete(item, S);
	}

	return S;
}

/* Task 5. 
	Implement a function to take two sets and return a new set which is the
	union of the two given sets
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error response have to be as in the comments below.
*/
set* uni(set* S, set* T) { // the name union is a reserved keyword
/*
	Inputs:
		1. 	Two sets S and T
	Actions:
		2.	Create an empty set U and carefully add the items from S and T to U
			ensuring that
			a)	U is in sorted order
			b)	U does not contain any duplicate item
			c)	The total operation takes only O(n) time. 
				This means you create U in order (without needing any insert 
				in the middle)
*/
	set *U = empty_set();
	// Task 5 Solution
	set* currS = S;
	set* currT = T;
	while(currS != NULL && currT != NULL){
		if(currS->data < currT->data){
			U = insert(currS->data, U);
			currS = currS->next;
		}
		else if(currS->data > currT->data){
			U = insert(currT->data, U);
			currT = currT->next;
		}
		else{
			U = insert(currS->data, U);
			currS = currS->next;
			currT = currT->next;
		}
	}

	if(currS == NULL){
		while(currT != NULL){
			U = insert(currT->data, U);
			currT = currT->next;
		}
	}

	else if(currT == NULL){
		while(currS != NULL){
			U = insert(currS->data, U);
			currS = currS->next;
		}
	}

	return U;
}

/* Task 6. 
	Implement a function to take two sets and return a new set which is the
	intersection of the two given sets
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error response have to be as in the comments below.
*/
set* inter(set* S, set* T) { // the name int is a reserved keyword
/*
	Inputs:
		1. 	Two sets S and T
	Actions:
		2.	Create an empty set U and carefully add the common items from S and
			T to U ensuring that
			a)	U is in sorted order
			b)	U does not contain any duplicate item
			c)	The total operation takes only O(n) time. 
				This means you create U in order (without needing any insert 
				in the middle)
*/
	set *U = empty_set();
	// Task 6 Solution
	set* currS = S;
	set* currT = T;
	while(currS != NULL && currT != NULL){
		if(currS->data < currT->data){
			// U = insert(currS->data, U);
			currS = currS->next;
		}
		else if(currS->data > currT->data){
			// U = insert(currT->data, U);
			currT = currT->next;
		}
		else{
			U = insert(currS->data, U);
			currS = currS->next;
			currT = currT->next;
		}
	}


	return U;
}

/* Task 7. 
	Implement a function to take two sets S and T and return a new set which
	is the S - T (all elements in S but not in T)
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error response have to be as in the comments below.
*/
set* diff(set* S, set* T) { 
/*
	Inputs:
		1. 	Two sets S and T
	Actions:
		2.	Create an empty set U and carefully add the common items from S and
			T to U ensuring that
			a)	U is in sorted order
			b)	U does not contain any duplicate item
			c)	The total operation takes only O(n) time. 
				This means you create U in order (without needing any insert 
				in the middle)
*/
	set *U = empty_set();
	// Task  7 Solution
	set* currS = S;
	set* currT = T;
	while(currS != NULL && currT != NULL){
		if(currS->data < currT->data){
			U = insert(currS->data, U);
			currS = currS->next;
		}
		else if(currS->data > currT->data){
			// U = insert(currT->data, U);
			currT = currT->next;
		}
		else{
			// U = insert(currS->data, U);
			currS = currS->next;
			currT = currT->next;
		}
	}


	if(currT == NULL){
		while(currS != NULL){
			U = insert(currS->data, U);
			currS = currS->next;
		}
	}


	return U;
}

/* Task 8 
	Implement a function to take two sets S and T and return a new set which
	is the S XOR T (all elements in exactly one of the two) 
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error response have to be as in the comments below.
*/
set* symdiff(set* S, set* T) { 
/*
	Inputs:
		1. 	Two sets S and T
	Actions:
		2.	Create an empty set U and carefully add the common items from S and
			T to U ensuring that
			a)	U is in sorted order
			b)	U does not contain any duplicate item
			c)	The total operation takes only O(n) time. 
				This means you create U in order (without needing any insert 
				in the middle)
*/
	set *U = empty_set();
	// Task  8 Solution
	set* currS = S;
	set* currT = T;
	while(currS != NULL && currT != NULL){
		if(currS->data < currT->data){
			U = insert(currS->data, U);
			currS = currS->next;
		}
		else if(currS->data > currT->data){
			U = insert(currT->data, U);
			currT = currT->next;
		}
		else{
			// U = insert(currS->data, U);
			currS = currS->next;
			currT = currT->next;
		}
	}

	if(currS == NULL){
		while(currT != NULL){
			U = insert(currT->data, U);
			currT = currT->next;
		}
	}

	else if(currT == NULL){
		while(currS != NULL){
			U = insert(currS->data, U);
			currS = currS->next;
		}
	}


	return U;
}


void test_four_set_operations(set *S, set *T) {
/*
	Helper function to test union, intersection, difference and symmetric difference
	of the two given sets.
*/
	printf("S \t\t = ");
	print_set(S);
	printf("T \t\t = ");
	print_set(T);

	set *U;

	// Uncomment after completing Task 5 
	
	U = uni(S,T);
	printf("uni(S,T) \t = ");
	print_set(U);
	free_set(U);
	
	
	// Uncomment after completing Task 6
	
	U = inter(S,T);
	printf("inter(S,T) \t = ");
	print_set(U);
	free_set(U);
	

	// Uncomment after completing Task 7
	
	U = diff(S,T);
	printf("diff(S,T) \t = ");
	print_set(U);
	free_set(U);
	

	// Uncomment after completing Task 8
	
	U = symdiff(S,T);
	printf("symdiff(S,T) \t = ");
	print_set(U);
	free_set(U);
	

	printf("--------------------------\n");
}


/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	int i, item;
	set *S, *T, *U;

	// Test for Inital Setup
	printf("Creating an empty set ...\n");
	printf("-----------------------------\n\n");
	S = empty_set();
	print_set(S);

	// Test for Task 3
	printf("Testing Task 3 : add()\n");
	printf("-----------------------------\n\n");
	for(i = 5; i < 10; i++) {
		printf("Adding %d ...\n", i);
		S = add(i, S);
		print_set(S);
	}	
	for(i = 0; i < 7; i++) {
		printf("Adding %d ...\n", i);
		S = add(i, S);
		print_set(S);
	}	
	printf("============================\n\n");

	// Test for Task 4: delete()
	printf("Testing Task 4: rem()\n");
	printf("-----------------------------\n\n");
	print_set(S);
	for(i = 0; i < 13; i += 3) {
		printf("Removing %d ...\n", i);
		S = rem(i, S);
		print_set(S);
	}

	free_set(S);
	printf("============================\n\n");

	printf("Testing Tasks 5 to 8 in four different scenarios \n");
	printf("------------------------------------------------\n\n");


	// Scenario 1 : Both S and T are empty sets 
	S = empty_set();
	T = empty_set();
	test_four_set_operations(S, T);

	// Scenario 2 : S empty
	S = empty_set();
	T = empty_set();
	for (i = 0; i < 6; i++) 
		T = add(i, T);
	test_four_set_operations(S, T);

	// Scenario 3 : T empty
	free_set(T);
	T = empty_set();
	for (i = 9; i > 3; i--) 
		S = add(i, S);
	test_four_set_operations(S, T);

	// Scenario 4 : Both non-empty
	for (i = 0; i < 6; i++) 
		T = add(i, T);
	test_four_set_operations(S, T);

	return 0;
}
