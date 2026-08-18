#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXTOKENS 1000
#define MAXEXPR 1000
#define STACKSIZE 1000
#define QUEUESIZE 1000

typedef struct
{
    char type; //'N' - number, otherwise character of operator, '(' or ')'
    int value; //value if type is 'N', precedence of operator otherwise
} token;

char assoc[] = {'L', 'L', 'R'}; //assoc[p] tells if operators with precedence p are left-associate or right-associative

typedef struct
{
    int top;
    token data[STACKSIZE];
} token_stack;

typedef struct
{
    int top;
    float data[STACKSIZE];
} value_stack;

typedef struct {
	int front;
	int back;
	token data[QUEUESIZE];
} Queue;

void init_queue(Queue *q)
{
	q->front = 0;
	q->back = 0;
}
int isempty_queue(Queue *q)
{
	return (q->front == q->back);
}
int isfull(Queue *q)
{
	return (q->back == QUEUESIZE);
}
void enqueue(Queue *q, token val)
{
	if(isfull(q))
		return;
	q->data[q->back] = val;
	q->back++;
}
token dequeue(Queue *q)
{
	if(isempty_queue(q))
		return q->data[q->front]; //returns garbage
	q->front++;
	return q->data[q->front-1];
}
void printqueue(Queue *q)
{
	printf("\n");
	int i;
	for(i = q->front; i < q->back; i++)
	{
        if(q->data[i].type == 'N')
            printf("%d ", q->data[i].value);
        else
            printf("%c ", q->data[i].type);
	}
}

void init_token_stack(token_stack *s)
{
    s->top = 0;
}

void push_token(token_stack *s, token t)
{
    if(s->top == STACKSIZE)
        return;
    s->data[s->top++] = t;
}

token pop_token(token_stack *s) //returns garbage if stack is empty
{
    if(s->top != 0)
        s->top--;
    return s->data[s->top];
}

int isempty_token_stack(token_stack *s)
{
    return (s->top == 0) ? 1 : 0;
}

token topmost(token_stack *s) //returns garbage if stack is empty
{
    if(s->top == 0)
        return s->data[0];
    return s->data[s->top - 1];
}

void init_value_stack(value_stack *s)
{
    s->top = 0;
}

void push_value(value_stack *s, float t)
{
    if(s->top == STACKSIZE)
        return;
    s->data[s->top++] = t;
}

float pop_value(value_stack *s) //returns garbage if stack is empty
{
    if(s->top != 0)
        s->top--;
    return s->data[s->top];
}

int isempty_value_stack(value_stack *s)
{
    return (s->top == 0) ? 1 : 0;
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
                    case '^':
                        t.value = 2;
                        break;
                    case ')':
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

int postfix(token expr[], int len, Queue *q) // q is assumed to be empty
{
	/*Task 1: Read the stream of tokens corresponding to an infix expression
	 * from the array of tokens expr and write the expression in postfix
	 * notation, again as a stream of tokens, to the queue q. Return -1 if
	 * there is an error in the input and 0 otherwise. You can use the
	 * token_stack type defined above to maintain the stack of operators 
	 * and parentheses needed by the shunting yard algorithm. */
    token_stack s;
    init_token_stack(&s);

    for(int i = 0; i < len; i++)
    {
        token curr = expr[i];

        // 🔵 Case 1: Number → directly to queue
        if(curr.type == 'N')
        {
            enqueue(q, curr);
        }

        // 🔵 Case 2: '(' → push
        else if(curr.type == '(')
        {
            push_token(&s, curr);
        }

        // 🔵 Case 3: ')'
        else if(curr.type == ')')
        {
            while(!isempty_token_stack(&s) && topmost(&s).type != '(')
            {
                enqueue(q, pop_token(&s));
            }

            if(isempty_token_stack(&s)) return -1; // unbalanced
            pop_token(&s); // remove '('
        }

        // 🔵 Case 4: Operator
        else
        {
            while(!isempty_token_stack(&s))
            {
                token top = topmost(&s);

                if(top.type == '(') break;

                int p_top = top.value;
                int p_curr = curr.value;

                // check precedence + associativity
                if( (p_top > p_curr) ||
                    (p_top == p_curr && assoc[p_curr] == 'L') )
                {
                    enqueue(q, pop_token(&s));
                }
                else break;
            }

            push_token(&s, curr);
        }
    }

    // 🔥 pop remaining operators
    while(!isempty_token_stack(&s))
    {
        if(topmost(&s).type == '(') return -1; // unbalanced
        enqueue(q, pop_token(&s));
    }


}

float evaluate(Queue *q) // empties the input queue
{
	/*Task 2: Read the stream of tokens corresponding to an expression in
	 * postfix notation from the queue of tokens q, evaluate the expression and
	 * return the final answer. You can use the data structure value_stack 
	 * defined above. */

    value_stack s;
    init_value_stack(&s);
    while(!isempty_queue(q))
    {
        token t = dequeue(q);

        // 🔵 Number → push
        if(t.type == 'N')
        {
            push_value(&s, t.value);
        }
        else
        {
            float b = pop_value(&s);
            float a = pop_value(&s);
            float res;

            switch(t.type)
            {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                case '^': res = pow(a, b); break;
            }

            push_value(&s, res);
        }
    }

    return pop_value(&s);s
}

int main()
{
    token tk[MAXTOKENS];
    char str[MAXEXPR];
    int len;
	while(1)
	{
    	printf("\nEnter expression (q to quit): ");
    	scanf(" %[^\n]", str);
		if(*str == 'q')
		{	
			printf("\nExiting\n");
			return 0;
		}
    	len = tokenize(str, tk);
    	printf("\n%s\n", str);
    	if(len != -1)
    	{
	//      printTokens(tk, len); //Uncomment to see list of tokens
        	Queue q;
        	init_queue(&q);
        	if(postfix(tk, len, &q) == -1)
            	printf("Expression contains unbalanced parantheses.\n");
        	else
        	{	
        		printf("Expression in postfix notation: ");
				printqueue(&q);
        		printf("\nExpression evaluates to: %g\n", evaluate(&q));
			}
    	}
    	else
        	printf("Tokenization error: invalid expression.\n");
	}
    return 0;
}
