/*
	Name:		<full name>
	Roll No:	<roll number>
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 8
	Tasks:		Quick Sort
*/

#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc
#include <time.h>	// To seed random number generator
#include <limits.h>	// For INT_MIN

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

