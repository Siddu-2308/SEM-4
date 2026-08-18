#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

struct node;
struct node {	
	int value;
	struct node *next;
};
typedef struct node Node;

typedef struct {
	Node *head;
} List;

typedef struct {
	int *data;
	int front;
	int back;
	int maxlength;
} Queue;

typedef struct
{
    int n;
    List **adj;
} Graph;

typedef struct {
    int len; //number of vertices visited in this traversal
    int *d; //d values of the vertices
    int *order; //order in which vertices are visited
    int *p; //use -1 for NULL   
} BFStraversal;

void init_Queue(Queue *q, int size)
{
	q->data = (int *) malloc(sizeof(int) * size);
	q->maxlength = size;
	q->front = 0;
	q->back = 0;
}

void destroy_queue(Queue *q)
{
	free(q->data);
}

int isempty(Queue *q)
{
	return (q->front == q->back);
}

int isfull(Queue *q)
{
	return (q->back == ((q->front != 0)? q->front - 1 : q->maxlength - 1));
}

void enqueue(Queue *q, int val)
{
	if(isfull(q))
		return;
	q->data[q->back] = val;
	q->back++;
	if(q->back == q->maxlength)
		q->back = 0;
}

int dequeue(Queue *q)
{
	int ret;
	if(isempty(q))
		return -1;
	ret = q->data[q->front];
	q->front++;
	if(q->front == q->maxlength)
	{
		q->front = 0;
	}
	return ret;
}

void init_traversal(BFStraversal *T, Graph *G)
{
    T->len = 0;
    T->order = (int *) malloc(sizeof(int) * G->n);
    T->d = (int *) malloc(sizeof(int) * G->n);
    T->p = (int *) malloc(sizeof(int) * G->n);
}

void destroy_traversal(BFStraversal *T)
{
    free(T->order);
    free(T->d);
    free(T->p);
}

void init_LL(List *l)
{
	/*Initializes an empty list.*/

	l->head = NULL;
}

void add_LL(List *l, int val)
{
	/*Adds a node with value "val" to the head of the list l.*/

	Node *n = (Node *) malloc(sizeof(Node));
	n->value = val;
	n->next = l->head;
	l->head = n;
}

Node *search_LL(List *l, int searchkey)
{
    Node *n;
    n = l->head;
    while(n != NULL && n->value != searchkey)
        n = n->next;
    return n;
}

void destroy_LL(List *l)
{
	/*Frees the space allocated for the list.*/

	Node *temp;
	temp = l->head;
	while(temp != NULL)
	{
		l->head = l->head->next;
		free(temp);
		temp = l->head;
	}
}

void init_Graph(Graph *G, int numvertices)
{
    int i;
    G->n = numvertices;
    G->adj = (List **) malloc(sizeof(List *) * G->n);
    for(i = 0; i < G->n; i++)
    {
        G->adj[i] = (List *) malloc(sizeof(List));
        init_LL(G->adj[i]);
    }
}

void destroy_Graph(Graph *G)
{
    int i;
    for(i = 0; i < G->n; i++)
        destroy_LL(G->adj[i]);
    free(G->adj);
}

void addEdge(Graph *G, int u, int v)
{
    if(u < G->n && v < G->n)
        add_LL(G->adj[u],v);
}

int isEdge(Graph *G, int u, int v)
{
    if(search_LL(G->adj[u], v) == NULL)
        return 0;
    else
        return 1;
}

int showGraph(Graph *G, BFStraversal *T)
{
    int i;
    FILE *fp;
    fp = fopen("graph.txt", "w");
    if(fp == NULL)
        return -1;
    if(G != NULL)
    {   
        for(i = 0; i < G->n; i++)
        {
            Node *t;
            fprintf(fp, "%d :", i);
            t = G->adj[i]->head;
            while(t != NULL)
            {
                if(t != G->adj[i]->head)
                    fprintf(fp, ",");
                if(T != NULL && T->p[t->value] == i)
                    fprintf(fp, " _%d", t->value);
                else
                    fprintf(fp, " %d", t->value);
                t = t->next;
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
    return 0;
}

BFStraversal *bfs(Graph *G, int s)
{
	/* Task 2: Implement Breadth First Search algorithm on the directed graph
	 * G starting from the vertex s. The function should return a structure of
	 * type BFStraversal with all its fields correctly populated. Please see
	 * the definition of the type BFStraveral at the top of this file. */

    int i;
    int *state;//0,1,2

    Queue q;
    BFStraversal *T;  //t has len,p(parent array),d(dist array),order(..)

    init_Queue(&q, G->n + 1);

    T = (BFStraversal *) malloc(sizeof(BFStraversal));
    init_traversal(T, G);

    state = (int *) malloc(sizeof(int) * G->n);

    for(i = 0; i < G->n; i++)
    {
        state[i] = 0;
        T->p[i] = -1; //instead of NULL
        T->d[i] = -1; //instead of infinity
    }
    
	/* Your code here */
    enqueue(&q, s);
    state[s] = 1;
    T->d[s] = 0;
    //t has len,p(parent array),d(dist array),order(..)
    while(!isempty(&q))
    {
        int u = dequeue(&q);

        T->order[T->len++] = u;

        Node *temp = G->adj[u]->head;

        while(temp != NULL)
        {
            int v = temp->value;

            if(state[v] == 0)
            {
                enqueue(&q, v);
                state[v] = 1;

                T->d[v] = T->d[u] + 1;
                T->p[v] = u;
            }

            temp = temp->next;
        }
        state[u]=2;
    }

	free(state);
	destroy_queue(&q);
    return T;
}

int main()
{
    int i, j;
    Graph G;
    pid_t guiproc;
    showGraph(NULL, NULL); //clears the graph.txt file

    printf("Enter the number of vertices: ");
    scanf("%d", &i);
    if(i <= 0)
        return 0;

    guiproc = fork();
    if(guiproc < 0)
        return -1;
    else if(guiproc == 0)
    {
        execlp("python3", "python3", "showdigraph.py", (char *) NULL);
    }

    init_Graph(&G, i);
    showGraph(&G, NULL);
    printf("Vertices numbered 0 to %d\n", G.n - 1);
    printf("Enter the edges (terminate by -1): ");
    while(1)
    {
        scanf("%d", &i);
        if(i < 0)
            break;
        scanf("%d", &j);
        if(j < 0)
            break;
        if(i < G.n && j < G.n)
        {
            if(isEdge(&G, i, j) == 1)
            {
                printf("Edge already exists.\n");
            }
            else
            {
                addEdge(&G, i, j);
                if(showGraph(&G, NULL) == -1)
                {
                    printf("Error writing to file.\n");
                    break;
                }
            }
        }
        else
            printf("Invalid edge (%d, %d).\n", i, j);
    }
    while(1)
    {
        BFStraversal *T;
        printf("\nEnter vertex to start BFS from (-1 to exit): ");
        scanf("%d", &i);
        if(i < 0)
            break;
        if(i < G.n)
        {
            T = bfs(&G, i);
            printf("\nVertices visited in order:\n");
            for(i = 0; i < T->len; i++)
                printf("%d (distance %d)\n", T->order[i], T->d[T->order[i]]);
            printf("\n");
            showGraph(&G, T);        
            destroy_traversal(T);
            free(T);
        }
        else
            printf("Invalid vertex.\n");
    }
    destroy_Graph(&G);
    kill(guiproc, SIGTERM);
    return 0;
}
