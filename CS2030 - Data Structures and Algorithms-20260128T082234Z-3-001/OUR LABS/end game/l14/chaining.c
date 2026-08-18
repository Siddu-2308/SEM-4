#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXKEYBITS 10 // keys range from 0 to 2ˆMAXKEYBITS - 1
#define TABLESIZE 16 //number of entries in the hash table
#define P 1031// a prime number larger that 2ˆMAXKEYBITS

struct node;
struct node {	
	int value;
	struct node *next;
};
typedef struct node Node;

typedef struct {
	Node *head;
} List;

typedef struct
{
    int type;   // 0: division hash, 1: mult hash, 2: universal hash
    
    int size;   // at most 20 for convenience of displaying the table
                // for mult hash: must be a power of 2
    
    int a, b;   // for mult hash: a chosen from 0 to 2ˆ{MAXKEYBITS} - 1, b is set to log_2(size)
                // for universal hash: a, b randomly chosen from Z_P - {0} and Z_P;
    
    List *entry;
} hashtable;

void init_LL(List *l)
{
	/*Initializes an empty list.*/

	l->head = NULL;
}

void add_LL(List *l, int val)
{
	/*Adds a node with value "val" to the head of the list l.*/

	Node *nod = (Node *) malloc(sizeof(Node));
	nod->value = val;
	nod->next = l->head;
	l->head = nod;
}

Node *search_LL(List *l, int searchkey)
{
    /* Returns the pointer to a node containing the value searchkey, if such a node exists, and NULL
        otherwise. */
    Node *nod;
    nod = l->head;
    while(nod != NULL && nod->value != searchkey)
        nod = nod->next;
    return nod;
}

void print_LL(List *l)
{
    /* Prints the contents of the linked list l. */
    
    Node *nod;
    nod = l->head;
    while(nod != NULL)
    {
        if(nod != l->head)
            printf(",");
        printf(" %d", nod->value);
        nod = nod->next;
    }
}
void destroy_LL(List *l)
{
	/*Frees the space allocated for the list l.*/

	Node *temp;
	temp = l->head;
	while(temp != NULL)
	{
		l->head = l->head->next;
		free(temp);
		temp = l->head;
	}
}

void init_hashtable(hashtable *ht, int n, int t)
{
    /*Task 1: Initialize the hash table ht according to its type. Refer to the definition of struct hashtable to understand how to initialize the fields a and b of ht. */

    int i;
    ht->size = n;
    ht->type = t;
    ht->entry = (List *) malloc(sizeof(List) * n);
    for(i = 0; i < n; i++)
    {
        init_LL(&ht->entry[i]);
    }
    if(t == 1)
    {
        // ht->size guaranteed to be power of 2
        // A recommended value between 0 and 1 that is to be multiplied with the key is (sqrt(5)-1)/2
        /* Add your code here */
        // b = log2(size). For size 16, b = 4.
        ht->b = (int)(log(n) / log(2));
        
        // Use the golden ratio A = (sqrt(5)-1)/2 approx 0.6180339887
        // a = A * 2^MAXKEYBITS
        double A = (sqrt(5.0) - 1.0) / 2.0;
        ht->a = (int)(A * (1 << MAXKEYBITS));
    }
    else if(t == 2)
    {
        /* Add your code here*/
        // Select ht->a and ht->b randomly
        ht->a = (rand() % (P - 1)) + 1;
        ht->b = rand() % P;
    }
}

void destroy_hashtable(hashtable *ht)
{
    int i;
    for(i = 0; i < ht->size; i++)
    {
        destroy_LL(&ht->entry[i]);
    }
    free(ht->entry);
}

int hash(hashtable *ht, int key)
{
    /*Task 2: Implement the hash function for the hash table ht.
    
    - If the type of the table is 0, then perform a division hash by returning the key modulo the table size.
    - If the type of the table is 1, then perform a multiplication hash by returning the MAXKEYBITS most significant bits of the fractional part of key * (ht->a / 2ˆ{MAXKEYBITS}), where ht->a is a fixed number between 0 and 2ˆ{MAXKEYBITS} - 1 that is chosen during initialization of the hash table.
    - If the type of the table is 2, then return the value that key is mapped to by the universal hashing function given by (ht->a, ht->b), which is chosen during initialization, when ht->a and ht->b are chosen at random. Recall that P is a prime number that is larger than the largest possible key. */
    if (ht->type == 0) // Division Method
    {
        return key % ht->size;
    }
    else if (ht->type == 1) // Multiplication Method
    {
        /* 1. Multiply key by a.
           2. Extract the fractional part using modulo 2^MAXKEYBITS (bitmasking).
           3. Shift right to get the 'b' most significant bits of that fractional part.
        */
        unsigned long long fraction = (unsigned long long)key * ht->a;
        int mask = (1 << MAXKEYBITS) - 1;
        return (int)((fraction & mask) >> (MAXKEYBITS - ht->b));
    }
    else if (ht->type == 2) // Universal Hashing
    {
        // Formula: ((ak + b) mod P) mod m
        return (int)((( (long long)ht->a * key + ht->b) % P) % ht->size);
    }
    return 0;
}

void insert_hashtable(hashtable *ht, int key)
{
    /* Task 3: Write a function that inserts the value key into the hash table ht, assuming that key is not
        already present in the table. */
    int index = hash(ht, key);
    add_LL(&ht->entry[index], key);
}

int search_hashtable(hashtable *ht, int key)
{
    /* Task 4: Write a function that returns 0 if the value key is not stored in the hash table ht, and 1 if it is stored in the table. */
    int index = hash(ht, key);
    if (search_LL(&ht->entry[index], key) != NULL) {
        return 1;
    }
    return 0;// To be changed
}

void display_hashtable(hashtable *ht)
{
    int i;
    for(i = 0; i < ht->size; i++)
    {
        printf("\n%2d: ", i);
        print_LL(&ht->entry[i]);
    }
}

int main()
{
    int num;
    hashtable table;

    printf("Enter hash table type: ");
    scanf("%d", &num);
    srand(time(NULL)); // Initializing random number generator

    init_hashtable(&table, TABLESIZE, num);

    while(1)
    {
        printf("\nEnter key (0 to randomly generate, -1 to exit): ");
        scanf("%d", &num);

        if(num < 0)
            break;
        if(num == 0)
        {
            do
            {
                num = rand() % (1<<MAXKEYBITS);
            }
            while(search_hashtable(&table, num) != 0);
        }
        else if(num >= (1 << MAXKEYBITS))
        {
            printf("\nKey must be less than %d.", 1 << MAXKEYBITS);
            continue;
        }
        else if(search_hashtable(&table, num) == 1)
        {
            printf("\nKey %d already in table.", num);
            continue;
        }
        printf("\nInserting key %d...\n", num);
        
		insert_hashtable(&table, num);

        display_hashtable(&table);
    }
    destroy_hashtable(&table);
}