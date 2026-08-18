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
    int *p; //parent pointer. use -1 for NULL   
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

void reverse_LL(List *l)
{
    Node *cur, *prev;
    if(l->head == NULL)
        return;
    prev = l->head;
    cur = l->head->next;
    l->head->next = NULL;
    while(cur != NULL)
    {
        Node *temp;
        temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }
    l->head = prev;
}

void concatenate_LL(List *l, List *r)
{
    Node *n, *prev;
    n = l->head;
    prev = NULL;
    while(n != NULL)
    {
        prev = n;
        n = n->next;
    }
    if(prev != NULL)
        prev->next = r->head;
    else
        l->head = r->head;
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
    {
        add_LL(G->adj[u],v);
        add_LL(G->adj[v],u);
    }
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
	/* Task 1: Implement Breadth First Search Algorithm on the undirected graph
	 * G starting from the vertex s. The function should return a structure of
	 * type BFStraversal with all its fields correctly populated. Please see
	 * the definition of the type BFStraveral at the top of this file. 

	 * Remember to destroy and free the BFStraversal object after use in the
	 * function which calls this function. */

    int i;
    int *state;
    Queue q;
    BFStraversal *T;

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
    
	/* Enter your code here */
     //t has len,p(parent array),d(dist array),order(..)
    enqueue(&q,s);
    T->d[s]=0;
    state[s]=1;
    while(!isempty(&q)){
        int dq=dequeue(&q);
        T->order[T->len++]=dq;
        Node *temp=G->adj[dq]->head;
        while(temp!=NULL){
            int val=temp->value;
            if(state[val]==0){
                enqueue(&q,val);
                state[val]=1;
                T->p[val]=dq;
                T->d[val]=T->d[dq]+1;
            }
            temp=temp->next;
        }
        state[dq]=2;
    }


	destroy_queue(&q);
	free(state);
    return T;
}

void print_LL(List *l)
{
    Node *t;
    t = l->head;
    printf("\n");
    while(t != NULL)
    {
        printf("%d ", t->value);
        t = t->next;
    }
    printf("\n");
}

List *connectedcomponents(Graph *G)
{
	/*Task 3: (Task 2 is in the file bfs-directed.c) Find the connected
	 * components in the graph G. Return a linked list of vertex labels, with
	 * the vertices of each connected component appearing consecutively in the
	 * list and vertices in different components being separated by a node with
	 * value -1. */
    int *state=(int *)malloc(sizeof(int) * G->n);;
    for(int i=0;i<G->n;i++){
        state[i]=0;
    }
    List *result = (List *) malloc(sizeof(List));
    init_LL(result);
    for(int i=0;i<G->n;i++){
        if(state[i]==0){
            BFStraversal *T=bfs(G,i);
            for(int j=0;j<T->len;j++){
                int v=T->order[j];
                if(state[v]==0){
                    add_LL(result,v);
                    state[v]=1;
                }
            }
            add_LL(result, -1);
            destroy_traversal(T);
            free(T);
        }
    }

    reverse_LL(result);

    if(result->head != NULL && result->head->value == -1)
    {
        Node *temp = result->head;
        result->head = temp->next;
        free(temp);
    }
    free(state);
    return result;

}

List *diameterpath(Graph *G)
{
	/*Task 4: A diameter path in a graph is a shortest path with the largest
	 * possible length. (Its length is called the diameter of the graph.) Find
	 * a diameter path of the graph G. The path found should be returned as a
	 * list of vertex labels. */

    BFStraversal *T1 = bfs(G, 0);

    int farthest = 0;
    for(int i = 0; i < G->n; i++){
        if(T1->d[i] > T1->d[farthest]){
            farthest = i;
        }
    }

    destroy_traversal(T1);
    free(T1);

    BFStraversal *T2 = bfs(G, farthest);

    int end = farthest;
    for(int i = 0; i < G->n; i++){
        if(T2->d[i] > T2->d[end]){
            end = i;
        }
    }

    List *path = (List *)malloc(sizeof(List));
    init_LL(path);

    int cur = end;
    while(cur != -1){
        add_LL(path, cur);
        cur = T2->p[cur];
    }

    destroy_traversal(T2);
    free(T2);

    return path;
}

int **APD(Graph *G)
{
	/*Task 5: Compute the All Pairs Distances matrix. The (i,j)-th entry of the
	 * matrix should contain the distance (length of a shortest path) between
	 * vertices i and j. The distance should be marked as -1 for two vertices
	 * which do not have a path between them. */

    int **mat = (int **)malloc(sizeof(int *) * G->n);

    for(int i = 0; i < G->n; i++){
        mat[i] = (int *)malloc(sizeof(int) * G->n);

        BFStraversal *T = bfs(G, i);

        for(int j = 0; j < G->n; j++){
            mat[i][j] = T->d[j]; // already -1 if unreachable
        }

        destroy_traversal(T);
        free(T);
    }

    return mat;

}

List *bipartition(Graph *G)
{
	/*Task 6: A graph is called bipartite, if vertex set can be partitioned
	 * into two sets such that every edge has one endpoint in the first set and
	 * the other endpoint in the other set. This function should check if the
	 * input graph G is bipartite and return a linked list of vertex labels,
	 * with vertices in one set appearing first, followed by a node with value
	 * -1, and then the vertices of the other set. It should return NULL if the 
	 * graph is not bipartite. */

    int *color = (int *)malloc(sizeof(int) * G->n);
    for(int i = 0; i < G->n; i++)
        color[i] = -1;

    for(int i = 0; i < G->n; i++){
        if(color[i] == -1){
            Queue q;
            init_Queue(&q, G->n + 1);

            enqueue(&q, i);
            color[i] = 0;

            while(!isempty(&q)){
                int u = dequeue(&q);

                Node *temp = G->adj[u]->head;
                while(temp != NULL){
                    int v = temp->value;

                    if(color[v] == -1){
                        color[v] = 1 - color[u];
                        enqueue(&q, v);
                    }
                    else if(color[v] == color[u]){
                        destroy_queue(&q);
                        free(color);
                        return NULL; // not bipartite
                    }

                    temp = temp->next;
                }
            }

            destroy_queue(&q);
        }
    }

    List *result = (List *)malloc(sizeof(List));
    init_LL(result);

    // add set 1
    for(int i = 0; i < G->n; i++){
        if(color[i] == 0)
            add_LL(result, i);
    }

    add_LL(result, -1);

    // add set 2
    for(int i = 0; i < G->n; i++){
        if(color[i] == 1)
            add_LL(result, i);
    }

    reverse_LL(result);

    free(color);
    return result;
}

List *shortestcycle(Graph *G)
{
	/*Task 7: This function should find a cycle of least length in the graph G.
	 * It should return a linked list of vertices in such a cycle in the cyclic
	 * order. It should return NULL if the graph does not contain any cycle. */

    int min_len = 100000;
    int *best_parent = NULL;
    int best_u = -1, best_v = -1;

    for(int s = 0; s < G->n; s++){
        int *dist = (int *)malloc(sizeof(int) * G->n);
        int *parent = (int *)malloc(sizeof(int) * G->n);

        for(int i = 0; i < G->n; i++){
            dist[i] = -1;
            parent[i] = -1;
        }

        Queue q;
        init_Queue(&q, G->n + 1);

        enqueue(&q, s);
        dist[s] = 0;

        while(!isempty(&q)){
            int u = dequeue(&q);

            Node *temp = G->adj[u]->head;
            while(temp != NULL){
                int v = temp->value;

                if(dist[v] == -1){
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    enqueue(&q, v);
                }
                else if(parent[u] != v){
                    int cycle_len = dist[u] + dist[v] + 1;

                    if(cycle_len < min_len){
                        min_len = cycle_len;

                        if(best_parent != NULL)
                            free(best_parent);

                        best_parent = (int *)malloc(sizeof(int) * G->n);
                        for(int k = 0; k < G->n; k++)
                            best_parent[k] = parent[k];

                        best_u = u;
                        best_v = v;
                    }
                }

                temp = temp->next;
            }
        }

        destroy_queue(&q);
        free(dist);
        free(parent);
    }

    if(min_len == 100000)
        return NULL;

    List *cycle = (List *)malloc(sizeof(List));
    init_LL(cycle);

    // path from u
    int *path1 = (int *)malloc(sizeof(int) * G->n);
    int len1 = 0;
    int x = best_u;
    while(x != -1){
        path1[len1++] = x;
        x = best_parent[x];
    }

    // path from v
    int *path2 = (int *)malloc(sizeof(int) * G->n);
    int len2 = 0;
    x = best_v;
    while(x != -1){
        path2[len2++] = x;
        x = best_parent[x];
    }

    // find LCA
    int i = len1 - 1, j = len2 - 1;
    while(i >= 0 && j >= 0 && path1[i] == path2[j]){
        i--; j--;
    }
    i++; j++;

    // build cycle
    for(int k = 0; k <= i; k++)
        add_LL(cycle, path1[k]);

    for(int k = j-1; k >= 0; k--)
        add_LL(cycle, path2[k]);

    free(path1);
    free(path2);
    free(best_parent);

    return cycle;
}

int main()
{
    int i, j;
    int **mat;
    Graph G;
    List *l;
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
        execlp("python3", "python3", "showgraph.py", (char *) NULL);
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
            if(isEdge(&G, i, j))
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
    l = shortestcycle(&G);
    if(l == NULL)
        printf("\nGraph contains no cycle.\n");
    else
    {
        Node *t;
        t = l->head;
        printf("\nShortest cycle:");
        while(t != NULL)
        {
            printf(" %d", t->value);
            t = t->next;
        }
        printf("\n");
        destroy_LL(l);
        free(l);
    }
    l = connectedcomponents(&G);
    if(l != NULL)
    {
        Node *t;
        int c;
        c = 1;
        t = l->head;
        printf("\nComponent %d:\n", c);
        while(t != NULL)
        {
            if(t->value == -1)
            {
                c++;
                printf("\nComponent %d:\n", c);
            }
            else
                printf(" %d", t->value);
            t = t->next;
        }
        printf("\n");
        destroy_LL(l);
        free(l);
    }
    l = diameterpath(&G);
    if(l != NULL)
    {
        Node *t;
        t = l->head;
        printf("\nDiameter path: ");
        while(t != NULL)
        {
            printf(" %d", t->value);
            t = t->next;
        }
        printf("\n");
        destroy_LL(l);
        free(l);
    }
    l = bipartition(&G);
    if(l == NULL)
    {
        printf("\nGraph is not bipartite.\n");
    }
    else
    {
        Node *t;
        int flag;
        flag = 0;
        printf("\nGraph is bipartite. A bipartition: {");
        t = l->head;
        while(t != NULL)
        {
            if(flag == 0)
                flag = 1;
            else if(t->value != -1)
                printf(",");
            if(t->value == -1)
            {
                printf(" }, {");
                flag = 0;
            }
            else
                printf(" %d", t->value);
            t = t->next;
        }
        printf(" }\n");
        destroy_LL(l);
        free(l);
    }
    mat = APD(&G);
    for(i = 0; i < G.n; i++)
    {
        printf("\n");
        for(j = 0; j < G.n; j++)
        {
            if(mat[i][j] == -1)
                printf("  \u221E");
            else
                printf(" %2d", mat[i][j]);
        }
    }
    printf("\n");
    for(i = 0; i < G.n; i++)
    {
        free(mat[i]);
    }
    free(mat);
    while(1)
    {
        printf("\nEnter -1 to exit: ");
        scanf("%d", &i);
        if(i < 0)
            break;
    }
    destroy_Graph(&G);
    kill(guiproc, SIGTERM);
    return 0;
}
