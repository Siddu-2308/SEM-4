#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define L 75

int *temparr; // Temporary array used by the merge function.

struct pnode;
struct pnode {	
	int key;
	struct pnode *next;
};
typedef struct pnode node;

typedef struct {
	node *head;
} list;

void init(list *l)
{
	/*Initializes an empty list.*/

	l->head = NULL;
}

void add(list *l, int keyval)
{
	/*Adds a node with key value keyval to the head of the list l.*/

	node *n = (node *) malloc(sizeof(node));
	n->key = keyval;
	n->next = l->head;
	l->head = n;
}

void populatelist(list *l, int a[], int len)
{
	/*Adds the values in the array a to list l.*/

	int i;
	for(i = 0; i < len; i++)
	{
		add(l, a[i]);
	}
}

void destroy(list *l)
{
	/*Frees the space allocated for the list.*/

	node *temp;
	temp = l->head;
	while(temp != NULL)
	{
		l->head = l->head->next;
		free(temp);
		temp = l->head;
	}
}

void printlist(list *l)
{
	/*This function prints the contents of the list.*/

	node *temp;
	temp = l->head;
	while(temp != NULL)
	{
		printf("%d ",temp->key);
		temp = temp->next;
	}
	printf("\n");
}

node* insert(node *x, node* h) 
{
	/*Inserts a node x into the correct position of a sorted linked list having head node h.*/
	node *ret;
	if(h == NULL || h->key >= x->key)
	{
		x->next = h;
		return x;
	}
	h->next = insert(x,h->next);
	return h;
}

c
void merge(int a[], int p, int q, int r)
{
	/* Helper function for Merge Sort on array.*/

	int i, j, k;
	i = p;
	j = q;
	k = 0;
	while(i < q || j < r)
	{
		if(i == q || (j < r && a[i] > a[j]))
		{
			temparr[k] = a[j++];
		}
		else
		{
			temparr[k] = a[i++];
		}
		k++;
	}
	for(i = 0; i < k; i++)
	{
		a[p + i] = temparr[i];
	}
}

void merge_sort(int a[], int p, int q)
{
	/* Implements Merge Sort on array.*/

	int mid;
	if(q <= p + 1)
		return;
	mid = (p + q) / 2;
	merge_sort(a, p, mid);
	merge_sort(a, mid, q);
	merge(a, p, mid, q);
}

void insertion_sort(int a[], int p, int q)
{
	/* Implements Insertion Sort on an array.*/

	int i, j, temp;
	for(i = p; i < q - 1; i++)
	{
		temp = a[i + 1];
		for(j = i; j >= p && a[j] > temp; j--)
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}
}

void ins_merge_sort(int a[], int p, int q)
{
	/* Implements Insertion-Merge Sort on array.*/

	int mid;
	if(q < p + L)
	{
		insertion_sort(a, p, q);
		return;
	}
	mid = (p + q) / 2;
	ins_merge_sort(a, p, mid);
	ins_merge_sort(a, mid, q);
	merge(a, p, mid, q);
}

int partition(int a[], int p, int q)
{
/* Task 1: Implement the Quick Sort Partition function.
	The subarray a[p]..a[q-1] has to be partitioned taking the value x = a[q-1] as pivot.
	That is, the function has to modify the array and return a position b in the subarray
	such that every element in a[p]..a[b-1] is less than or equal to x, a[b] is equal to
	x and every element in a[b+1]..a[q-1] is greater than x.
*/
	int x=a[q-1];
	int b=p;
	int i=p;
	while(i<q-1){
		if(a[i]< x){
			//swap ai and ab
			int temp=a[i];
			a[i]=a[b];
			a[b]=temp;
			b+=1;
		}
		i+=1;
	}
	//swap ab and aq-1
	int temp2=a[q-1];
	a[q-1]=a[b];
	a[b]=temp2;
	return b;
}

void quicksort(int a[], int p, int q)
{
	/* 	Task 2: Implement Quick Sort on array. 
		This function should sort the subarray from a[p] to a[q-1].
	*/
	if(q-p<=1){
		return;
	}
	else{
		//int mid=p + (q-p)/2;
		int k=partition(a,p,q);
		quicksort(a,p,k);
		quicksort(a,k+1,q);
		
	}
	
}

node *findmid(node *h)
{
	/* Task 3: Given a linked list having head node h, this function should
	return the pointer to a node such that if the linked list is split just
	after this node, we get two linked lists whose lengths differ by at most
	one. You can assume that this function is always called on a linked list
	having at least two nodes.

	Hint. This can be done using a single forward pass through the linked list.
	*/
	node *temp1=h;
	int count1=0;
	while(temp1!=NULL){
		count1++;
		temp1=temp1->next;
	}
	node *temp2=h;
	int mid=(count1-1)/2;
	for(int j=0;j<mid;j++){
		temp2=temp2->next;
	}

	return temp2;
}
node* list_merge(node *h1, node *h2)
{
	/* Task 4: Given two sorted linked lists having head nodes h1 and h2, this
	function should return the head node of a sorted linked list that is the
	union of the two input linked lists. No new nodes should be created, and
	the content of no node should be changed.

	Hint. Think recursion.
	*/
	//node *h3=NULL;
	if(h1==NULL){
		return h2;
	}
	if(h2==NULL){
		return h1;
	}
	if(h1->key<=h2->key){
		h1->next=list_merge(h1->next,h2);
		return h1;
	}
	else{
		h2->next=list_merge(h1,h2->next);
		return h2;
	}
	//return h3;
}
node* list_merge_sort(node *h)
{
	/*Task 5: Implement Merge Sort for linked lists. The function takes as
	input an unsorted linked list having head node h and returns the head node
	of a sorted linked list containing the same nodes as the original list. Use
	the functions findmid and list_merge implemented above. No new nodes should
	be created, and the content of no node should be changed.*/
	if(h->next==NULL){
		return h;
	}
	else{
		node* mid=findmid(h);
		node* second=mid->next;
		mid->next=NULL;
		h=list_merge_sort(h);
		second=list_merge_sort(second);
		return list_merge(h,second);
	}
}
int main()
{
	int *a, *x, len, i;
	clock_t begin, end;
	clock_t mergetime, instime, insmergtime, quicktime, ll_instime, ll_mergetime;
	list l;

	printf("Enter length of array: ");
	scanf("%d", &len);

	a = (int *) malloc(sizeof(int)*len);
	x = (int *) malloc(sizeof(int)*len);	
	temparr = (int *) malloc(sizeof(int)*len);	

	if(a == NULL || x == NULL || temparr == NULL)
	{
		printf("Memory allocation error.\n");
		return 1;
	}

	srand(time(NULL)); // Initializing random number generator 

	for (i = 0; i < len; i++) // Populates the array a with random values in the range 0 .. 4*len-1
	{
		a[i] = rand() % (4 * len);
	}

	for (i = 0; i < len; i++) // Copies the array a to x
	{
		x[i] = a[i];
	}

	printf("\nThe unsorted array:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", x[i]);
	}
	printf("\n");

	begin = clock(); // Store clock value just before merge_sort() is called
	merge_sort(x, 0, len);
	end = clock(); // Store clock value just after the call to merge_sort() returns
	mergetime = end - begin; // Find time elapsed during execution of merge_sort()

	printf("\nArray sorted using Merge Sort:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", x[i]);
	}
	printf("\n");

	for (i = 0; i < len; i++)
	{
		x[i] = a[i];
	}

	begin = clock();
	insertion_sort(x, 0, len);
	end = clock();
	instime = end - begin; // Find time elapsed during execution of insertion_sort()

	printf("\nArray sorted using Insertion Sort:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", x[i]);
	}
	printf("\n");

	for (i = 0; i < len; i++)
	{
		x[i] = a[i];
	}

	begin = clock();
	ins_merge_sort(x, 0, len);
	end = clock();
	insmergtime = end - begin;

	printf("\nArray sorted using Insertion-Merge Sort:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", x[i]);
	}
	printf("\n");

	for (i = 0; i < len; i++)
	{
		x[i] = a[i];
	}

	begin = clock();
	quicksort(x, 0, len);
	end = clock();
	quicktime = end - begin;

	printf("\nArray sorted using Quick Sort:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", x[i]);
	}
	printf("\n");

	init(&l);
	populatelist(&l, a, len);
	begin = clock();
	l.head = list_insertion_sort(l.head);
	end = clock();
	ll_instime = end - begin;

	printf("\nArray sorted using Insertion Sort on linked list:\n");
	printlist(&l);
	printf("\n");

	destroy(&l);

	init(&l);
	populatelist(&l, a, len);
	begin = clock();
	l.head = list_merge_sort(l.head);
	end = clock();
	ll_mergetime = end - begin;

	printf("\nArray sorted using Merge Sort on linked list:\n");
	printlist(&l);
	printf("\n");

	destroy(&l);
	free(a);
	free(x);
	free(temparr);

	printf("\n           %20s|%20s|%20s|%20s|%20s|%20s\n-----------------------------------------------------------------------------------------------------------------------------------------\n","     Merge Sort     ","   Insertion Sort   ","   Ins-Merge Sort   ", "     Quick Sort     ", "  LL Insertion Sort ", "    LL Merge Sort   ");
	printf("Clock ticks%12lu        |%12lu        |%12lu        |%12lu        |%12lu        |%12lu\n\n",mergetime, instime, insmergtime, quicktime, ll_instime, ll_mergetime);

	printf("\n");

}
