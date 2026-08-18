#include <stdio.h>
#define MAXDISKS 10

int peg[3][MAXDISKS]; // Global array to call the disks in the peg
int len[3];	// Global array to store the number of disks in each peg.
int num_moves = 0; // Global variable to store the number of moves done

void printarrays()
{
/* Helper functions to print the peg arrays as disks on the peg. */
	int i, j, max;
	max = len[0];
	for(i = 1; i < 3; i++)
	{
		if(len[i] > max)
			max = len[i];
	}
	printf("\n");
	for(i = 0; i <= max; i++)
	{
		for(j = 0; j < 3; j++)
		{
			if(max - i < len[j])
			{
				printf("%4d", peg[j][max - i]);
			}
			else
			{
				printf("    ");
			}
		}
		printf("\n");
	}
	printf("  --  --  --\n");
	printf("%4s%4s%4s\n", "P1", "P2", "P3");
}

void hanoi(int *base0, int *base1, int *base2, int target)
/* Task 6: The three pointers base0, base1, base2 point to the bottom most
	disk in the respective peg. The function should follow the rules of
	Towers of Hanoi and reach a configuration in which all the disks are
	on the target peg. Note that the starting configuration can be arbitrary.
	That is the disks may be distributed on multiple pegs, but it will
	obey Rule 2 below.

	Rules of the game:
	1.	Each valid move consists of taking the top most disk from any of
		the three pegs and placing it as the top most disk of another peg.
	2.	At no point should a larger disk be on top of a smaller disk.

	In addition, increment the global variable num_moves each time you make
	a move so that the total number of moves taken can be computed.
*/
{
    int max = *base0;
    int src = 0;

    if(*base1 > max){
        max = *base1;
        src = 1;
    }
    if(*base2 > max){
        max = *base2;
        src = 2;
    }

    // no disks left
    if(max == 0)
        return;

    // if largest disk already on target
    if(src == target){
        if(src == 0) hanoi(base0+1, base1, base2, target);
        if(src == 1) hanoi(base0, base1+1, base2, target);
        if(src == 2) hanoi(base0, base1, base2+1, target);
        return;
    }

    // find auxiliary peg
    int aux = 3 - src - target;

    // move smaller disks away
    if(src == 0) hanoi(base0+1, base1, base2, aux);
    if(src == 1) hanoi(base0, base1+1, base2, aux);
    if(src == 2) hanoi(base0, base1, base2+1, aux);

    // move largest disk
    int disk = peg[src][len[src]-1];

    peg[target][len[target]] = disk;
    len[target]++;

    peg[src][len[src]-1] = 0;
    len[src]--;

    num_moves++;
    printarrays();

    // move smaller disks onto target
    if(src == 0) hanoi(base0+1, base1, base2, target);
    if(src == 1) hanoi(base0, base1+1, base2, target);
    if(src == 2) hanoi(base0, base1, base2+1, target);
}

int main()
{
	int i, j;
	len[0] = len[1] = len[2] = 0;
	printf("Enter initial configuration below.\n");
	printf("Enter the disks in each peg as a list of descending numbers terminated by 0\n");
	for(j = 0; j < 3; j++)
	{
		printf("Peg-%d : ", j+1);
		scanf("%d",&i);
		while(i != 0)
		{
			peg[j][len[j]] = i;
			len[j]++;
			scanf("%d",&i);
		}
	}
	printarrays();
	hanoi(peg[0], peg[1], peg[2], 2);
	printf("\n Total number of moves = %d\n", num_moves);
}
