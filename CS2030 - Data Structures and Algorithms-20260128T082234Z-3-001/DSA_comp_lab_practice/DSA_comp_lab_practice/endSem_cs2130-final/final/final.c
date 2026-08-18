/*
	Name:		Bhogaraju Shanmukha Sri Krishna
	Roll No:	112201013
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		End-Sem | 02/May/2024
       Tasks:		1 (a,b,c), 2(a[i,ii,iii], b), 3(a,b), 4 (10)
       Marks: 1(a,b,c) : 6+2+4 = 12
              2(a[i, ii, iii],b): (1+2+3)+8 = 14
              3(a,b): 4+5 = 9
              4: 10
              
        ************ Attempt all questions. Total marks is 45, but the maximum you can score is 40 ***************** 
       	
     	
	Note: 1) All the tasks are given in Section 2. Section 1 contains some helper functions which you may require. Section 3 contains testing functions which you will not require. 
	      2) In Section 2, the functions init_hash_oa_table() and hash_oa_search() are already implemented. These are given in order to give you idea about the hash function and open    	          	 addressing scheme. The tasks 3(a) and 3(b) are given after these two functions.	
	      3) Do not modify the functions init_hash_oa_table() and hash_oa_search() and any function outside Section 2.
	      4) In Task 4, you are required to briefly explain (in 2-3 lines) your algorithm to solve the task.
	      5)  For j = 1,2,3,4, the drawing for graphj is given in Digraphj.pdf (and adjacency matrix in digraphj).
	      
	      
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include"stack-on-array.c"


/*****************************************************************Section 1: Helper Functions*************************************************************************/

/*Node data structure for nodes used in lists.*/
typedef struct list_node {
	int node_index;                             // Index of the node as given by the adjacency matrix
	struct list_node* ptr_sibling;                   // Pointer to its next sibling in the adjacency list
	
} list_node;
/* Create a new adjacency list node and returns a pointer to it.
Input: Index of the node.
Output: Pointer to the newly created adjacency list node or NULL if the node creation fails.*/

list_node* create_node (int node_index){
	list_node* ptr_new_node = (list_node*) malloc (sizeof (list_node));
	if (ptr_new_node != NULL){
		ptr_new_node-> node_index = node_index;
		ptr_new_node->ptr_sibling = NULL;
	}
	return ptr_new_node;
}

/* Print List: Helper function to print the elements of a given list. */
int print_list (list_node* ptr_list_node){
	


	while (ptr_list_node != NULL){
		printf ("%d ", ptr_list_node-> node_index);
		ptr_list_node = ptr_list_node -> ptr_sibling;
	}
	
	return 0;
}

/* create_adjacency_list: Helper function to create adjacency list of a digraph from its adjacency matrix.*/
								

list_node** create_adjacency_list (char* file_name, int * order){


	FILE * graph_data;
	int i, j, temp;
	char* row;

	graph_data = fopen ( file_name,"r"); // Open the file in read-only mode
			
	list_node* ptr_new;
	list_node** adjacency_list;

	if (graph_data != NULL){

		fscanf(graph_data,"%d", &temp);
		(*order) = temp;

		adjacency_list = (list_node**)malloc(temp* sizeof(list_node*));
		row = malloc((temp+2) * sizeof(char));
		fgets(row,(temp+2), graph_data);
		
		for (i = 0; i < temp; i++){
			fgets(row,(temp+2), graph_data);
			adjacency_list[i] = NULL;
			
			for (j=0; j < temp; j++){
				if((row[j] - '0') == 1) {
					ptr_new = create_node(j);
					ptr_new -> ptr_sibling = adjacency_list[i];
					adjacency_list[i] = ptr_new;
				}

				
			} 
		} 

		fclose(graph_data);
	}

	return adjacency_list;
}


/* get_reverse_adjacency_list. Given the adjacency list of a digraph return the adjacency list of its reverse.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
			Output: Adjacency list of the reverse graph.
*/


list_node** get_reverse_adjacency_list (int order, list_node** adjacency_list){
	int i, child_index;
	list_node** reverse_adjacency_list;
	reverse_adjacency_list = (list_node**) malloc (order * sizeof(list_node*));
	list_node* ptr_list;
	list_node* ptr_new_node;
	
	for (i =0; i< order; i++){
		reverse_adjacency_list[i] = NULL;
	}

	for (i = 0; i < order; i++){
		ptr_list = adjacency_list[i];
		while (ptr_list != NULL){
		

			child_index = ptr_list -> node_index;
			ptr_new_node = create_node(i);
			ptr_new_node -> ptr_sibling = reverse_adjacency_list [child_index];
			reverse_adjacency_list [child_index] = ptr_new_node;
			ptr_list = ptr_list->ptr_sibling;
		}
		
	}
	
	return reverse_adjacency_list;
}

/*free_list: Helper function to free a list of node_list type nodes*/
int free_list(list_node* list){

		if (list == NULL){
			return 0;
		}

		if(list-> ptr_sibling != NULL){
			free_list(list-> ptr_sibling);
		}
		free(list);
		
		return 0;
}

/*free_adjacency_list: Helper function to free adjacency list*/
int free_adjacency_list (list_node** list, int order){
	int i;
	for (i=0; i < order ; i++){

		free_list(list[i]);
	}
	
	free(list);
	
	return 0;
}




/* 
get_random. Returns a random number between lb and ub.
*/




int get_random(int lb, int ub){
	int rand_num;
	srand(time(0));
	rand_num = (rand()%(ub-lb+1)+ lb);
	return rand_num;
}

/*
get_big_random. Returns a random unsigned int.
*/
unsigned int get_big_random(){
	
	unsigned int rand_val;


	
	rand_val  = (unsigned int) rand() & 0xff;
        rand_val |= ((unsigned int)rand() & 0xff) << 8;
        rand_val |= ((unsigned int)rand() & 0xff) << 16;
        rand_val |= ((unsigned int)rand() & 0xff) << 24;
        

        
        return rand_val;
        
}

/*

get_prime. Given an integer it returns a prime greater than the number. 

*/

int next_prime(int m){
	int i, j;
	bool flag;
	int sqval;
	double k;
	
	
	while(1){
		flag = false;
		
		sqval = (int) sqrt(m);
		
		
		for(i =2; i <= sqval; i++){
			if (m % i == 0){
				m++;
				flag = true;
				break;
			}
		}
		
		if(flag == false){
			return m;
		}
	}
}	





/*******************************************************************************Section 2: Tasks***************************************************************************/

/**************************************************************** Task 1: Strong Connectedness************************************************************/
/*Task 1: Goal of this task is to return a list of vertices reachable from a given vertex (the set includes the vertex itself). 
It is divided into the following two subtasks.
*/

/* Task 1(a): dfs_explore. Run a DFS from a given node and return a list of all the nodes reachable from it. 
				Input: i) order: Order of the graph.
				       ii) adjacency_list: Pointer to the adjacency list of the graph.
				       iii) node_index: Index of the node from which DFS will start.
				       iv) visited: Pointer to an array (indexed by node indices) indicating the list of nodes already visited by the DFS. A node is visited when the DFS reaches the 						   node for the first time.  visited[i] = 1 if the node i has been visited, otherwise visited[i] = 0.
				        
				 Output: i) A list of nodes reachable by the DFS from the starting node. Assume/ note that a node is reachable from itself. 
				 	   visited array should be updated accordingly.
				 	   
				 	  ( 6 Marks )
 */
list_node* dfs_explore(int order, list_node** adjacency_list, int node_index, int * visited){
	list_node* reachable_set = create_node(node_index);
	visited[node_index] = 1;

	list_node* x = adjacency_list[node_index];
	while(x != NULL){
		if(visited[x->node_index] == 0){
			list_node* temp = dfs_explore(order, adjacency_list, x->node_index, visited);
			list_node* curr = reachable_set;
			if(curr->ptr_sibling == NULL){
				curr->ptr_sibling = temp;
			}
			else{
				while(curr->ptr_sibling != NULL){
					curr = curr->ptr_sibling;
				}
				curr->ptr_sibling = temp;
			}
		}

		x = x->ptr_sibling;
	}
	
	
	
	return reachable_set;
}

/* Task 1(b): list_reachable. Return a list of nodes reachable from a given node.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
				iii) node_index: Index of the given node.
			Output:
				A list of nodes reachable from the given node. Assume/note that a node is reachable from itself.
				
				(2 Marks)
			       	
*/
list_node* list_reachable(int order, list_node** adjacency_list, int node_index ){
	list_node* reachable_set = NULL;
	int* visited = calloc(order, sizeof(int));

	reachable_set = dfs_explore(order, adjacency_list, node_index, visited);

	
	return reachable_set;
}



/* Task 1(c): is_strongly_connected. Checks whether the input directed graph (given by the adjacency list) is strongly connected.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
			Output: 1 if the graph is strongly connected; 0 otherwise.
			
			(4 Marks)
*/
 
int is_strongly_connected(int order, list_node** adjacency_list ){
	list_node** rev_list = get_reverse_adjacency_list(order, adjacency_list);

	int index = 4;
	list_node* list1 = list_reachable(order, adjacency_list, index);
	list_node* list2 = list_reachable(order, rev_list, index);

	int len1 = 0;
	int len2 = 0;

	list_node* temp1 = list1;
	list_node* temp2 = list2;

	while(temp1 != NULL){
		temp1 = temp1->ptr_sibling;
		len1++;
	}

	while(temp2 != NULL){
		temp2 = temp2->ptr_sibling;
		len2++;
	}
	
	return (len1 == len2);
}






/************************************************************* Task 2:  Queue, BFS, and Single Source Shortest Path Information ************************************************************/


/*********** Task 2(a): Queue Routines*******************************/

/*In the following implement a Queue ADT on a linked-list. The items in the queue will be of list_node type. */


typedef struct {
	list_node* ptr_front;
	list_node* ptr_rear;
	int size;	
} Queue;

/*Task 2(a)[i]: init_queue. Initialize the queue.
 (1 Mark) */
Queue init_queue(){
	Queue new_queue;
	new_queue.ptr_front = NULL;
	new_queue.ptr_rear = NULL;
	new_queue.size = 0;
	
	return new_queue;
}

/*Task 2(a)[ii]: enque. Given a queue and an item, add the item to the queue.

(2 Marks)*/

int enque (Queue* ptr_queue, int item){
	list_node* new = create_node(item);

	if(ptr_queue->size == 0){
		ptr_queue->ptr_front = new;
		ptr_queue->ptr_rear = new;
	}

	else{
		ptr_queue->ptr_rear->ptr_sibling = new;
		ptr_queue->ptr_rear = new;
	}
	ptr_queue->size++;

	return 0;	   
}

/*Task 2(a)[iii]: deque. Given a queue perform the dequeue operation.

(3 Marks)*/

int deque (Queue* ptr_queue){
	int val;
	if(ptr_queue->size == 0){
		fprintf(stderr, "Error in deque: Queue Empty\n");
		return -1;
	}

	val = ptr_queue->ptr_front->node_index;
	list_node* temp = ptr_queue->ptr_front;
	ptr_queue->ptr_front = ptr_queue->ptr_front->ptr_sibling;
	free(temp);
	ptr_queue->size--;

	return val;
}

int print_queue(Queue q){
	int i;
	list_node* ptr_temp;
	ptr_temp = q.ptr_front;
	for (i =0; i< q.size; i++){
		printf("%d ", ptr_temp->node_index);
		ptr_temp = ptr_temp -> ptr_sibling;
		
	}
	return 0;
}



/*Task 2(b): BFS: Goal of the task is to perform BFS on a digraph, given its adjacency list and a source node. In the end, it returns (for each node)*/
/*length of the shortest path from the source node to the given node, and parent of the given node along the BFS shortest path. Following data structure */
/*collects these information. Here note that, it is enough to have the parent information, as the length of the shortest path can be computed from it.  */
/*	Input*/
/*		order: order of the graph.*/
/*		adjacency_list: adjacency list of the graph*/
/*		node_index: index of the source node*/
/*	Output*/
/*		BFS_Data: this data structure (defined below) has two integer pointers. */
/*			i) ptr_sp_length: pointer to an integer array where the j-th element is the length of the shortest path to the node j. If there is no such path*/
/*			   then the j-th element is a large number (say 2* order of the graph). */
/*			ii) ptr_parent: pointer to an integer array where the j-th element is the parent of the j-th node in the BFS path from the source node. It is -1 if there*/
/*			   no parent. 

(8 Marks) */
// #define LARGE_NUM(order) 2*order

typedef struct {
	int* ptr_sp_length;
	int* ptr_parent;
}BFS_Data;

BFS_Data BFS(int order, list_node** adjacency_list, int node_index){
	BFS_Data bfs_lists;
	
	int* dist = malloc(sizeof(int) * order);
	int* par = malloc(sizeof(int) * order);

	for(int i=0; i<order; i++){
		dist[i] = 2 * order;
		par[i] = -1;
	}

	dist[node_index] = 0;
	Queue q = init_queue();
	enque(&q, node_index);

	while(q.size != 0){
		int v = deque(&q);
		list_node* x = adjacency_list[v];
		while(x != NULL){
			if(dist[x->node_index] > dist[v] + 1){
				dist[x->node_index] = dist[v] + 1;
				par[x->node_index] = v;
				enque(&q, x->node_index);
			}

			x = x->ptr_sibling;
		} 
	} 

	bfs_lists.ptr_sp_length = dist;
	bfs_lists.ptr_parent = par;
	
	return bfs_lists;
	
}


/***************************** Task 3: Hashing with Open Addressing **************************************************************/

typedef struct {
	int num_data; // Number of elements stored in the table at any given time
	int prime;   // Prime chosen for hash computation
	int num_collisions; // Number of collisions occurred in a certain sequence of insert operations (this is only required for testing and not an essential part of hash table information)
	unsigned int* ptr_table; // Array to store data items in the table. The data items are of unsigned int type.
}OA_Hash_Table;



/*
init_oa_hash_table: Initialize the parameters of the hash table given an estimate of the number of items to be stored.


		   Input: num_data_items - Max number of data items that the table is expected to store.
		   Output : OA_Hash_Table with all its members initialized. num_collisions to be intitialized to 0. All the hash table entries should be initialized to some special value, e.g., 					UINT_MAX.
		   
		   
		***************** This is not a task.**********************************
*/
OA_Hash_Table init_hash_oa_table(int num_data_items){
	OA_Hash_Table ht;
	int i;
	ht.prime = next_prime(num_data_items);
	ht.num_data =0;
	
	ht.num_collisions = 0;
	ht.ptr_table = (unsigned int*) malloc (ht.prime* sizeof(unsigned int));
	for (i=0; i< ht.prime;i++){
		ht.ptr_table[i] = UINT_MAX;
	}
	
	return ht;
}

/*

hash_oa_insert: Insert a given list of data items into a given hash table with open addressing.
		Input: i) num_data_items - number of data items to be inserted.
		       ii) ptr_data - list of data items to be inserted
		       iii) ptr_oaht - pointer to the OA_Hash_Table hash table data structure.
		       iv) probe_seq - identifier for a particular probe sequence. We will use any one from the list given in the class notes.
		       
		Output: Updata the hash table pointed by ptr_oaht appropriately.       
*/
int hash_oa_insert(int num_data_items, unsigned int* ptr_data, OA_Hash_Table* ptr_oaht, int probe_seq){

	int i, j, hash, init_hash;
	
	for (i =0; i< num_data_items; i++){
	
		init_hash = ptr_data[i] % ptr_oaht->prime;
	
		for (j = 0; j < ptr_oaht->prime; j++){
			hash = (init_hash+j) % ptr_oaht->prime;
			if (ptr_oaht->ptr_table[hash] == UINT_MAX){
				ptr_oaht->ptr_table[hash] = ptr_data[i];
				ptr_oaht->num_data = ptr_oaht->num_data+1;
				break;
			
			} else {
			
					ptr_oaht->num_collisions = ptr_oaht->num_collisions+1;
			}
		}

	}
	
	return 0;
}



/** Task 3(a): hash_oa_search: Search the hash table for a given list of data items.
		Input: i) num_data_items - number of data items to be searched.
		       ii) ptr_data - list of data items to be searched.
		       iii) ptr_flag - An array of flags indicating whether a data item has been found in the table. If ptr_data[i] is found in the hash table then ptr_flag[i] should be set to 1.
		       		All the flags are set to 0 in the input.
		       		
		       iv) ptr_oaht - pointer to the OA_Hash_Table hash table data structure.
		       v) probe_seq - identifier for a particular probe sequence. We will use any one from the list given in the class notes.
		Output: Update the ptr_flag array appropriately.
		
		(4 Marks) */      
		       
int hash_oa_search(int num_data_items, unsigned int* ptr_data, OA_Hash_Table* ptr_oaht, int* ptr_flag, int probe_seq){
	for(int i=0; i<num_data_items; i++){
		int init_hash = ptr_data[i] % ptr_oaht->prime;
		for(int j=0; j<ptr_oaht->prime; j++){
			int hash = (init_hash + j) % ptr_oaht->prime;
			if(ptr_oaht->ptr_table[hash] == ptr_data[i]){
				ptr_flag[i] = 1;
				break;
			}
		}

	}
	
	return 0;
}

/* Task 3(b): hash_oa_delete: Delete a given list of data items from the hash table.
		Input: i) num_data_items - number of data items to be deleted.
		       ii) ptr_data - list of data items to be deleted.
		       iii) ptr_flag - An array of flags indicating whether a data item has been found and deleted from the table. If ptr_data[i] is found and deleted from the hash table then 					ptr_flag[i] should be set to 1. All the flags are set to 0 in the input.
		       iv) ptr_oaht - pointer to the OA_Hash_Table hash table data structure.
		       v) probe_seq - identifier for a particular probe sequence. Use any one from the list given in the class notes.
		       
		Output: If a given data item is found in the table then it should be deleted with appropriate modification to the table. Update the ptr_flag array appropriately. 
		
		(5 Marks)*/  


int hash_oa_delete(int num_data_items, unsigned int* ptr_data, OA_Hash_Table* ptr_oaht, int* ptr_flag, int probe_seq){
	for(int i=0; i<num_data_items; i++){
		int init_hash = ptr_data[i] % ptr_oaht->prime;
		for(int j=0; j<ptr_oaht->prime; j++){
			int hash = (init_hash + j) % ptr_oaht->prime;
			if(ptr_oaht->ptr_table[hash] == ptr_data[i]){
				ptr_oaht->ptr_table[hash] = UINT_MAX - 1;
				ptr_flag[i] = 1;
				break;
			}
		}
	}	

	return 0;
}

/**********************************************************************Task 4: Count Inversion*****************************************************************************************/
/* count_inversion: Goal of this task is to count inversions in a given array of distinct integers. Given an array of distinct integers a pair (i, j) is an inversion if i>j and i appears before 
j in the array. For example, in the array [1, 4, 3, 2] there are 3 inversions, namely, (4,3), (4,2), and (3, 2).

Input : i) size: size of the input array
	ii) ptr_array: pointer to the input array
	
Output : count: the number of inversions.	

     (8 Marks); 3 marks for correct explanation of an algorithm that is better than O(n^2) brute-force algorithm + 7 marks for correct implementation of the algorithm.
 
*/


/****** 2-3 lines of explanation of your algorithm:

In merge sort while doing merge, we can change the counter in order to produce correct no.of inversions as 

*******/ 


void merge(int* array, int lsize, int rsize, int* count){
	int i = 0;
	int j = lsize;
	int* z = malloc(sizeof(int) * (lsize + rsize));


	for(int m=0; m<lsize+rsize; m++){
		if(i >= lsize){
			z[m] = array[j++];
			(*count)++;
		}
		else if(j >= lsize + rsize){
			z[m] = array[i++];
			// (*count)++;
		}
		else if(array[i] < array[j]){
			z[m] = array[i++];
			// (*count)++;
		}
		else{
			z[m] = array[j++];
			(*count)++;
		}
	}

	for(int i=0; i<lsize+rsize; i++){
		array[i] = z[i];
	}

	free(z);

}


void mergeSort(int* array, int size, int* count){
	if(size <= 1)
		return;

	int mid = size/2;
	mergeSort(array, mid, count);
	mergeSort(array + mid, size -mid, count);
	merge(array, mid, size - mid, count);
	(*count)++;
}




int count_inversion(int size, int* ptr_array){
	int count = 0;

	mergeSort(ptr_array, size, &count);
	
	// for(int i=0; i<size; i++){
	// 	printf("%d ", ptr_array[i]);
	// }
	// printf("\n");
	// if(size > 1){
	// 	if(ptr_array[0] > ptr_array[1]){
	// 		count++;
	// 	}
	// }
	// int c = count_inversion(size - 1, ptr_array +1);
	// count = count + c;
	// // push(&s, ptr_array[i]);


	return count;
}




/***************************************************************** Section 3: Testing Functions *****************************************************************************************/




/*sssp (single source shortest path). Given the adjacency list of a digraph and a source node print the distance of every other node from the source node, */
/*	   and also (one of the) shortest paths from the source node to the other nodes.*/
/*	   Input*/
/*	   1) order: order of the graph.*/
/*	   2) adjacency_list: pointer to the adjacency list of the graph*/
/*	   3) source_index: index of the source node of sssp.*/
/*	   Output*/
/*	   	For each node i or the graph, print the following.*/
/*	   		If there is a path from the source node to node i, then print*/
/*	   		"Distance of node <i> from source <source_node> is <distance>".*/
/*	   		"One of the shortest paths from <source_node> to <i> is"*/
/*	   			"<source_node>-<i1>-<i1>- ..., <ip>-<i>", where i1,i2,...,ip is the*/
/*	   			sequece of nodes of a shortest path from <source_node> to <i>.*/

int sssp(int order, list_node** adjacency_list, int source_index){

	BFS_Data bfs_lists;
	int d,i,j,k, sp_length;

	int LARGE_VALUE = 2*order;
	Stack s;
	char c;
	
	
	bfs_lists = BFS(order, adjacency_list, source_index);
	
	for(i=0; i< order; i++){
		sp_length = bfs_lists.ptr_sp_length[i];
		
		if (sp_length == LARGE_VALUE){
			
			printf("There is no path from %d to %d\n", source_index, i);
		} else {
			
			printf ("Distance of %d from source %d = %d\n", i, source_index, sp_length);
			printf("\n");
			init(&s);
			if (i < 10){
				push(&s,'0'+i);
			}else{
				push(&s,'a'+i-10);
			}

			j = bfs_lists.ptr_parent[i];
			
			while(j!=-1){

				push(&s, '-');
				if(j<10){
					push(&s,'0'+j);
				}else{
					push(&s,'a'+j-10);
				}				
				j = bfs_lists.ptr_parent[j];
			}
			printf ("One of the shortest paths from source %d to destination %d is \n", source_index, i );
			for(k = 0;; k++) {
				c = pop(&s);
				if (c == '$') {
					printf("\n");
					break;
				}
				printf("%c", c);
			}

		}
			
		printf("\n\n");
	} 
}



/************ Data structure for test data *************************************************************/
typedef struct{
	int ins_set_size;
	int del_set_size;
	int search_set_size;
	unsigned int* ptr_insert_data;
	unsigned int* ptr_delete_data;
	unsigned int* ptr_search_data;
	
	int* ptr_delete_pattern;
	int* ptr_search_pattern;
} Test_Data;

Test_Data generate_data(int ins_set_size, int block_size, int test_block_num)
{
	Test_Data td;
	int i,j, p, t;
	
	td.ins_set_size = ins_set_size;

	
	td.ptr_insert_data = (unsigned int*) malloc (ins_set_size* sizeof(unsigned int));
	td.ptr_delete_data = (unsigned int*) malloc (((block_size+2)*test_block_num)* sizeof(unsigned int));
	td.ptr_search_data = (unsigned int*) malloc (((block_size+2)*test_block_num)* sizeof(unsigned int));
	td.ptr_delete_pattern = (int*) malloc (((block_size+2)*test_block_num)* sizeof(int));
	td.ptr_search_pattern = (int*) malloc (((block_size+2)*test_block_num)* sizeof(int));
	
	srand(time(NULL));
	
	for (i = 0; i < ins_set_size; i++){
		td.ptr_insert_data[i] = get_big_random();
	}
	
	for (i =0; i< test_block_num; i++){
		for(j=0; j < block_size-2; j++){ 
			td.ptr_delete_data[i*block_size+j] = td.ptr_insert_data[i*block_size+j];
			td.ptr_delete_pattern[i*block_size+j] = 1;			
		}
		
		td.ptr_delete_data[i*block_size+j] = td.ptr_delete_data[i*block_size+j - 3];
		td.ptr_delete_pattern[i*block_size+j]=0;
		
		td.ptr_delete_data[i*block_size+j+1] = td.ptr_delete_data[i*block_size+j-2];
		td.ptr_delete_pattern[i*block_size+j+1]=0;	
	}
	td.del_set_size = test_block_num* block_size;
	
	
	
	
	for (i =0; i< test_block_num; i++){
		for(j=0; j < block_size-2; j++){ 
			td.ptr_search_data[i*block_size+j] = td.ptr_insert_data[td.del_set_size+i*block_size+j];
			td.ptr_search_pattern[i*block_size+j] = 1;
			
		}
		td.ptr_search_data[i*block_size+j] = td.ptr_search_data[i*block_size+j-4]+1;
		
		td.ptr_search_pattern[i*block_size+j]=0;
	
		td.ptr_search_data[i*block_size+j+1] = td.ptr_search_data[i*block_size+j-2]+1;
		td.ptr_search_pattern[i*block_size+j+1]=0;	
	}
	
	td.search_set_size = test_block_num* block_size;
	
	return td;
	
}


/**************************** Tests for Task 1 ****************************************************/






int test_hash_oa_search(OA_Hash_Table* ptr_oaht, int data_size, unsigned int* ptr_data, int * ptr_input_flag, int probe_seq){
	
	int i;
	bool bflag = false;
	clock_t start, end;
	int * ptr_flag = (int *) calloc (data_size, sizeof(int));
	
	start = clock();
	hash_oa_search(data_size, ptr_data, ptr_oaht, ptr_flag, probe_seq);
	end = clock();
	for (i = 0; i< data_size; i++){
		if (ptr_flag[i] != ptr_input_flag[i]){
			bflag = true;
			break;
		}
	}
	
	if (bflag == true){
		printf("Search failed for index %d\n", i);
	} else {
		 printf ("Total cpu cycles used %f\n",(double)(end - start));
        	  printf("Average cpu cycles per data item = %f\n",((double)(end - start)/ data_size));
		
	}
	
	return 0;
	
}


int test_hash_oa_delete(OA_Hash_Table* ptr_oaht, int data_size, unsigned int* ptr_data, int * ptr_input_flag, int probe_seq){
	int i;
	bool bflag = false;
	clock_t start, end;
	int * ptr_flag = (int *) calloc (data_size, sizeof(int));
	
	start = clock();
	hash_oa_delete(data_size, ptr_data, ptr_oaht, ptr_flag, probe_seq);
	end = clock();
	for (i = 0; i< data_size; i++){
		if (ptr_flag[i] != ptr_input_flag[i]){
			bflag = true;
			break;
		}
	}
	
	if (bflag == true){
		printf("Deletion failed for index %d\n", i);
	} else {
		 printf ("Total cpu cycles used %f\n",(double)(end - start));
        	  printf("Average cpu cycles per data item = %f\n",((double)(end - start)/ data_size));
		
	}
	
	return 0;
	
}

int test_count_inversion(int size, int* ptr_array){
	int count, i, j;
	count = 0;
	for (i = 0; i< size; i++){
		for (j=i+1; j< size; j++){
			if (ptr_array[i] > ptr_array[j]){
				count++;
			}
		}
	}
	
	return count;
}

/********************** main function*****************/

int main(){

	list_node** adjacency_list;
	list_node* list;
	list_node** scc;
	int order, i, j;
	int * ptr_topo_order;

	char graph1[] = "digraph1";
	char graph2[] = "digraph2";
	char graph3[] = "digraph3";
	char graph4[] = "digraph4";
	

	
       Test_Data td1;
       OA_Hash_Table oaht1;
       int num_data = 60;
       int del_set_block_size = 7;
       int del_set_num_blocks = 4 ;
       
       int invert_array1[8] = {2,6,3,1,4,5,8,7};
       int invert_array2[10] = {8,6,5,10,7,2,4,1,9,3};
       int invert_array3[16] = {12,16,5,10,11,6,7,4,2,3,1,8,13,14,15,9};
       int invert_array4[16] = {14,4,5,10,12,9,7,16,2,15,1,8,13,11,3,6};
	
	



/* Task 1*/
	printf("**********************Testing Tasks 1(a) and 1(b) ********************\n");
	int vertex;
	
/*  */
	adjacency_list = create_adjacency_list(graph1,&order);
	vertex = 4;
	list = list_reachable(order, adjacency_list, vertex);
	printf("List of vertices reachable from %d in Digraph1\n", vertex);
	print_list(list);
	printf("\n\n");
/*  */
	free_adjacency_list (adjacency_list,order);

/*  */
	
	
	adjacency_list = create_adjacency_list(graph2,&order);
	vertex = 0;
	list = list_reachable(order, adjacency_list, vertex);
	printf("List of vertices reachable from %d in Digraph2\n", vertex);
	print_list(list);
	printf("\n\n");
/*  */
	free_adjacency_list (adjacency_list,order);
	
	adjacency_list = create_adjacency_list(graph2,&order);
	vertex = 3;
	list = list_reachable(order, adjacency_list, vertex);
	printf("List of vertices reachable from %d in Digraph2\n", vertex);
	print_list(list);
	printf("\n\n");
/*  */
	free_adjacency_list (adjacency_list,order);
	
	
	adjacency_list = create_adjacency_list(graph3,&order);
	vertex = 0;
	list = list_reachable(order, adjacency_list, vertex);
	printf("List of vertices reachable from %d in Digraph3\n", vertex);
	print_list(list);
	printf("\n\n");
/*  */
	free_adjacency_list (adjacency_list,order);
	
	adjacency_list = create_adjacency_list(graph4,&order);
	vertex = 10;
	list = list_reachable(order, adjacency_list, vertex);
	printf("List of vertices reachable from %d in Digraph3\n", vertex);
	print_list(list);
	printf("\n\n");
/*  */
	free_adjacency_list (adjacency_list,order);
/*  */
/*  */
/*  */
	printf("********************** Testing Tasks 1(c) ********************\n");
	
	adjacency_list = create_adjacency_list(graph1,&order);
	printf("Digraph1 is ");
	if (is_strongly_connected(order, adjacency_list) == 1){
		printf ("Strongly connected \n");
	} else {
		printf ("Not strongly connected\n");
	}
	
	free_adjacency_list (adjacency_list,order);
	
	adjacency_list = create_adjacency_list(graph2,&order);
	printf("Digraph2 is ");
	if (is_strongly_connected(order, adjacency_list) == 1){
		printf ("Strongly connected \n");
	} else {
		printf ("Not strongly connected\n");
	}
	
	free_adjacency_list (adjacency_list,order);
	adjacency_list = create_adjacency_list(graph3,&order);
	printf("Digraph3 is ");
	if (is_strongly_connected(order, adjacency_list) == 1){
		printf ("Strongly connected \n");
	} else {
		printf ("Not strongly connected\n");
	}
/*  */
	free_adjacency_list (adjacency_list,order);
	
	adjacency_list = create_adjacency_list(graph4,&order);
	printf("Digraph4 is ");
	if (is_strongly_connected(order, adjacency_list) == 1){
		printf ("Strongly connected \n");
	} else {
		printf ("Not strongly connected\n");
	}
/*  */
	free_adjacency_list (adjacency_list,order);






/*************** Task 2 ************************************/

/*************** Task 2(a)****************************/
	printf("***********Testing task 2(a)***********\n");
	Queue q;
	int num_items = 8;
	int half_num_items = num_items/2;
	int item, num;
	
	q = init_queue();
	srand(time(0));
	
	
	for (i = 0; i< num_items; i++){
		
		item  = rand()% (num_items+1);
		printf ("Adding %d to the queue\n", item);
		enque(&q, item);
	}
	printf("Printing the items of the queue\n");
	print_queue(q);
	printf("Dequeuing ...\n");
	for(i =0;i < half_num_items; i++){
		j = deque(&q);
		printf("Dequeued %d\n", j);
	}
	printf("Size of the queue = %d\n", q.size);
	printf("Printing the items of the queue\n");
	print_queue(q);
	j = deque(&q);
	
	while(j != -1){
		printf("Dequed %d\n", j);
		j = deque(&q);
	}
	if(q.size == 0){
		printf("Queue is empty \n");
	}
/*  */
/*  ************** Task 2(b) *************************** */
/*   */
	printf("**************Testing task 2(b)********\n");
	BFS_Data bfs;
	int index =0;
	
	printf("****Running Task 2(b) on Digraph1****\n\n");
	adjacency_list = create_adjacency_list(graph1, &order);
	sssp(order, adjacency_list,0);
/*  */
	free_adjacency_list(adjacency_list, order);
	printf("\n\n");
	
	printf("****Running Task 2(b) on Digraph2****\n\n");
	adjacency_list = create_adjacency_list(graph2, &order);
	sssp(order, adjacency_list,0);
/*  */
	free_adjacency_list(adjacency_list, order);
	printf("\n\n");
	
	printf("****Running Task 2(b) on Digraph3****\n\n");
	adjacency_list = create_adjacency_list(graph3, &order);
	sssp(order, adjacency_list,0);
	free_adjacency_list(adjacency_list, order);
	printf("\n\n");
	
	printf("****Running Task 2(b) on Digraph4****\n\n");
	adjacency_list = create_adjacency_list(graph4, &order);
	sssp(order, adjacency_list,0);
	free_adjacency_list(adjacency_list, order);
	printf("\n\n");


/* 	*/
 	



     /*************************** Task 3 ************************************/

	printf ("******************Testing Task 3**************\n");
	
	for (i = 1; i<=6; i++){
	
		printf ("*******************************************\n");
		printf ("Inserting %d data items \n", i*num_data);
/*  */
		td1 = generate_data(i*num_data, del_set_block_size, del_set_num_blocks);
		oaht1 = init_hash_oa_table(i*num_data);
              hash_oa_insert(td1.ins_set_size, td1.ptr_insert_data, &oaht1, 0);
		printf("\n\n");
		printf ("Testing search...\n");
		test_hash_oa_search(&oaht1, td1.search_set_size, td1.ptr_search_data,td1.ptr_search_pattern,0);
		
		printf("\n\n");
		
		printf("Testing delete ....\n");
		test_hash_oa_delete(&oaht1, td1.del_set_size, td1.ptr_delete_data, td1.ptr_delete_pattern,0);
		printf ("\n\n");
	}
/*	*/
/*	*/
	/******************* Task 4*****************************************************/
	
	printf("************** Testing Task 4\n**************************");
	 int count1, count2;
	count2 = test_count_inversion(8, invert_array1);
	count1 = count_inversion (8, invert_array1);

	if (count1 == count2){
		printf("Inversion count %d is correct for array1\n", count1);
	}else{
		printf("Inversion count is not correct for array1,count1 = %d, count2 = %d\n", count1, count2);
	
	}
	
	count2 = test_count_inversion(10, invert_array2);;
	count1 = count_inversion (10, invert_array2);

	if (count1 == count2){
		printf("Inversion count %d is correct for array2\n", count1);
	}else{
		printf("Inversion count is not correct for array2, count1 = %d, count2 = %d\n", count1, count2);
	
	}
	count2 = test_count_inversion(16, invert_array3);
	count1 = count_inversion (16, invert_array3);

	if (count1 == count2){
		printf("Inversion count %d is correct for array3\n", count1);
	}else{
		printf("Inversion count is not correct for array3,count1 = %d, count2 = %d\n", count1, count2);
	
	}
	count2 = test_count_inversion(16, invert_array4);
	count1 = count_inversion(16, invert_array4);

	if (count1 == count2){
		printf("Inversion count %d is correct for array4\n", count1);
	}else{
		printf("Inversion count is not correct for array4,count1 = %d, count2 = %d\n", count1, count2);
	
	}
 

	

	return 0;
}



