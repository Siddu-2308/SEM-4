/*
	Course:		CS2130 DSA Lab 
	Semester:	2026 Jan-Apr
	Lab No:		Test 2
	File: 		1
	Aim: 		Implement the QuickSort algorithm on an array of integers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int a[], int p, int q)
{
	/* Task 1 (4 marks): Implement the Quick Sort Partition function.
		The subarray a[p]..a[q-1] has to be partitioned taking the value x = a[q-1] as pivot.
		That is, the function has to modify the array and return a position b in the subarray
		such that every element in a[p]..a[b-1] is less than or equal to x, a[b] is equal to
		x and every element in a[b+1]..a[q-1] is greater than x.
	*/

	return 0;
}

void quicksort(int a[], int p, int q)
{
	/* 	Task 2 (4 marks): Implement Quick Sort on array. 
		This function should sort the subarray from a[p] to a[q-1].
	*/

}

int main()
{
	int *a, len, i, j;

	printf("Enter length of array: ");
	scanf("%d", &len);

	a = (int *) malloc(sizeof(int) * len);

	if(a == NULL)
	{
		printf("Memory allocation error.\n");
		return -1;
	}

	srand(time(NULL));

	for (i = 0; i < len; i++)
	{
		a[i] = rand() % (4 * len);
	}	

	printf("\nThe unsorted array:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	j = partition(a, 0, len);
	printf("\nTask 1 (4 marks): Array after calling the partition function once:\n");
	for(i = 0; i < len; i++)
	{
		if(i == j)
			printf("|");
		printf("%d", a[i]);
		if(i == j)
			printf("|");
		printf(" ");
	}

	printf("\n");

	quicksort(a, 0, len);

	printf("\nTask 2 (4 marks) Array sorted using Quick Sort:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	free(a);
}