/*
	Name:		<full name>
	Roll No:	<roll number>
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 7
	Tasks:		1 to 6
	
	Aim: 		Implement a MaxHeap using arrays. 
				Recall that a MaxHeap is a nearly complete binary tree with the
				property that the value of any node is never more than the
				value of its parent node.
	Assume:		All data to be stored are integers.
	Inst:		Do not change any function interface
*/

#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc
#include <time.h>	// To seed random number generator
#include <limits.h>	// For INT_MIN

#define HEAP_SIZE 15 // Default size of the heap

typedef struct {
    int *data;		// Pointer to the start of array which stores the data. 
    int size;		// Number of data items currently in the heap
    int capacity;	// Memory currently allotted for the heap.
} Heap;


void init_heap(Heap* h) {
	h->size 		= 0;
	h->capacity		= HEAP_SIZE;	
	
	h->data = (int*) malloc(h->capacity * sizeof(int));
	if (h->data == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}
	else {
		printf("A heap of size %d initialized successfully.\n", h->capacity);
	}
}

void free_heap(Heap* h) {
	h->size 		= 0;
	h->capacity		= 0;	
	free(h->data);
	printf("Memory allocated for heap freed.\n");
}

/* 	Next four functions abstracts out the computations to get 
	a)	index of the parent,
	b)	index of the left child,
	c)	index of the right child, and
	c)	level of
	the given index.

	Note that array indices start from 0 in C */
int parent(int i) {
	return (i == 0) ? -1 : (i-1)/2;
}
int left(int i) {
	return 2*i + 1;	
}
int right(int i) {
	return 2*i + 2;
}
int level(int i) {
	int l = 0;
		while (i > 0) {
			i = parent(i);
			l ++;
		}
	return l;
}

int is_heap(Heap* h) {
/*	Input:	A potential heap h
	Output:	1 if h satisfies the max heap property. 0 otherwise */

	for (int i = h->size-1; i > 0; i--)
		if (h->data[i] > h->data[parent(i)])
			return 0;
	return 1;
}

/*	Prints the heap in a tree-like way.
	It took me about an hour to get the aesthetics of this correct.
	So please take time at the end of the lab to understand the
	math behind this aesthetics :) */
void print_heap(Heap* h) {
	int padding = 1;	// for alignment
	for (int i = 0; i < level(h->size-1); i++)
		padding = padding * 2 + 1;

	int l = 0;		// level
	for(int i = 0; i < h->size; i++) {
		if(level(i) > l) {
			printf("\n");
			l = level(i);
			padding = padding / 2;
		}
		// To prefix some space and a line 
		for (int i = 0; i < (padding+1)/2; i++)
			printf("  ");
		for (int i = (padding+1)/2; i < padding; i++)
			printf("__");

		printf("%2d", h->data[i]);	// Online line that prints any data.

		// To suffix a line and some space
		for (int i = (padding+1)/2; i < padding; i++)
			printf("__");
		for (int i = 0; i < (padding+1)/2; i++)
			printf("  ");
		printf("  ");
	}
	printf("\n");
	if (is_heap(h))
		printf("Max heap property satisfied.\n");
	else
		printf("Max heap property NOT satisfied.\n");

	return;
}

void swap(int a[], int i, int j, int size) {
/*	Input: 	An array a; two indices i and j; size of the array
	Action: Swaps the data values in locations i and j
	Error: 	Prints "Error in swap: Index out of range" to stderr 
			if i or j is outside the heap 
	Note:	Checking for the index overflow is a good bug catcher */

	if (i < 0 || i >= size || j < 0 || j >= size) {
		fprintf(stderr, "Error in swap: Index out of range (%d, %d, %d).\n",
			i, j, size);
		return;
	}
	
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
	return;
}


/* Task 1. Heapify */
void heapify(Heap *h, int i) {
/*	Input: 	A nearly complete binary tree h and an index i in the h.
	Assume:	The left and right subtrees of i satisfy the max heap property	
	Action: Rearranges the tree such that the subtree hanging from i 
			satisfies the heap property.
*/
	// Task 1 Solution
	int largest = 0;
	int l = left(i);
	int r = right(i);

	if(l < h->size && h->data[l] > h->data[i])
		largest = l;
	else
		largest = i;
	
	if(r < h->size && h->data[r] > h->data[largest])
		largest = r;

	if(largest != i){
		swap(h->data, i, largest, h->size);
		heapify(h, largest);
	}

	return;
}

/* Task 2. Build Heap */
void build_heap(Heap *h) {
/*	Input: 	A nearly complete binary tree h which may not satisfy the heap property.
	Action: Rearranges the heap using repeated calls to heapify 
			so that it satisfies the heap property. */
	
	// Task 2. Solution
	int i = (h->size - 1) / 2;
	for(; i >= 0; i--){
		heapify(h, i);
	}
	return;
}

/* Task 3. Insert */
void insert(Heap *h, int data) {
/*	Input: 	A heap h and a data to be inserted to the heap
	Assume:	The heap h satisfies the max heap property before insertion.
	Action: Inserts data to h and re-establishes the max heap property 
			for the new heap in O(log h->size) time.
	Error:	Prints "Error in insert: Heap Full" to stderr if h is full
*/
	// Task 3 Solution
	if(h->size >= h->capacity){
		fprintf(stderr, "Error in insert: Heap Full\n");
		return;
	}

	// h->size++;
	h->data[++h->size] = data;
	int i = h->size - 1; 
	while(i > 0 && h->data[parent(i)] < h->data[i]){
		swap(h->data, i, parent(i), h->size);
		i = parent(i);
	}
	
	return;
}


/* Task 4. Extract Max */
int extract_max(Heap *h) {
/*	Input: 	A heap h 
	Assume:	The heap h satisfies the max heap property before extraction.
	Action: Returns the maximum element in h after removing it from h
			and re-establishing the max-heap property for the remaining heap.
	Error:	Prints "Error in extract_max: Heap Empty" to stderr if h is empty
			and return INT_MIN (wonder why!)
*/
	// Task 4 Solution
	if(h->size <= 0){
		fprintf(stderr, "Error in extract_max: Heap Empty\n");
		return INT_MIN;
	}
	int key = h->data[0];
	h->data[0] = h->data[h->size - 1];
	h->size--;
	heapify(h, 0); 


	return key; // You may have to edit this
}

/* Task 5. In-place Heap Sort */
void sort_heap(Heap* h) {
/*	Input: 	A heap h 
	Assume:	The heap h satisfies the max heap property before extraction.
	Action: Sorts the data in h in non-decreasing order using extract_max(). 
			The maximum value is secretly appended to the end of the heap
			and the heap size is reset to the full value after the sorting. */

	// Task 5 Solution
	int temp = h->size;
	build_heap(h);
	// printf("Message 0\n");

	for(int i = h->size - 1; i >= 1; i--){
		swap(h->data, i, 0, h->size);
		// printf("Message 0.1\n");
		h->size--;
		heapify(h, 0);
		// printf("Message 1\n");
	}
	h->size = temp;

	return;
}

/* To compare the running time between selection sort and heap sort */

/* Selection Sort */
void sort_sel(int a[], int size) {
/*	Input: 	An array a of size many integers
	Action: Sorts the data in a in non-decreasing order using selection sort */
	
	if (size <= 1)
		return;

	int i_min = 0;
	for (int i = 1; i < size; i++) {
		if (a[i] < a[i_min]) 
			i_min = i;
	}

	swap(a, 0, i_min, size);
	sort_sel(a + 1, size-1);
}


/* Quick Sort */

/* Partition using one pointer */
int partition1(int a[], int size, int pi) {
/*	Input: An integer array a, it's size and locaiton of pivot
	Action: Orders the array so that all the elements less than
			the pivot comes first, then one copy of the pivot,
			and then the rest.
	Return : Size of the first part (elements less than pivot) */
	
	if (size <= 1)
		return 0;

	// Save the pivot in location 0
	swap(a, 0, pi, size);
	
	int p = a[0];	// Pivot
	int ls = 0;		// Left part size
	for (int i = 1; i < size; i++) {
		if (a[i] < p){
			ls++;
			swap(a, i, ls, size);
		}
	}
	
	// Put the pivot immediately after the left part
	swap(a, 0, ls, size);

	return ls;
}

/* Partition using two pointers */
int partition2(int a[], int size, int pi) {
/*	Input: An integer array a, it's size and locaiton of pivot
	Action: Orders the array so that all the elements less than
			the pivot comes first, then one copy of the pivot,
			and then the rest.
	Return : Size of the first part (elements less than pivot) */
	
	if (size <= 1)
		return 0;

	// Save the pivot in location 0
	swap(a, 0, pi, size);
	
	int p = a[0];	// Pivot
	int l = 1;
	int r = size-1;		

	while (1) {
		while (l < size && a[l] < p) 
			l++;
		while (r > 1 && a[r] >= p)
			r--;
		if (l < r)
			swap(a, l, r, size);
		else
			break;
	}
	
	swap(a, 0, l-1, size);

	return l-1;
}

void sort_quick(int a[], int size) {
/*	Input: 	An array a of size many integers
	Action: Sorts the data in a in non-decreasing order using quick sort */
	
	if (size <= 1)
		return;
	
	int pi	= rand() % size;	// Pivot Index
	int ls 	= partition2(a, size, pi);	

	sort_quick(a, ls);
	sort_quick(a + ls + 1, size - ls - 1);
}

/* Task 6. Implement the merge function for the Merge Sort */

// Merges two parts of a single array
void merge(int a[], int size, int lsize) {
/*	Input: 	An array a of size many integers
	Assumption : First lsize elements of a are sorted in non-dec order.		
				 Remaining elements of a are sorted in non-dec order.		
	Action: Merge the two parts so that all the elements are sorted */

	// Task 6 Solution

	// Memory for the temporary output array
	int *c = (int *) malloc(size * sizeof(int));
	if (c == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}
	int i = 0;
	int j = lsize;

	for(int m=0; m<size; m++){
		if(i >= lsize)
			c[m] = a[j++];
		else if(j >= size)
			c[m] = a[i++];
		else if(a[i] < a[j])
			c[m] = a[i++];
		else
			c[m] = a[j++];
	}

	for(i=0; i<size; i++){
		a[i] = c[i];
	}
	
	free(c);

	return;
}

void sort_merge(int a[], int size) {
/*	Input: 	An array a of size many integers
	Action: Sorts the data in a in non-decreasing order using merge sort */
	
	if (size <= 1)
		return;
	
	int half = size/2;
	sort_merge(a, half);
	sort_merge(a + half, size - half);
	merge(a, size, half);
	
	return;
}

int is_sorted(int a[], int size) {
/*	Input:	An array a and its size
	Output:	1 if a is sorted in non-decreasing order. 0 otherwise */

	for (int i = 0; i < size-1; i++) {
		if(a[i] > 	a[i+1])
			return 0;
	}

	return 1;
}

/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	Heap h; 
	init_heap(&h);
	srand(time(0));		// Seed the random number generator

	//Test helper functions
	h.size = 10;
	for (int i = 0; i < h.size; i++) {
		printf("Node: %2d:\t Level %d, Parent %2d, Left %2d, Right %2d\n",
			i, level(i), parent(i), left(i), right(i));
	}

	// Populates the heap with some data in correct order
	h.size = 10;
	for (int i = 0; i < h.size; i++) {
		h.data[i] = 99-i; //rand() % 90 + 10;
	}
	print_heap(&h);
	

	

	// Test Task 1: Heapify
	printf("\nTesting Task 1. Heapify\n");
	printf("=========================\n");
	// Populates the heap with some junk data (not in heap order)
	h.size =  10;
	for (int i = 0; i < h.size; i++) {
		h.data[i] = rand() % 50 + 10;
	}
	print_heap(&h);

	for (int i = parent(h.size-1); i >=0; i--) {
		heapify(&h, i);
		print_heap(&h);
	}
	
	
	// Test Task 2: Build Heap
	printf("\nTesting Task 2. Build Heap\n");
	printf("============================\n");
	// Populates the heap with some junk data (not in heap order)
	h.size =  10;
	for (int i = 0; i < h.size; i++) {
		h.data[i] = rand() % 50 + 10;
	}
	print_heap(&h);
	build_heap(&h);
	print_heap(&h);

	
	// Test Task 3: Insert
	printf("\nTesting Task 3: Insert\n");
	printf("========================\n");

	for(int i = 0; i < 6; i ++) {
		int data = rand() % 20 + 50;
		printf("Inserting %d\n", data);
		insert(&h, data);
		print_heap(&h);
	}

	
	// Test Task 4: Extract Max
	printf("\nTesting Task 4: Extract Max\n");
	printf("============================\n");

	while(1) {
		int max = extract_max(&h);
		if (max == INT_MIN) 
			break;
		printf("Max value is %d\n", max);
		print_heap(&h);
	}

	
	// Test Task 5: Heap Sort
	printf("\nTesting Task 5. Heap Sort\n");
	printf("===========================\n");
	// Populates the heap with some junk data (not in heap order)
	h.size =  10;
	for (int i = 0; i < h.size; i++) {
		h.data[i] = rand() % 50 + 10;
	}
	print_heap(&h);
	build_heap(&h);
	print_heap(&h);
	sort_heap(&h);
	print_heap(&h);
	for(int i=0; i<h.size; i++){
		printf("%d ", h.data[i]);
	}
	printf("\n");
	
	free_heap(&h);
	
	// Timing Different Sorting Algorithms
	clock_t start, end;
	int size = 100000;
	printf("\nTiming different sorting algorithms on an array of size %d.\n", size);
	printf("=============================================================\n");

	// Populates four arrays with the same unsorted data 
	int *data1 = (int*) malloc(size * sizeof(int));
	int *data2 = (int*) malloc(size * sizeof(int));
	int *data3 = (int*) malloc(size * sizeof(int));
	int *data4 = (int*) malloc(size * sizeof(int));
	if (data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}
	else {
		printf("Memory for an array of size %d allotted successfully.\n", size);
	}
	for (int i = 0; i < size; i++) {
		data1[i] = rand() % 1000;
		data2[i] = data1[i];
		data3[i] = data1[i];
		data4[i] = data1[i];
	}

	// Heap Sort data1

	// Wrap the first array in a heap	
	Heap wrap;
	wrap.size 		= size;
	wrap.capacity 	= size;
	wrap.data 		= data1;

	start = clock();
	build_heap(&wrap);
	sort_heap(&wrap);
	end = clock();

	if (is_sorted(data1, size)) 
		printf("Heap Sort: \t %9d clock cycles\n", end-start);
	else
		printf("Heap Sort: \t Failed\n");

	// Selectin Sort data2
	start = clock();
	sort_sel(data2, size);
	end = clock();
	
	if (is_sorted(data2, size)) 
		printf("Selection Sort:  %9d clock cycles\n", end-start);
	else
		printf("Selection Sort:  Failed\n");

	// Quick Sort data3
	start = clock();
	sort_quick(data3, size);
	end = clock();

	if (is_sorted(data3, size)) 
		printf("Quick Sort: \t %9d clock cycles\n", end-start);
	else
		printf("Quick Sort: \t Failed\n");

	// Test Task 6
	// Merge Sort data4
	start = clock();
	sort_merge(data4, size);
	end = clock();

	if (is_sorted(data4, size)) 
		printf("Merge Sort: \t %9d clock cycles\n", end-start);
	else
		printf("Merge Sort: \t Failed\n");


	free(data1);
	free(data2);
	free(data3);
	free(data4);

	

	return 0;
}


