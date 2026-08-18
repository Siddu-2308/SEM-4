#include <stdio.h>

int arr[100]; // An array that will store a binary string
int len;
int count;

void printarray()
{
	/* Prints the current contents of the global array arr */

    int i;
	int flag = 0;
    for(i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
	printf(" : {");

    for(i = 0; i < len; i++)
    {
        if(arr[i] == 1) 
		{
			if(flag)
				printf(", ");
			else
				flag = 1;
			printf("%d", i+1);
		}
    }	
	printf("}\n");
    count++;
}

/* The final aim of this function is to print all bit stings of length len
 * by recursively generating all bit patterns of smaller lengths. Note that
 * these strings are a representation of all subsets of {1,..., len} */ 

void printbinstrings(int p, int q)
{
	/* Task 4: Print all 2^{q-p} binary strings that can be obtained from the global
	 * 0-1 array arr by replacing arr[p] .. arr[q-1] with all possible (q-p)-length
	 * bitstrings. */
    if (p==q) { 
            printarray();
            return;
    }

    int first = p; // This targets the current bit we are deciding

    arr[first] = 0;
    printbinstrings(p+1, q ); // Move to the next bit (the one to the left)

    arr[first] = 1;
    printbinstrings(p+1, q); // Move to the next bit (the one to the left)
}

/* The final aim of this function is to print all bit stings of length len
 * containing exactly num 1-bits recursively. Note that these strings are
 * a representation of num-sized subsets of the set {1, ..., len}. */

void printbinstringsnum(int p, int q, int num)
{
	/* Task 5: Print all binary strings that can be obtained from the global
	 * 0-1 array arr of length len (global variable) by replacing arr[p] ..
	 * arr[q-1] with all possible (q-p)-length binary strings with exactly num
	 * 1-bits. */

	 if(p==q){
	     if (num==0){
	         printarray();
	         return;
	     }
	     else{
	         return;
	     }
	 }
	 
	 int first = p; // This targets the current bit we are deciding

     arr[first] = 0;
     printbinstringsnum(p+1, q,num ); // Move to the next bit (the one to the left)

     arr[first] = 1;
     printbinstringsnum(p+1, q ,num-1); // Move to the next bit (the one to the left)

}

int main()
{
    int i;
    printf("Enter length of binary string: ");
    scanf("%d", &len);
    count = 0;
    for(i = 0; i < len; i++) //Initializing the array a to the all-zeroes binary string
    {
        arr[i] = 0;
    }
	printf("\n");
    printbinstrings(0, len);
    printf("Total number of bitstrings generated: %d\n", count);

    count = 0;
    printf("Enter number of 1-bits: ");
    scanf("%d", &i);
	printf("\n");
    printbinstringsnum(0, len, i);
    printf("Total number of bitstrings generated: %d\n", count);
}
