/*
	Name:		<full name>
	Roll No:	<roll number>
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 9
	Tasks:		1 to 4
	Aim: 		Process a postfix expression
				
*/

#include <stdio.h>
#include <limits.h>
#include "stack.h"
#include "token.h"

/* Task 1. Complete the following code to evaluate a given postfix expression. 
	where the operands are integers (multiple digits allowed) and operators
	are either ~ (unary minus), +, -, * or /

   Examples of postfix notation
		"2 31 +",					// (2+31) = 33
		"2 31~ +", 					// (2+(~31)) = ~29 
		"10 2 3 + ~ /",				// 10/(~(2+3)) = ~2
	Definition:
		a) A number is a postfix expression
		b) if p is postfix expression than "p ~" is a postfix expression 
		c) if p and q are postfix expression than "p q #" is a postfix expression 
			for # in {+, -, *, /}.
	Partial Solution.
		Since postfix evaluation was not done in class, we are including almost
		90% of the code here. You only need to complete the Step 3b in the
		description below.
*/
int postfix_eval(char *str) {
/*
	Input: 	A postfix expression
	Output: The result of evaluating the expression
	Steps:
		1.	Tokenise str to get a token array (say ta)
		2.	Declare and initialise an operand stack (say valStack) of required size
			(number of tokens in ta is one way to estimate the size)
		3.	Linearly process ta till you hit a token of type EoS
			a) 	If the current token is an operand, push the value to valStack
			b) 	If the current token is the unary negation
				-	pop valStack, 
					(break the token scan if you get INT_MIN as value)
				-	negate the popped value, and 
				-	push the result back to valStack
			b) 	If the current token is a binary operator
				-	pop valStack twice to get val2 and val1 (in that order)
					(break the token scan if you get INT_MIN as either value)
				-	compute the result = val1 operator val2 using a switch case
					on the operator, and
				-	push the result back to valStack
		4.	When the current token is EoS, the final result can be popped from
			the valStack.
		5.	If either the current token is not EoS or result is INT_MIN or 
			the valStack is not empty after the last pop, the expression was
			invalid. Print an error and return INT_MIN.

	Error repsonse:	 Print the following error messages to stderr and return INT_MIN
		1. Tokenise error:  "Error: Could not tokenise <str>. Returning <INT_MIN>.\n"
		2. Evalution error: "Error; Invalid postfix expression\n"
*/
	Token*	ta = tokenise(str);
	if(ta == NULL){
		fprintf(stderr, "Error: Could not tokenise %s. Returning %d.\n", str, INT_MIN);
		return INT_MIN;
	}

	int numVals = 0;
	int numTokens = 0;
	while(ta[numTokens++].type != EoS);
	
	iStack valStack;
	init_is(&valStack, numTokens);
	
	int val1, val2, result;

	while(ta->type != EoS){
		if(ta->type == operand){
			push_is(&valStack, ta->value);
		}
		else if(ta->type == operator){
			if (ta->op == '~') {
				val1 = pop_is(&valStack);
				if(val1 == INT_MIN) 
					break;
				result = -val1;
				push_is(&valStack, result);
			}
			else {
				val2 = pop_is(&valStack);
				val1 = pop_is(&valStack);
				if(val1 == INT_MIN || val2 == INT_MIN) 
					break;
				// Task 1. Solution (Switch cases for binary operators)
				switch(ta->op){
					case '+':
					result = val1 + val2;
					break;

					case '-':
					result = val1 - val2;
					break;

					case '*':
					result = val1 * val2;
					break;

					case '/':
					result = val1 / val2;
					break;
				}

				push_is(&valStack, result);
			}
		}
		ta++;
	}
	result = pop_is(&valStack);

	// These are all error cases
	if(	ta->type != EoS || result == INT_MIN || !isempty_is(&valStack)) {
		fprintf(stderr, "Error in postfix_eval: Invalid postfix expression\n");
		result = INT_MIN;
	}

	free_is(&valStack);
	return result;
}

/* Task 2. Generate an expression tree from a given postfix expression */
eTree* postfix_to_etree(char *str) {
/*
	Input: 	A postfix expression
	Output: Pointer to the root of the equivalent expression tree.
	Steps:
		1.	Tokenise str to get a token array (say ta)
		2.	Declare and initialise a Node Stack (say nodeStack)
			(num of operand tokens in ta is one way to estimate the size)
		3.	Linearly process ta till you hit a token of type EoS
			a) 	If the current token is an operand
				-	Create a new operand node with 
					- 	current token as node token
					- 	NULL as left and NULL as right pointers
					-	push this node to nodeStack
			b) 	If the current token is the unary negation
				-	pop nodeStack once to get a single node t, 
					(break the token scan if you get NULL in this pop)
				-	Create a new operator node with 
					~ 	current token as the node token
					-	the popped node  t as its right child
					-	NULL as its left child
				-	push this new node to nodeStack 
			b) 	If the current token is a binary operator
				-	pop nodeStack twice to get two nodes n2 and n1 (in that order)
					(break the token scan if you get NULL in either pop)
				-	Create a new operator node token with 
					~ 	current token as the node token
					-	the popped node  n1 as its left child
					-	the popped token  n2 as its right child
				-	push this new node to ns
		4.	When the current token is EoS, nodeStack contains only the root node
			of the expression tree
		5.	If either the current token is not EoS or result is INT_MIN or 
			the valStack is not empty after the last pop, the expression was
			invalid. Print an error and return INT_MIN.

	Error response:	 Print the following error messages to stderr and return NULL
		1. Tokenise error:  "Error: Could not tokenise <str>. Returning <INT_MIN>.\n"
		2. Evaluation error: "Error; Invalid postfix expression\n"
*/

	Token*	ta = tokenise(str);
	if(ta == NULL){
		fprintf(stderr, "Error: Could not tokenise %s. Returning %d.\n", str, INT_MIN);
		return NULL;
	}

	int numVals = 0, i = 0;
	while(ta[i].type != EoS){
		if(ta[i].type == operand){
			numVals++;
		}
		i++;
	}
		
	pStack nodeStack;
	init_ps(&nodeStack, numVals);
	
	eTree *node1, *node2; 

	// Task 2. Solution

	while(ta->type != EoS){
		if(ta->type == operand){
			eTree* new = create_node(*ta, NULL, NULL);
			push_ps(&nodeStack, new);
		}

		else if(ta->type == operator){
			if(ta->op == '~'){
				node1 = pop_ps(&nodeStack);
				if(node1 == NULL)
					break;
			eTree* new = create_node(*ta, NULL, node1);
			push_ps(&nodeStack, new); 
			}

			else{
				node2 = pop_ps(&nodeStack);
				node1 = pop_ps(&nodeStack);
				if(node1 == NULL || node2 == NULL)
					break;
				eTree* new = create_node(*ta, node1, node2);
				push_ps(&nodeStack, new);
			}
		}
		ta++;
	}
	eTree* temp = pop_ps(&nodeStack);
	if(	ta->type != EoS || !isempty_ps(&nodeStack)) {
		fprintf(stderr, "Error in postfix_to_etree: Invalid postfix expression\n");
		return NULL;
	}

	
	free_ps(&nodeStack);

	return temp;  // You may want to edit this
}

/* Task 3. Genrate a fully parenthesised infix expression from a given expression tree
*/

void etree_to_infix(eTree *t) {
/* 	Input:	The root of an expression tree
	Action: Print the fully parenthesised infix expression of this tree
			Single operands should not be in parenthesis
*/
	if (t == NULL)
		return;
		
	// Task 3. Solution
	if(t->token.type == operand){
		// printf("(");
		printf("%d", t->token.value);
		// printf(")");
	}
	else if(t->token.type == operator){
		printf("(");
		etree_to_infix(t->left);
		printf(" %c ", t->token.op);
		etree_to_infix(t->right);
		printf(")");
	}



}

/* Task 4. Evaluate a given expression tree 
*/
int etree_eval(eTree *t) {
/* 	Input:	The root of an expression tree
	Action: Evaluate the expression tree recursively and return the answer
*/
	if (t == NULL) {
		fprintf(stderr, "Error in etree_eval: Trying to evaluate an empty tree\n");
		return INT_MIN;
	}

	// Task 4. Solution
	if(t->token.type == operator && t->token.op != '~'){
		int t1 = etree_eval(t->left);
		int t2 = etree_eval(t->right);
		switch(t->token.op){
			case '+':
				return t1 + t2;
			case '-':
				return t1 - t2;
			case '*':
				return t1 * t2;
			case '/':
				return t1 / t2;
		}
	}
	else if(t->token.type == operator && t->token.op == '~'){
		return -(etree_eval(t->right));
	}
	else if(t->token.type == operand){
		return t->token.value;
	}
	
}


/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	Token *ta;

	// Testing the tokeniser
	printf("\nTesting tokenise()\n");
	printf("====================\n");

	int nTests = 3;
	char str[][100] = {
		"+-()",
		"(1 + 2145) - [35*5 ]",
		"1 / ~21 +"
	};
	
	for(int i = 0; i < nTests; i++) {
		printf("\nTokenizing %s\n", str[i]);
		ta = tokenise(str[i]);
		if(ta == NULL)
			printf("Error in tokenizing.\n");
		else
			print_tokens(ta);
	}

	// Testing postfix_eval()
	printf("\nTesting Tasks 1 to 3.\n");
	printf("=======================\n");

	nTests = 10;
	char post[][100] = {
		"2 31 +",					// (2+31) = 33
		"2 31~ +", 					// (2+(~31)) = ~29 
		"10 2 3 + ~ /",				// 10/(~(2+3)) = ~2
		"2 3 1 * + 9 -", 			// ((2+(3*1))-9) = -4
		"2 3 - 4 + 5 6 7 * + *", 	// (((2-3)+4)*(5+(6*7))) = 141
		"2 3 - 4 + 5 6 7 * + * /", 	// Invalid
		"1 2 3 - 4 + 5 6 7 * + *", 	// Invalid
		"(1 + 2)",					// Invalid
		"1 + 2",					// Invalid
		"+ 1 2"						// Invalid 
	};

	int result;
	eTree *root;
	for(int i = 0; i < nTests; i++) {
		char* s = post[i];
		// Task 1 Test
		printf("\n%d. Processing \"%s\"\n", i+1, s);
		printf("-----------------------------\n");
		result = postfix_eval(s);
		printf("Task 1. Evaluate postfix expression: Result = %d\n", result);
		// Task 2 Test
		root = postfix_to_etree(s);
		if(root == NULL){
			printf("Task 2. Invalid postfix expression\n");
		}
		else {
			printf("Task 2. Expression Tree\n");
			print_etree(root);
		}
		// Task 3 Test
		printf("Task 3. Fully parenthesised infix expression: ");
		etree_to_infix(root);
		printf("\n");

		// Task 4 Test
		result = etree_eval(root);
		printf("Task 4. Evaluate expression tree: Result =%d\n", result );
	}

	return 0;
}


