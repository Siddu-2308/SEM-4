/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Test 1 | 15/Feb/2024
	Tasks:		1 and 2 (5 points each)
	
	Aim: 		Implement Flexi Stack ADT over the Array Data Structure
	Assume:		All data to be stored are of type char
*/

#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc

#define MIN_SIZE 16 // Minimum size of the stack

typedef struct {
	char* data;	// Pointer to the start of array. Space will be allocated by init()
	int size;	// Max size of stack
	int top;	// Index of next empty location
} Stack;

/* Initialize a stack */
void init(Stack* s) {
	s->top = 0;	// index of next empty location 
	s->size = MIN_SIZE;
	s->data = (char*) malloc(s->size * sizeof(char));
	
}


int push(Stack* s, char c) {
	if (s->top >= s->size) {
		fprintf(stderr, "Stack Overflow\n");
		return -1;
	}

	/* Task 1a.
		Fill in the statements to add c to the stack and increment top	
	*/

	s->data[s->top] = c;
	s->top++;
	
	return 0;
}

char pop(Stack *s) {
	if (s->top <= 0) {
/*		fprintf(stderr, "Stack Empty\n");*/
		return '$';
	}
	/* Task 1b.
		Fill in the missing statements 
	*/
	
	s->top--;
	return(s->data[s->top]);
}
	

