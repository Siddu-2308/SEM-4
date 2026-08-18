/*
	Name:		Bhogaraju Shanmukha Sri Krishna
	Roll No:	112201013
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Test 2 | 28/Mar/2024
	Tasks:		5 (5 points)
	Aim: 		Implement a prefix expression evaluator
	Inst:		Do not change any function interface
				Compile with gcc token.c prefix.c
*/

#include <stdio.h>
#include <limits.h>
#include "token.h"

/* Task 5. Evaluator for Prefix Expressions
   Examples of prefix notation
		"+ 2 31",					// (2+31) = 33
		"+ 2 ~ 31", 				// (2+(~31)) = ~29 
		"/ 10 ~ + 2 3",				// 10/(~(2+3)) = ~2

	Definition:
		a) A number is a prefix expression
		b) if p is prefix expression, then "~ p" is a prefix expression 
		c) if p and q are prefix expressions, then "# p q" is a prefix expression 
			for # in {+, -, *, /}.

	Assumptions:
	- 	Operands are integers (multiple digits allowed) 
	-	Operators are either ~ (unary minus), +, -, * or /
	-	The input will always be a valid prefix expression
		(You need not worry about syntax checking)

	Hints to Evaluate:
		Recall that we used a single stack (for operands) to evaluate a postfix
		expression and two stacks (one for operands, one for operators) for an
		infix expression. To evaluate a prefix expression, you do not need a
		stack!! You can directly follow the definition above and implement
		an evaluator using recursion. 

	Pseudocode (you may or may not follow this):
		We follow the model that whenever the evaluator passed an array of tokens
		which starts with a valid prefix expression (and may contain more stuff
		after it) will evaluate the valid prefix expression and store the result
		as an operand token in the same token array. But it will store the result
		token at the place where the last token that got processed during its 
		evaluation. It will return the pointer to this token.

		a)	If the first token in the array is a number (an operand) the 
			evaluation is complete. Return the back the input pointer

		b)	If the first token in the array is the unary minus (~) recursively
			evaluate the rest of the token-array and replace the first token
			in the returned array (which will contain the result of the recursive
			evaluation) with its negative and then return that pointer.

		c)	If the first token in the array is a binary operator #, then recursively
			evaluate the rest of the token array (which will return a token array
			with the first token containing the value for the first argument of #
			followed by the remaining part of the expression. Extract this first
			argument and then recursively evaluate the rest of the token array
			to get the second argument. Now compute the result of # on these
			two arguments and replace the value of the first token in the token
			array returned by the second recursive call with this result and then
			return that pointer.
*/

Token* prefix_eval(Token *ta) {
/*
	Input: 	The token array ta of a valid prefix expression exp
	Action: Evaluates a valid prefix of expression and replaces the last parsed
			token with the result of the above evaluation.
	Output: Start of the token array from the position of above result
*/

	// Task 5 Solution

	if(ta->type == operand){
		return ta;
	}

	if(ta->type == operator && ta->op == '~'){
		Token* temp = prefix_eval(ta + 1);
		temp->value = -1 * temp->value;
		return temp;
	}

	if(ta->type == operator && ta->op != '~'){
		Token* temp1 = prefix_eval(ta + 1);
		int arg1 = temp1->value;

		Token* temp2 = prefix_eval(temp1 + 1);
		int arg2 = temp2->value;
		int result = 0;

		switch(ta->op){
			case '+':
				result = arg1 + arg2;
				break;
			
			case '-':
				result = arg1 - arg2;
				break;
			
			case '*':
				result = arg1 * arg2;
				break;
			
			case '/':
				result = arg1 / arg2;
				break;
		}
		temp2->value = result;
		return temp2;
	}

	
	// return NULL; // You may have to edit this
}


/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {

	int nTests = 7;
	char prefix_tests[][100] = {
		"100",							// 100
		"+ 2 31",						// (2+31) = 33
		"+ 2 ~ 31",						// (2+(~31)) = ~29 
		"/ 10 ~ + 2 3",					// 10/(~(2+3)) = ~2
		"- + 2 * 3 1 9",				// ((2+(3*1))-9) = -4
		"/ / / / / / 64 2 2 2 2 2 2",	// ((((((64/2)/2)/2)/2)/2)/2) = 1 
		"* * * 2 2 2 2",				// (((2*2)*2)*2)
	};

	for(int i = 0; i < nTests; i++) {
		char* str = prefix_tests[i];
		Token*	ta = tokenise(str);
		if(ta == NULL){
			fprintf(stderr, "Error: Could not tokenise %s.\n", str);
			return INT_MIN;
		}

		printf("\n%d. Evaluating the prefix expression: \"%s\"\n", i+1, str);
		int result = prefix_eval(ta)->value; 
		printf("Result = %d\n", result);
	
	}

	return 0;
}