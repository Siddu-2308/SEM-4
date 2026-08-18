/*
	Course:		CS2024 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab No:		1
	Aim: 		Simple data analysis on a list of non-zero integers. 
	Instructions:
		1.	Read a list of numbers from the terminal and store it in an array.
		2.	You can also read the list by redirecting a file data.txt to the input 
		3.	Complete a set of data analytic tasks on these numbers.
*/

//for task2
#include <stdio.h>
#include <math.h> 
#define N 100		// The maximum amount of data the program will handle

int helper(int arr[], int size, int num){ //helper function for returning the count of each element in array
	int count = 0;
	for(int i=0; i<size; i++){
		if(arr[i] == num)
			count++;
	}
	return count;
}



int main()
{
	int a[N];
	int i, len, temp;

	for(i = 0; i < N; i++)
	{
		scanf("%d", &temp);
		if(temp == 0){
			len = i;
			break;}
		else{
			a[i] = temp;}
	}

	/* Task 1. Modify the loop below to print the numbers in reverse order
	*/
	for(i = 0; i < len; i++)
		printf("%d\n", a[i]);
	
	printf("\nTask1\n");
	for(i = len-1; i >=0; i--) //Task1: changed the values in the for loop 
		printf("%d\n", a[i]);

	/* Task 2. Find some cumulative statistics of the data
		a) 	Average 
		b)	Standard Deviation
		c)	Minimum value
		d) 	Maximum value
	*/

	printf("\nTask2\n");
	int sum = 0;
	for(i = 0; i<len; i++){
		sum += a[i]; //finding the sum of all elements
	}
	
	
	float avg = sum/len; // average
	printf("Average: %f\n", avg);
	
	int d[N];
	int sq_sum = 0;
	for(i=0; i<len; i++){
		d[i] = (a[i] - avg) * (a[i] - avg);
		sq_sum += d[i]; //added all squared values
	}

	float sigma_square = sq_sum/len; //variance is obtained
	double x;
	x = sqrt(sigma_square); //square root of variance = Standard deviation


	
	//printf("Variance: %f\n", sigma_square);
	printf("SD: %lf\n", x); //Standard deviation


	int min = a[0];
	for(i=0; i<len; i++){
		if(a[i] < min){
			min = a[i]; //algorithm for finding minimum value
		}
	}

	int max = a[0];
	for(i=0; i<len; i++){
		if(a[i] > max){
			max = a[i]; //algorithm for finding maximum value
		}
	}

	printf("Minimum: %d\nMaximum: %d\n", min, max);


	printf("\nTask3\n");
	/* Task 3. Generate a histogram of the data in the following form
		01 - 10 : ####
		11 - 20 : ########
		...
		91 -100 : ##
		
		Here the number of #'s after i-j denote the number of numbers in the
		list which are between i and j (i and j included)
	*/
	int c[] = {0,0,0,0,0,0,0,0,0,0}; //here, i am storing the counts for respective class intervals in an array
	for(i=0; i<len; i++){
		if(a[i] >= 1 && a[i] <= 10)
			c[0]++;
		else if(a[i] >= 11 && a[i] <= 20)
			c[1]++;
		else if(a[i] >= 21 && a[i] <= 30)
			c[2]++;
		else if(a[i] >= 31 && a[i] <= 40)
			c[3]++;
		else if(a[i] >= 41 && a[i] <= 50)
			c[4]++;
		else if(a[i] >= 51 && a[i] <= 60)
			c[5]++;
		else if(a[i] >= 61 && a[i] <= 70)
			c[6]++;
		else if(a[i] >= 71 && a[i] <= 80)
			c[7]++;
		else if(a[i] >= 81 && a[i] <= 90)
			c[8]++;
		else if(a[i] >= 91 && a[i] <= 100)
			c[9]++;
	}


	printf("01-10: "); //this does the formatted printing
	while(c[0]--){
		printf("#");
	}
	printf("\n");
	
	printf("11-20: ");
	while(c[1]--){
		printf("#");
	}
	printf("\n");

	printf("21-30: ");
	while(c[2]--){
		printf("#");
	}
	printf("\n");

	printf("31-40: ");
	while(c[3]--){
		printf("#");
	}
	printf("\n");
	
	printf("41-50: ");
	while(c[4]--){
		printf("#");
	}
	printf("\n");

	printf("51-60: ");
	while(c[5]--){
		printf("#");
	}
	printf("\n");

	printf("61-70: ");
	while(c[6]--){
		printf("#");
	}
	printf("\n");

	printf("71-80: ");
	while(c[7]--){
		printf("#");
	}
	printf("\n");

	printf("81-90: ");
	while(c[8]--){
		printf("#");
	}
	printf("\n");

	printf("91-100: ");
	while(c[9]--){
		printf("#");
	}
	printf("\n");

	
	printf("\nTask4\n");
	/* Task 4. Search type tasks
		a) 	Find the number of times the maximum value repeats in the list
		b)	Find the value which repeats the maximum number of times in the list
			(this is called the mode of the list)
	*/

	printf("No.of times max occurs: %d\n", helper(a, N, max));
	printf("No.of times min occurs: %d\n", helper(a, N, min)); //please refer to the helper above for algorithm

	int count[N];
	for(i=0; i<len; i++){ //storing the count of each element(not class interval) in this array
		count[i] = helper(a, len, a[i]);
	}

	int help = count[0];
	for(i=0; i<len; i++){
		if(count[i] > help)
			help = count[i]; //help is the maximum count
	}

	int index =0;
	for(i=0; i<len; i++){
		if(count[i] == help) //this gives the index of the maxcount
			index = i;
			break;
	}
	printf("Mode: %d", a[index]); //a[index] is the mode:max count element


	printf("\nTask5\n");
	/* Task 5. Sorting
		a) Sort the array in the non-decreasing order 
		b) Print the array in sorted order*/

	for(i=0; i<len; i++){
		int j = i-1;
		while(j >= 0 && a[j+1] < a[j]){
			int temp = a[j+1];
			a[j+1] = a[j];
			a[j] = temp;
			j--;
		}
	}

	//used insertion sort for sorting the array

	for(i=0; i<len; i++){
		printf("%d\n", a[i]); //print each element
	}

	printf("\nTask6\n");
	/* Task 6.  Uniqueness
		a) Create a new array which contains all elements of the first 
				but without any repetition.
		b) Print this array
	*/
	int arr1[N];
	for(i=0; i<len; i++){
		arr1[i] = -1; //each element of arr1 is initialized with -1
	}

	//a is sorted in the above task
	for(i=0; i<len; i++){
		if(a[i] < a[i+1]){
			arr1[i] = a[i]; //a[i] == a[i+1] means that there is a repetition
		}
	}

	for(i=0; i<len; i++){
		if(arr1[i] != -1) //-1 is represents repetition hence not printed. all others are unique elements
			{
				printf("%d\n", arr1[i]);
			}
	}


	return 0;
}
