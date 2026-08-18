#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXKEYVALUE 1024 // keys range from 0 to MAXKEYVALUE - 1
#define TABLESIZE 17 //number of entries in the hash table, chosen to be prime for double hashing
#define BIGMAXKEYVALUE 100000
#define BIGTABLESIZE 1031

int printprobes = 1; // flag that can be set to zero to suppress printing of probe locations

typedef struct
{
    int type;   // 0: linear probing, 1: quadratic probing, 2: double hashing
    
    int size;   // at most 20;
                // also, for double hashing, size is a prime number
        
    int *entry;

    int probecount; // total number of probes carried out for insertion operations (whether successful or not)
} hashtable;

void init_hashtable(hashtable *ht, int n, int t)
{
    int i;
    ht->size = n;
    ht->type = t;
    ht->probecount = 0;
    ht->entry = (int *) malloc(sizeof(int) * n);
    for(i = 0; i < n; i++)
    {
        ht->entry[i] = -1; // unoccupied slot
    }
}

void destroy_hashtable(hashtable *ht)
{
    free(ht->entry);
}

int hash(hashtable *ht, int key, int i)
{
    /* Task 5: Implement the hashing function according to the type of the table ht. The function returns the
        position of the table to be probed for the i-th time while inserting key.
        - If type is 0, perform linear probing.
        - If type is 1, perform quadratic probing.
        - If type is 2, perform double hashing by choosing the first hash function as (key mod tablesize), and
        the second hash function as 1 + (key mod (tablesize - 1)). Recall that tablesize can be assumed to be
        a prime number in this case. */

    int m = ht->size;
    int h1 = key % m;

    if (ht->type == 0) // Linear Probing
    {
        return (h1 + i) % m;
    }
    else if (ht->type == 1) // Quadratic Probing
    {
        return (h1 + i * i) % m;
    }
    else if (ht->type == 2) // Double Hashing
    {
        // h2 must be relatively prime to m. 
        // Given m is prime, h2 = 1 + (key % (m-1)) works well.
        int h2 = 1 + (key % (m - 1));
        return (h1 + i * h2) % m;
    }
    return 0;
}

int insert_hashtable(hashtable *ht, int key)
{
    /* Task 6: Insert key into the table ht by following the probing sequence that is given by the function hash(). Return 0 if insert fails because a valid position cannot be found for inserting key. Otherwise return the number of probes that was used in the process of insertion. You should increment the variable ht->probecount by the number of probes that were used. The function should print the locations that were probed during the process if the global variable printprobes is set to 1, and should not print this information otherwise.*/

    for (int i = 0; i < ht->size; i++)
    {
        int pos = hash(ht, key, i);

        if (printprobes)
        {
            printf("%d ", pos);
        }

        if (ht->entry[pos] == -1) // Found an empty slot
        {
            ht->entry[pos] = key;
            int probesUsed = i + 1;
            ht->probecount += probesUsed;
            return probesUsed;
        }
    }

    // If loop finishes, no valid position was found (table full or sequence failed)
    ht->probecount += ht->size;
    return 0;
}

int search_hashtable(hashtable *ht, int key)
{
    /* Task 7: Search the table ht for key. Return 1 if the key is found in the table, and 0 otherwise. */
    int i;
    for (i = 0; i < ht->size; i++)
    {
        int pos = hash(ht, key, i);

        if (ht->entry[pos] == key)
        {
            return 1; // Key found
        }
        
        if (ht->entry[pos] == -1)
        {
            return 0; // Optimization: Stop if we hit an empty slot
        }
    }
    return 0; // Key not found after checking all possible probe locations
}

void display_hashtable(hashtable *ht)
{
    int i;
    printf("\n");
    for(i = 0; i < ht->size; i++)
    {
        printf("%2d: ", i);
        if(ht->entry[i] == -1)
            printf("*\n");
        else
            printf("%d\n", ht->entry[i]);
    }
}

int main()
{
    int num, i, count, countlin, countquad, countdoub;
    float avglin, avgquad, avgdoub, cap;
    hashtable table;
    hashtable tablin, tabquad, tabdoub;

    printf("Enter hash table type: ");
    scanf("%d", &num);

    if(num != 2)
        init_hashtable(&table, TABLESIZE, num);
    else
        init_hashtable(&table, TABLESIZE, num);

    srand(time(NULL)); // Initializing random number generator

    while(1)
    {
        printf("\nTotal probes so far: %d", table.probecount);
        printf("\nEnter key (0 to randomly generate new key, -1 to exit): ");
        scanf("%d", &num);

        if(num < 0)
            break;
        if(num == 0)
        {
            do
            {
                num = rand() % MAXKEYVALUE;
            }
            while(search_hashtable(&table, num) != 0);
        }
        else if(num >= MAXKEYVALUE)
        {
            printf("\nKey must be less than %d.", MAXKEYVALUE);
            continue;
        }
        else if(search_hashtable(&table, num) == 1)
        {
            printf("\nKey %d found in table.", num);
            continue;
        }
        printf("\nInserting key %d...\n", num);
        i = insert_hashtable(&table, num);
		if(i == 0)
            printf("\nCannot insert - table full.\n");
        else
            printf("\n Number of probes used: %d\n", i);
        display_hashtable(&table);
    }
    destroy_hashtable(&table);

    printf("Number of random sequences of keys to generate: ");
    scanf("%d", &num);

    if(num <= 0)
        return 0;
    
    printf("Count probes only after this load factor is achieved (enter value between 0 and 1): ");
    scanf("%f", &cap);

    avglin = 0.0;
    avgquad = 0.0;
    avgdoub = 0.0;
    count = -1;
    countlin = -1;
    countquad = -1;
    countdoub = -1;

    printprobes = 0; //Suppress printing of probe locations

    for(i = 0; i < num; i++)
    {
        int j;
        init_hashtable(&tablin, BIGTABLESIZE, 0);
        init_hashtable(&tabquad, BIGTABLESIZE, 1);
        init_hashtable(&tabdoub, BIGTABLESIZE, 2);
        for(j = 0; j < BIGTABLESIZE; j++)
        {       
            int r; 
            do
            {
                r = rand() % BIGMAXKEYVALUE;
            }
            while(search_hashtable(&tabdoub, r) != 0);
            insert_hashtable(&tablin, r);
            insert_hashtable(&tabquad, r);
            insert_hashtable(&tabdoub, r);
            if(count == -1 && (float) j/BIGTABLESIZE >= cap)
            {
                count = j;
                countlin = tablin.probecount;
                countquad = tabquad.probecount;
                countdoub = tabdoub.probecount;
            }
        }
        avglin += tablin.probecount - countlin;
        avgquad += tabquad.probecount - countquad;
        avgdoub += tabdoub.probecount - countdoub;
        destroy_hashtable(&tablin);
        destroy_hashtable(&tabquad);
        destroy_hashtable(&tabdoub);
    }
    avglin /= num;
    avgquad /= num;
    avgdoub /= num;

    printf("\nAverage number of probes\n------------------------\nLinear probing: \t%.2f\nQuadratic probing: \t%.2f\nDouble hashing: \t%.2f\n", avglin, avgquad, avgdoub);
}