/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Use:		Header file for quick-sort.c
*/

// A protection to ensure that a header file is not included multiple times.

#ifndef QuickSort_H
#define QuickSort_H

int is_sorted(int a[], int size);
/*	Input:	An array a and its size
	Output:	1 if a is sorted in non-decreasing order. 0 otherwise */

void swap(int a[], int i, int j, int size);
/*	Input: 	An array a; two indices i and j; size of the array
	Action: Swaps the data values in locations i and j
	Error: 	Prints "Error in swap: Index out of range" to stderr 
			if i or j is outside the heap 
	Note:	Checking for the index overflow is a good bug catcher */

/* Quick Sort */

/* Partition using one pointer */
int partition1(int a[], int size, int pi);
/*	Input: An integer array a, it's size and locaiton of pivot
	Action: Orders the array so that all the elements less than
			the pivot comes first, then one copy of the pivot,
			and then the rest.
	Return : Size of the first part (elements less than pivot) */

/* Partition using two pointers */
int partition2(int a[], int size, int pi);
/*	Input: An integer array a, it's size and locaiton of pivot
	Action: Orders the array so that all the elements less than
			the pivot comes first, then one copy of the pivot,
			and then the rest.
	Return : Size of the first part (elements less than pivot) */
	
void sort_quick(int a[], int size);
/*	Input: 	An array a of size many integers
	Action: Sorts the data in a in non-decreasing order using quick sort */

#endif
