/*
	Name:		Bhogaraju Shanmukha Sri Krishna
	Roll No:	112201013
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
	if (s->data == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}
	else {
		printf("A stack of size %d created successfully.\n", s->size);
	}
}

/* Task 1.	Flexi Stack
	-	Write the push and pop functions for a normal stack, test it and
		get it evaluated (2 points)
	-	A flexi stack is a stack whose size changes automatically depending
		on the amount of data that is stored inside it.
	-	Modify the push function to dynamically double the size of the array
		data when one tries to push a character onto a full stack. (1 point)
	-	Modify the pop function to dynamically half the size of the array
		data when only less that half the size is in use. However the array
		size should never fall below MIN_SIZE, which is 16. (1 point)
	-	Hint. User realloc function in stdlib (man realloc)
	-	1 point for proper comments and indentation
	-	Do not change the function interfaces of push and pop
*/

int push(Stack* s, char c) {
/*  Inputs
		1.	Pointer to a stack data structure s
		2.	A character c to be pushed to the stack
	Actions
		1.	If s is not full then pushes c to s
		2.	If s is full, then doubles its size and then pushes	c to s.
			-	Print a message indicating the new size of stack
	Exit behaviour:
		- On success: returns 0
		- On error: Prints an appropriate error message to stderr and returns -1
*/
	// Task 1a (push) Solution	

	if(s->top >= s->size){ // contents of stack exceeded the size of array(stack)
		// fprintf(stderr, "Stack Overflow.\n"); // Will not be needed because we are doubling the size of stack
		// return -1;
		s->size = s->size * 2;
		s->data = (char*) realloc(s->data, sizeof(char) * s->size);	// Doubled the size of the stack when overflown
		// printf("Dynamically doubled the size of array\n");
	}
	else{
		s->data[s->top++] = c; // general case for push
		return 0;
	}
	// return 0;
}

char pop(Stack *s) {
/*  Inputs
		1.	Pointer to a stack data structure s
	Actions
		1.	If s is not empty, then removes the top element from the stack and
			returns it. 
			-	If the number of elements in the stack is smaller than half the
				size of the stack and if the current size is at least twice
				MIN_SIZE, then reduce the size of the stack to half.
			-	Print a message indicating the new size of stack
		1.	If s is empty print the message "Stack Empty\n" to stderr and 
			return '$'
	Exit Behaviour
		- On success: returns the character on top of stack
		- On error: Message to stderr and returns '$'
*/
	// Task 1b (pop) Solutions
	
	if(s->top <= 0){ // checking if popping from empty stack
		fprintf(stderr, "Error, popping from empty stack.\n");
		return '$';
	}
	if(s->top < s->size / 2 && s->size >= MIN_SIZE * 2){ // conditions given in the question
		s->size = s->size / 2; // halving the size of stack
		s->data = (char*) realloc(s->data, sizeof(char) * s->size);
		// printf("Dynamically halved the size of array\n");
	}
	return s->data[--s->top]; // base case for pop
}
	
/* Task 2.	Checking balanced parentheses with two types of parentheses.
	-	Write a function which will take a string of normal and square opening
		and closing parentheses - i.e. '(', ')', '[', and ']' - and check
		whether every '(' has a matching ')' and vice-versa and whether every
		'[' has a matching ']' and vice versa.
	-	Hint. Use a stack - Push the openings. Pop and match the closings.
	-	2 points if complete if for a single type of parentheses
	-	2 points for both types
	-	1 point for comments and indentation
	-	Do not change the function interface
*/
int is_balanced(char *test) {
/*
	Input 
		-	A string (an array of characters terminated by the null character)
	Action 
		- 	Return 1 if the string is balanced, 0 otherwise
*/

//")("
//a, b, +, *, {, }, etc.
//"((("
// Task 2 Solution
	Stack s;
	init(&s);

	char* temp = test;
	while(*temp != '\0'){
		
		if(*temp == '[' || *temp == '(') // pushing the openings
			push(&s, *temp);

		else {
			char var = pop(&s); // popping the closings
			if(*temp == ')' && var != '(')
				return 0; // unbalanced
		
			else if(*temp == ']' && var != '[')
				return 0; // unbalanced
		}
		temp++; // iterating through string
	}
	return 1;
}


/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	Stack s;
	int i, flag;
	char c;

	init(&s);

	
	// Testing push
	printf("\nTesting Push\n");
	printf("============\n");
	for(i = 0; i < 26; i++) {
		flag = push(&s, 'a'+i);
		if(flag == -1)
			break;
		printf("Pushed %c\n", 'a'+i);
	}

	// Testing pop
	printf("\nTesting Pop\n");
	printf("===========\n");
	for(i = 0;; i++) {
		c = pop(&s);
		if (c == '$') {
			printf("Stack Empty\n");
			break;
		}
		printf("Popped %c\n", c);
	}

	
	// Testing balanced parentheses
	printf("\nTesting Balanced Parentheses\n");
	printf("=========================\n");

	#define NUM_TESTS 6
	char* strings[NUM_TESTS] = {
		"(())(()())",			// good
		"[[]][[][]]",			// good
		"([])[()[]]",			// good
		"([])[()[])",			// bad
		"[[()[]]]([()])",		// good
		"[[]]([][]]",			// good
	};
	
	for(i =0; i < NUM_TESTS; i++) {
		char* test = strings[i];
		if(is_balanced(test))
			printf("%s is balanced.\n", test);
		else
			printf("%s is not balanced.\n", test);
	}
	
	
	return 0;
}


