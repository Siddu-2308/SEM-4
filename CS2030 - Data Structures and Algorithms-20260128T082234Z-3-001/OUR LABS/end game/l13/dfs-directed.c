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
} Queue; //Queue that supports a "pop" operation that pops off an element from the back of the queue 

typedef struct
{
    int n;
    List **adj;
} Graph;

typedef struct {
    int n; //number of vertices in host graph
    Queue *disclist;
    Queue *finlist;
    int *p; //parent pointers; use -1 for NULL
    int *depth; //depths
    List *trees;
    int **edgetypes;

/* Explanation of the various fields:
    n : the number of vertices of the host graph, i.e. the graph from which this DFS traversal was obtained
    disclist: contains the vertices of the host graph in the order in which they were discovered by the DFS
    finlist: contains the vertices of the host graph in the order in which they were "finished" by the DFS
    p : an array that contains the parent pointers of each vertex; for a vertex u, p[u] is the label of the parent of u in the DFS forest corresponding to this traversal. If u has no parent, that is, if it is the root of some DFS tree, then p[u] is -1.
    depth: an array that contains the depth of each vertex in its DFS tree; for a vertex u, depth[u] is the length of the path to u from  the root of the DFS tree that contains u.
    trees : This is a list that contains the vertex sets of each tree in the DFS forest. The vertices in each tree have to occur consecutively, and the vertex sets of two different trees must be separated by a "-1" entry.
    edgetypes : This is an n x n matrix whose (i,j)-th entry is:
                    0 : if there is no edge from i to j in the graph,
                    1 : if the edge (i,j) is a tree edge,
                    -x, where x is a positive integer : if the edge (i,j) is a back edge between two vertices whose depths differ by x,
                    2 : if (i,j) is an edge that is not a tree edge or back edge.
*/
} DFStraversal;

void init_Queue(Queue *q, int size)
{
	q->data = (int *) malloc(sizeof(int) * (size + 1));
	q->maxlength = size + 1;
	q->front = 0;
	q->back = 0;
}

void destroy_Queue(Queue *q)
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

int pop(Queue *q)
{
	if(isempty(q))
		return -1;
	q->back--;
	if(q->back < 0)
	{
		q->back = q->maxlength - 1;
	}
	return q->data[q->back];
}

void init_LL(List *l)
{
	/*Initializes an empty list.*/

	l->head = NULL;
}

void add_LL(List *l, int val)
{
	/*Adds a node with value "val" to the head of the list l.*/

	Node *nod = (Node *) malloc(sizeof(Node));
	nod->value = val;
	nod->next = l->head;
	l->head = nod;
}

Node *search_LL(List *l, int searchkey)
{
    Node *nod;
    nod = l->head;
    while(nod != NULL && nod->value != searchkey)
        nod = nod->next;
    return nod;
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

Node *duplicate(Node *n)
{
    Node *t;
    if(n == NULL)
        return NULL;
    t = (Node *) malloc (sizeof(Node));
    t->value = n->value;
    t->next = duplicate(n->next);
    return t;
}
List *duplicate_LL(List *l)
{
    /* This helper function creates returns a linked list that is a copy of the linked list l.*/

    List *ret;
    ret = (List *) malloc(sizeof(List));
    init_LL(ret);
    if(l->head != NULL)
        ret->head = duplicate(l->head);
    return ret;
}

void init_Traversal(DFStraversal *T, Graph *G)
{
    int i, j;
    T->n = G->n;
    T->disclist = (Queue *) malloc(sizeof(Queue));
    T->finlist = (Queue *) malloc(sizeof(Queue));
    T->p = (int *) malloc(sizeof(int) * G->n);
    T->depth = (int *) malloc(sizeof(int) * G->n);
    T->trees = (List *) malloc(sizeof(List));
    init_LL(T->trees);
    init_Queue(T->disclist, G->n);
    init_Queue(T->finlist, G->n);
    T->edgetypes = (int **) malloc(sizeof(int *) * G->n);
    for(i = 0; i < G->n; i++)
        T->edgetypes[i] = (int *) malloc(sizeof(int) * G->n);
    for(i = 0; i < G->n; i++)
    {
        for(j = 0; j < G->n; j++)
            T->edgetypes[i][j] = 0;
    }
}

void destroy_Traversal(DFStraversal *T)
{
    int i;
    destroy_Queue(T->disclist);
    destroy_Queue(T->finlist);
    destroy_LL(T->trees);
    free(T->trees);
    for(i = 0; i < T->n; i++)
        free(T->edgetypes[i]);
    free(T->edgetypes);
    free(T->disclist);
    free(T->finlist);
    free(T->p);
    free(T->depth);
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

Graph *reverseGraph(Graph *G)
{
    /* This helper function returns a new graph that is obtained by reversing all the edges of G.*/

    Graph *ret;
    Node *nod;
    int i;
    ret = (Graph *) malloc(sizeof(Graph));
    init_Graph(ret, G->n);
    for(i = 0; i < G->n; i++)
    {
        nod = G->adj[i]->head;
        while(nod != NULL)
        {
            add_LL(ret->adj[nod->value], i);
            nod = nod->next;
        }
    }
    return ret;
}

int showGraph(Graph *G, int **edgetypes)
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

                if(edgetypes != NULL && edgetypes[i][t->value] == 1)
                    fprintf(fp, " _");
                else if(edgetypes != NULL && edgetypes[i][t->value] < 0)
                    fprintf(fp, " +");
                else if(edgetypes != NULL && edgetypes[i][t->value] == 2)
                    fprintf(fp, " *");
                else
                    fprintf(fp, " ");

                fprintf(fp, "%d", t->value);
                t = t->next;
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
    return 0;
}

void dfs_visit(Graph *G, int u, DFStraversal *T, int *state)
{
    /* Task 1b: Implement the DFS-VISIT helper function for the dfs function given below. This function takes the an array state and the pointer to an integer time. For each vertex u, state[u] will contain the state of u at the point at which this function has been called.*/
    state[u]=1;
    enqueue(T->disclist,u);
    Node *temp=G->adj[u]->head;
    while(temp!=NULL){
        if(state[temp->value]==0){
            T->edgetypes[u][temp->value]=1;
            T->p[temp->value]=u;
            T->depth[temp->value]=T->depth[u]+1;
            dfs_visit(G,temp->value,T,state);
        }
        else{
            if(state[temp->value]==1){
                int diff=T->depth[u]-T->depth[temp->value];
                T->edgetypes[u][temp->value]=-diff;

            }
            else{
                T->edgetypes[u][temp->value]=2;
            }

        }
        temp=temp->next;
    }
    state[u]=2;
    enqueue(T->finlist,u);
    /*| Condition       | Meaning           | Edge type      |
    | --------------- | ----------------- | -------------- |
    | `state[v] == 0` | not visited       | Tree edge (1)  |
    | `state[v] == 1` | ancestor (active) | Back edge (-x) |
    | `state[v] == 2` | already finished  | Other edge (2) |
    */
}

DFStraversal *dfs(Graph *G, Queue *q)
{
    /* Task 1a: Implement Depth First Search using the functions dfs and dfs_visit which have been given as placeholders.
    
    If q is not NULL, then q contains the vertices of G in some order. The outermost loop of the DFS has to consider the vertices in the reverse of the order given by q (calling pop(q) repeatedly retrieves the elements of q in reverse order) for calling dfs_visit on them. The queue q can be changed, or even emptied, by this function. If q is NULL, then the outermost loop of the DFS can process the vertices in any order.

    The function returns the pointer to an object of type DFStraversal. Refer to the definition of this data type at the top for an explanation of how the fields of a DFStraversal object have to be filled in.
    */

    int u;
    DFStraversal *T;
    int *state;
    T = (DFStraversal *) malloc(sizeof(DFStraversal));
    init_Traversal(T, G);
    state = (int *) malloc(sizeof(int) * G->n);
    for(u = 0; u < G->n; u++)
    {
        state[u] = 0;
        T->p[u] = -1; //instead of NULL
        T->depth[u] = 0;
    }

    /* Insert your code that calls dfs_visit here */
    if(q!=NULL){
        while(!isempty(q)){
            u=pop(q);
            if(state[u]==0){
                add_LL(T->trees,-1);
                dfs_visit(G,u,T,state);
            }
        }
    }
    else{
        for(u = 0; u < G->n; u++)
        {
            if(state[u] == 0)
            {
                add_LL(T->trees, -1);   // new tree
                dfs_visit(G, u, T, state);
            }
        }

    }


    free(state);
    return T;
}
List *checkDAG(Graph *G)
{
    /* Task 2: Check if G is a DAG. Return NULL if it is a DAG. Otherwise return a list that contains the vertices of a directed cycle in G in the cyclic order.*/
    DFStraversal *T = dfs(G, NULL);
    int i, j;

    for(i = 0; i < G->n; i++)
    {
        for(j = 0; j < G->n; j++)
        {
            if(T->edgetypes[i][j] < 0)
            {
                // cycle found
                List *cycle = (List *) malloc(sizeof(List));
                init_LL(cycle);

                add_LL(cycle, j);
                add_LL(cycle, i);

                destroy_Traversal(T);
                free(T);
                return cycle;
            }
        }
    }

    destroy_Traversal(T);
    free(T);
    return NULL; // DAG
    
}
List *topsort(Graph *G)
{
    /* Task 3: Assuming that G is a DAG, return a list containing the vertices of G in a topologically sorted order.*/
    DFStraversal *T = dfs(G, NULL);
    List *result = (List *) malloc(sizeof(List));
    init_LL(result);

    while(!isempty(T->finlist))
    {
        int v = dequeue(T->finlist);
        add_LL(result, v); // reverse order
    }

    destroy_Traversal(T);
    free(T);

    return result;
}
void scc_dfs_visit(Graph *Gr, int u, int *state, List *l)
{
    Node *temp;
    state[u] = 1; // Visited
    temp = Gr->adj[u]->head;
    while(temp != NULL)
    {
        if(state[temp->value] == 0)
        {
            scc_dfs_visit(Gr, temp->value, state, l);
        }
        temp = temp->next;
    }
    state[u] = 2; // Finished
    
    /* Prepend the vertex to the list. Because add_LL adds to the head, 
       this builds the component list segment. */
    add_LL(l, u);
}
List *strongcomponents(Graph *G)
{
    /* Task 4: Return a list containing the vertex sets of the strongly connected components of G. The vertices in each strongly connected component have to occur consecutively on the list and the vertex sets of two different strongly connected components must be separated by a "-1" entry between them.*/
    DFStraversal *T1;
    Graph *Gr;
    List *result;
    int *state;
    int i, u;

    /* 1. First pass: DFS on G to compute finishing times.
       The finishing times are stored in T1->finlist. */
    T1 = dfs(G, NULL);

    /* 2. Reverse the graph. */
    Gr = reverseGraph(G);

    /* 3. Initialize the result list and a state array for the second pass. */
    result = (List *) malloc(sizeof(List));
    init_LL(result);
    
    state = (int *) malloc(sizeof(int) * G->n);
    for(i = 0; i < G->n; i++)
        state[i] = 0;

    /* 4. Second pass: Process vertices in decreasing order of finishing times.
       Using pop() on the finlist retrieves vertices from the back (latest finished). */
    while(!isempty(T1->finlist))
    {
        u = pop(T1->finlist);
        if(state[u] == 0)
        {
            /* Every time we start a new DFS visit from this loop, we've found a new SCC.
               We add the vertices of the SCC to the list first. */
            scc_dfs_visit(Gr, u, state, result);
            
            /* Then we prepend -1 to signify the start/boundary of this component.
               In the resulting list, this -1 will appear BEFORE the vertices 
               when main() traverses head -> next. */
            add_LL(result, -1);
        }
    }

    /* Clean up temporary memory */
    free(state);
    destroy_Graph(Gr);
    free(Gr);
    destroy_Traversal(T1);
    free(T1);

    return result;

}

void userinput()
{
    int i;
    while(1)
    {
        printf("\nEnter -1 for next step: ");
        scanf("%d", &i);
        if(i < 0)
            break;
    }
}

int main()
{
    int i, j;
    int **mat;
    Graph G;
    List *l;
    DFStraversal *T;
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

    T = dfs(&G, NULL);
    printf("\nVertices visited in order:\n");
    while(!isempty(T->disclist))
        printf(" %d", dequeue(T->disclist));

    mat = (int **) malloc(sizeof(int *) * G.n);
    for(i = 0; i < G.n; i++)
        mat[i] = (int *) malloc(sizeof(int) * G.n);
    for(i = 0; i < G.n; i++)
    {
        for(j = 0; j < G.n; j++)
            mat[i][j] = 0;
    }

    for(i = 0; i < G.n; i++)
    {
        if(T->p[i] != -1)
            mat[T->p[i]][i] = 1;
    }
    
    showGraph(&G, mat);
    destroy_Traversal(T);
    free(T);

    userinput();

    T = dfs(&G, NULL);
    showGraph(&G, T->edgetypes);
    destroy_Traversal(T);
    free(T);

    userinput();

    l = strongcomponents(&G);
    if(l != NULL)
    {
        Node *t;
        int c;
        c = 0;
        t = l->head;
        while(t != NULL)
        {
            if(t->value == -1)
            {
                c++;
                printf("\nStrong component %d:\n", c);
            }
            else
                printf(" %d", t->value);
            t = t->next;
        }
        printf("\n");
        destroy_LL(l);
        free(l);
    }
    
    userinput();

    l = checkDAG(&G);
    if(l != NULL)
    {
        Node *t;
        printf("Cycle found: ");
        t = l->head;
        while(t != NULL)
        {
            printf(" %d", t->value);
            t = t->next;
        }
        destroy_LL(l);
        free(l);
    }
    else
    {
        Node *t;
        l = topsort(&G);
        printf("Topological ordering: ");
        t = l->head;
        while(t != NULL)
        {
            printf(" %d", t->value);
            t = t->next;
        }
        destroy_LL(l);
        free(l);
    }

    userinput();

    destroy_Graph(&G);
    kill(guiproc, SIGTERM);
    return 0;
}