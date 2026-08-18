
/*
	Name:		Bhogaraju Shanmukha Sri Krishna
	Roll No:	112201013
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Test 2 | 28/Mar/2024
	Tasks:		1 and 2 (5 points each)
	
	Aim: 		Implement Merge Sort and Quick Sort over Arrays
	Assume:		All data to be stored are of type int
	Instruction: Do not change the interface of any function
*/

#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc
#include <time.h>	// To seed random number generator

/* Helper Functions */
int is_sorted(int a[], int size) {
/*	Input:	An array a and its size
	Output:	1 if a is sorted in non-decreasing order. 0 otherwise */

	for (int i = 0; i < size-1; i++) {
		if(a[i] > 	a[i+1])
			return 0;
	}

	return 1;
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

/* For benchmarking (bubble sort) */
void sort_bubble(int a[], int size) {
/*	Input: 	An array a of size many integers
	Action: Sorts the data in a in non-decreasing order using bubble sort */
	
	int temp;
	for (int i = 0; i < size; i ++) 
		for (int j = 0; j < size - i -1; j ++)
			if (a[j] > a[j+1]) 
				swap(a, j, j+1, size);
	return; 
}


/* Task 1.	Merge Sort  (5 points)
	- 2 points for the merge() function 
	- 2 points for sort_merge() funciton which uses the above merge function
	- 1 point for good programming practices and readability
*/

/* Task 1a. Merge */
void merge(int a[], int lsize, int rsize) {
/*	Input: 	An array a of integers of size lsize + rsize
	Assumptions : 
		First lsize elements of a are sorted in non-dec order.		
		Next rsize elements of a are also sorted in non-dec order.		
		Total size of the array is lsize + rsize
	Action: Merge the two parts so that  entire array a is sorted
*/

	// Task 1a Solution
	// Temp array of size equal to size of array initialized
	int* c = malloc(sizeof(int) * (lsize + rsize));
	
	int i = 0;
	int j = lsize;
	
	// Filling the data in the temporary array
	for(int m = 0; m < (lsize + rsize); m++){
		// If i is out of bounds, assign from jth index
		if(i >= lsize){
			c[m] = a[j++];
		}
		
		// If j is out of bounds, assign from ith index
		else if(j >= rsize + lsize){
			c[m] = a[i++];
		}
		
		// assign the least among the two values 
		else if(a[i] < a[j])
			c[m] = a[i++];

		// a continuation of the above case
		else{
			c[m] = a[j++];
		}			
	}

	// Copying all the elements of temporary array into input array
	for(int i = 0; i < (lsize + rsize); i++)
		a[i] = c[i];

	// Freeing heap memory -> Good programming practice
	free(c);

	return;
}



/* Task 1b. Merge Sort */
void sort_merge(int a[], int size) {
/*	Input: 	An array a of size many integers
	Action: Sorts the data in a in non-decreasing order using merge sort */

	// A maybe nice implementation of merge sort using only two parameters

	// Task 1b. Solution
	// If the size of array is 1 or less, return
	if(size <= 1)
		return;

	// Else, just merge sort from 0th index to mid - 1 index (mid  = #values)
	// and then from mid'th to size - 1 index (size - mid = #values)   
	else{
		int mid = size/2;
		sort_merge(a, mid);
		sort_merge(a + mid, size - mid);
		merge(a, mid ,size - mid);
	}
	
	return;
}

/* Task 2.	Quick Sort  (5 points)
	- 2 points for the partition function 
	- 2 points for sort_quick() funciton which uses the above partition function
	- 1 point for good programming practices and readability
*/

/* Task 2a. Partition by Pivot */
int partition(int a[], int size, int pi) {
/*	Input: 
		a: 		an integer array a
		size:	number of elements in a
		pi:		index of the pivot (not its value) 
	Action: 
		Orders the array so that all the elements less than the pivot comes
		first, then one copy of the pivot, and then the rest.
	Return : Size of the first part (elements less than pivot)
*/
	// Swapped 0th and pith elements
	swap(a, 0, pi, size);

	// left is the size of array <= pivot
	// right is the size of array > pivot
	int left = 0;
	int right = size - 1;

	// iterating through array and finding the exact index of pivot
	while(left < right){
		while(a[left] <= a[0])
			left++;
		while(a[right] > a[0])
			right--;

		if(left < right)
			swap(a, left, right, size);
	}
	// right is the correct index for pivot
	// swapping inorder to place pivot correctly
	swap(a, right, pi, size);

	// returns right -> correct position for pivot
	return right;
	// Task 2a. Solution
	// return 0; // You may have to edit this
}

/* Task 2b. Quick Sort */
void sort_quick(int a[], int size) {
/*	Input: 	An array a of size many integers
	Action: Sorts the data in a in non-decreasing order using quick sort */
	
	// Task 2b. Solution

	// Another maybe nice implementation of quick sort using 2 inputs

	// Base case for recursion
	if(size <= 1)
		return;
	
	// taking pivot = 0 (start index)
	int pi = 0;

	// finding pivot position and recursively sorting the array
	int q = partition(a, size, pi);
	sort_quick(a, q);
	sort_quick(a + q + 1, size - q - 1);
}

int main()
{
	// Timing Different Sorting Algorithms
	clock_t start, end;
	int size = 10000;
	printf("\nTiming different sorting algorithms on an array of size %d.\n", size);
	printf("=============================================================\n");
	srand(time(0));		// Seed the random number generator

	// Populates three arrays with the same unsorted data 
	int *data1 = (int*) malloc(size * sizeof(int));
	int *data2 = (int*) malloc(size * sizeof(int));
	int *data3 = (int*) malloc(size * sizeof(int));
	if (data1 == NULL || data2 == NULL || data3 == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}
	else {
		printf("Memory for an array of size %d allotted successfully.\n", size);
	}
	for (int i = 0; i < size; i++) {
		data1[i] = rand();
		data2[i] = data1[i];
		data3[i] = data1[i];
	}

	// Time Bubble Sort
	start = clock();
	sort_bubble(data1, size);
	end = clock();

	if (is_sorted(data1, size)) 
		printf("Bubble Sort Successfull: \t %9ld clock cycles\n", end-start);
	else
		printf("Bubble Sort: \t Failed\n");

	// Test Task 1. Merge Sort
	start = clock();
	sort_merge(data2, size);
	end = clock();

	if (is_sorted(data2, size)) 
		printf("Merge Sort Successfull: \t %9ld clock cycles\n", end-start);
	else
		printf("Merge Sort: \t Failed\n");

	// for(int i=0; i<size; i++){
	// 	printf("%d ", data2[i]);
	// }
	// printf("\n");
	// Test Task 2. Quick Sort
	start = clock();
	sort_quick(data3, size);
	end = clock();

	if (is_sorted(data3, size)) 
		printf("Quick Sort Successfull: \t %9ld clock cycles\n", end-start);
	else
		printf("Quick Sort: \t Failed\n");

	// Free the extra memory (good programming practice)
	free(data1);
	free(data2);
	free(data3);

	return 0;
}
