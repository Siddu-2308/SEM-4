#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

void countsort(char *str[], int n, int index) {
	/* Task 1: Implement Counting Sort to sort an input array str of strings
	 * based on the character at a given position (index).  The strings are 
	 * assumed to contain only characters 'a' to 'z' and the null character '\0' 
	 * (ASCII value 0)
	 */
    int count[27] = {0};  //0-26 indices
    for(int i = 0; i < n; i++)
    {   int key;
        if(str[i][index] == '\0')
            key = 0;
        else
            key = str[i][index] - 'a' + 1;
        count[key]++;
    }
    for(int i=1;i<27;i++){
        count[i]=count[i-1]+count[i];
    }

    char *output[n];
    for(int i = n-1; i >= 0; i--)
    {
        int key;

        if(str[i][index] == '\0')
            key = 0;
        else
            key = str[i][index] - 'a' + 1;

        output[--count[key]] = str[i];
        
    }

    for(int i = 0; i < n; i++)
    {
        str[i] = output[i];
    }
}

void radix_sort(char *str[], int n, int len)
{
	/*Task 2: Implement Radix Sort to sort an array str of strings in the
	 * lexicographic order. Each string in the array str is a character array
	 * of length len and consists of the characters 'a' to 'z' and the null
	 * character ('\0' or 0). You can assume that in each string in str, all
	 * the characters after the first null character will also be null
	 * characters. Also, the character at position len of each string is the
	 * null character. Details of implementation: Call the countsort function
	 * implemented above on the array str len times, with the character
	 * position to sort on varying from len-2 down to 0.*/
    for(int i = len-2; i >= 0; i--)
    {
        countsort(str, n, i);
    }

}

int main()
{
    int i, j, k, n, len;
    char **str;

	printf("Enter number of strings: ");
	scanf("%d", &n);
	printf("Enter the maximum length of a string: ");
	scanf("%d",&len);

    len = len + 1;

	str = (char **) malloc(sizeof(char *) * n);

    for(i = 0; i < n; i++)
    {
        str[i] = (char *) malloc(sizeof(char) * len);
    }

	srand(time(NULL)); // Initializing random number generator 

	for (i = 0; i < n; i++) // Populates the array str with random strings
	{
        for(j = 0; j < len - 1; j++)
        {
            do
            {
    		    str[i][j] = (rand() % 27);
            }
            while(j == 0 && str[i][j] == 0);
            if(str[i][j] == 0)
            {
                for(k = j + 1; k < len; k++)
                {
                    str[i][k] = 0;
                }
                break;
            }
            else
            {
                str[i][j] = 'a' + str[i][j] - 1;
            }
        }
        if(j == len - 1)
        {
            str[i][j] = 0;
        }
	}

	printf("\nThe unsorted array:\n");
	for(i = 0; i < n; i++)
	{
		printf("%s\n", str[i]);
	}
	printf("\n");

    printf("Enter position to sort on: ");
    scanf("%d", &k);
    countsort(str, n, k);

    printf("\nThe array sorted on position %d:\n", k);
	for(i = 0; i < n; i++)
	{
		printf("%s\n", str[i]);
	}
	printf("\n");

    radix_sort(str, n, len);
    printf("\nThe fully sorted array:\n");
	for(i = 0; i < n; i++)
	{
		printf("%s\n", str[i]);
	}
	printf("\n");

    for(i = 0; i < n; i++)
    {
        free(str[i]);
    }

    free(str);
}
