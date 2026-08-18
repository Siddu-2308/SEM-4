/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		04 | Set ADT on Sorted Linked Lists
	Task Set:	01 | Test for Sorted Linked Lists
*/

#include <limits.h>	// For INT_MAX
#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc
#include "sorted-ll.h"



/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	unsigned int i;
	sortedLL *list = NULL, *tempList = NULL;
	
	// Test for Task 1: insert()
	printf("Testing Task 1: insert()\n");
	printf("-----------------------------\n\n");
	for(i = 5; i < 10; i++) {
		list = insert(i, list);
		print_list(list);
	}	
	for(i = 0; i < 7; i++) {
		list = insert(i, list);
		print_list(list);
	}	
	printf("============================\n\n");

	
	// Test for Task 2: delete()
	printf("Testing Task 2: delete()\n");
	printf("-----------------------------\n\n");
	print_list(list);
	for(i = 0; i < 13; i += 3) {
		printf("Deleting data (%d)\n", i);
		list = delete(i, list);
		print_list(list);
	}
	printf("============================\n\n");

	// Test for find() (Last Week Task 4)
	printf("Testing Last Week's Task 4: find()\n");
	printf("-----------------------------\n\n");
	print_list(list);
	for(i = 0; i < 14; i+=2)
		printf("Position of %d is %d\n", i, find(i, list)); 
	printf("============================\n\n");

	delete_list(list);
	
	return 0;
}
