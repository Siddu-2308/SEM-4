#include <stdio.h>
#include <stdlib.h>

#define MAXTOKENS 1000
#define MAXEXPR 1000
#define MAXNODES 4000


typedef struct
{
    char type; //'N' - number, otherwise character of operator, '(' or ')'
    int value; //value if type is 'N', precedence of operator otherwise
} token;

struct node;
typedef struct node
{
	token data;
	struct node *left;
	struct node *right;
	struct node *p;
} Node;

typedef struct
{
	Node *root;
} BinaryTree;

void init(BinaryTree *T)
{
	T->root = NULL;
}

int height(Node *x)
{
	int max, hl, hr;
	if(x == NULL)
		return -1;
	hl = height(x->left);
	hr = height(x->right);
	max = (hl <= hr) ? hr : hl;
	return max + 1;
}

void printTree(BinaryTree *T)
{
	Node *a[MAXNODES], *b[MAXNODES];
	int len, arrempty, fieldsize;
	fieldsize = 1 << (height(T->root) + 2);
	a[0] = T->root;
	arrempty = 0;
	len = 1;
	while(!arrempty)
	{
		int i, j;
		arrempty = 1;
		printf("\n\n");
		j = 0;
		for(i = 0; i < len; i++)
		{
			int k;
			for(k = 0; k < (fieldsize >> 1) - 1; k++)
			{
				printf(" ");
			}
			if(a[i] != NULL)
			{
				arrempty = 0;
                if(a[i]->data.type == 'N')
    				printf("%2d", a[i]->data.value);
                else
                    printf("%2c", a[i]->data.type);
				b[j++] = a[i]->left;
				b[j++] = a[i]->right;
			}
			else
			{
				printf("  ");
				b[j++] = NULL;
				b[j++] = NULL;
			}
			for(k = 0; k < (fieldsize >> 1) - 1; k++)
			{
				printf(" ");
			}
		}
		len = len << 1;
		fieldsize = fieldsize >> 1;
		for(i = 0; i < len; i++)
		{
			a[i] = b[i];
		}
	}
	printf("\n");
}

void destroyNode(Node *x)
{
	if(x == NULL)
		return;
	destroyNode(x->left);
	destroyNode(x->right);
	free(x);
}

void destroy(BinaryTree *T)
{
	destroyNode(T->root);
	T->root = NULL;
}

void printTokens(token expr[], int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        printf("\n%2d. ", i);
        if(expr[i].type == 'N')
            printf("Number: %d", expr[i].value);
        else
            printf("Operator: %c, precedence: %d", expr[i].type, expr[i].value);
    }
}
int tokenize(char *str, token expr[])
{
    int i, j, val, state, sign;
    token t;
    //state: 0 - expecting number, 1 - reading number, 2 - expecting operator
    //sign: 1 - number being read is positive, -1 - number begin read is negative
    i = -1;
    j = 0;
    state = 0;
    sign = 1;
    do
    {
        i++;
        switch(state)
        {
            case 0:
                if(str[i] >= '0' && str[i] <= '9')
                {
                    state = 1;
                    val = sign * (str[i] - '0');
                }
                else if(str[i] == '-')
                {
                    if(sign == -1)
                        return -1;
                    sign = -1;
                }
                else if(str[i] == '(')
                {
                    if(sign == -1)
                    {
                        t.type = 'N';
                        t.value = -1;
                        expr[j++] = t;
                        t.type = '*';
                        t.value = 1;
                        expr[j++] = t;
                        sign = 1;
                    }
                    t.type = '(';
                    t.value = 2;
                    expr[j++] = t;
                }
                else if(str[i] != ' ')
                    return -1;
                break;
            case 1:
                if(str[i] >= '0' && str[i] <= '9')
                {
                    val = val * 10 + sign * (str[i] - '0');
                }
                else
                {
                    t.type = 'N';
                    t.value = val;
                    expr[j++] = t;
                    state = 2;
                    sign = 1;
                    i--;
//                    printf("\n%d %d %d", val, i, state);
                }
                break;
            case 2:
                switch(str[i])
                {
                    case '+':
                    case '-':
                        t.value = 0;
                        break;
                    case '*':
                    case '/':
                        t.value = 1;
                        break;
                    case ')':
                        t.value = 2;
                        break;
                    case ' ':
                    case '\0':
                        break;
                    default:
                        return -1;
                }
                if(str[i] != '\0' && str[i] != ' ')
                {
                    t.type = str[i];
                    expr[j++] = t;
                    if(str[i] != ')')
                        state = 0;
                }
                break;
        }
    }
    while(str[i] != '\0');
    return j;
}
Node *makeTree(token tk[], int start, int end)
{
  	/*Task 1: This function should constuct an expression tree corresponding to the list of tokens tk[start] .. tk[end - 1] and
    return the pointer to the node of this tree. Return NULL if list of tokens does not correspond to a valid expression. Before
    returning NULL, make sure to free the nodes allocated so far by calling destroyNode on the root nodes of any subtrees that
    have been created.*/

    /*
        1️⃣ If only one token → create number node

        2️⃣ If expression surrounded by parentheses → remove them

        3️⃣ Scan tokens to find lowest precedence operator outside parentheses

        4️⃣ Create node with that operator

        5️⃣ Recursively build
    */

        // If no tokens, expression is invalid
    if(start >= end)
        return NULL;

    // BASE CASE: If only one token exists
    // It must be a number, so create a leaf node
    if(start == end - 1)
    {
        if(tk[start].type == 'N')
        {
            Node *x = (Node*)malloc(sizeof(Node));  // allocate memory
            x->data = tk[start];                   // store token
            x->left = x->right = x->p = NULL;      // leaf node
            return x;
        }
        return NULL; // invalid expression if single token not a number
    }

    // Remove outer parentheses
    // Example: (3 + 4) -> process 3 + 4
    if(tk[start].type == '(' && tk[end-1].type == ')')
        return makeTree(tk, start+1, end-1);

    int level = 0;      // tracks parentheses depth
    int pos = -1;       // position of root operator
    int minprec = 10;   // store lowest precedence found

    // Scan tokens to find operator with lowest precedence
    for(int i = start; i < end; i++)
    {
        if(tk[i].type == '(')
            level++;        // entering parentheses
        else if(tk[i].type == ')')
            level--;        // exiting parentheses
        else if(level == 0 && tk[i].type != 'N')
        {
            // Only consider operators outside parentheses
            if(tk[i].value <= minprec)
            {
                minprec = tk[i].value;
                pos = i;    // store operator position
            }
        }
    }

    // If no operator found → invalid expression
    if(pos == -1){
        return NULL;
    }

    // Create node for the root operator
    Node *root = (Node*)malloc(sizeof(Node));
    root->data = tk[pos];

    // Recursively build left subtree
    root->left = makeTree(tk, start, pos);

    // Recursively build right subtree
    root->right = makeTree(tk, pos+1, end);

    // Set parent pointers if children exist
    if(root->left)
        root->left->p = root;

    if(root->right)
        root->right->p = root;

    return root; // return root of constructed subtree
}
void postorder(Node *x)
{
	/*Task 2: This function should print the tokens in the nodes of the subtree rooted at node x in the order in
	which the nodes will be visited by an postorder traversal of the subtree rooted at x.*/

    // If node is NULL, stop recursion
    if(x == NULL)
        return;

    // Traverse left subtree
    postorder(x->left);

    // Traverse right subtree
    postorder(x->right);

    // Print current node
    if(x->data.type == 'N')
        printf("%d ", x->data.value);  // print number
    else
        printf("%c ", x->data.type);   // print operator

}
float evaluate(Node *x)
{
	/*Task 3: This function should evaluate the expression represented by the expression tree having root x and return the value
    that the expression evaluates to. Notice that the return value is of type float even though the numbers in the input
    expression are of type int, since the expression contains the '/' operator.*/

    // If node contains a number, return its value
    if(x == NULL)
        return 0;
        
    if(x->data.type == 'N')
        return x->data.value;

    // Recursively evaluate left and right subtrees
    float left = evaluate(x->left);
    float right = evaluate(x->right);

    // Apply operator stored in current node
    switch(x->data.type)
    {
        case '+':
            return left + right;

        case '-':
            return left - right;

        case '*':
            return left * right;

        case '/':
            return left / right;
    }

    return 0;
}

int main()
{
    token tk[MAXTOKENS];
    char str[MAXEXPR];
    BinaryTree T;
    int len;
    printf("Enter expression: ");
    scanf(" %[^\n]%*c", str);
	while(str[0] != '0')
	{
    	len = tokenize(str, tk);
    	printf("\n");
    	if(len != -1)
    	{
	//      printTokens(tk, len); //Uncomment to see list of tokens
        	init(&T);
        	T.root = makeTree(tk, 0, len);
        	if(T.root == NULL)
            	printf("Expression contains unbalanced parantheses.\n");
        	else
        	{
            	printTree(&T);
            	printf("Expression in postfix notation: ");
            	postorder(T.root);
            	printf("\nExpression evaluates to: %f\n", evaluate(T.root));
            	destroy(&T);
        	}
    	}
    	else
        {	
			printf("Tokenization error: invalid expression.\n");
		}
   	 
		printf("Enter expression (Start with 0 to terminate): ");
    	scanf(" %[^\n]%*c", str);
	}
    return 0;
}
