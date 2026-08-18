/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 12 | 18/Apr/2024
	Tasks:		1 (a,b,c), 2(a,b,c)
	
	Aim:  To perform the following tasks by running DFS and BFS on a directed graph.
		Taks 1 (divided into a,b,c): Given the adjacency list and a vertex of a digraph list all its strongly connected components.
		Task 2 (divided into a,b,c): Given the adjacency list of a digraph and a source node list single source shortest paths to all the nodes from the source.
		
		
	Note: 1)The tasks are given in Section 3. Section 1 contains some helper functions which you may not require, and Section 2 contains some previously implemented functions which you may 	            require.
	      2) You may have to use some stack functionality. For that, stack-on-array.c has been included. You can directly call those functions.		
	
				
	
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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






/********************************************************************************Section 2: Functions Implemented in Previous Labs ********************************************************************************/

/* dfs_explore. Run a DFS from a given node and return a list of all the nodes reachable from it. 
				Input: i) order: Order of the graph.
				       ii) adjacency_list: Pointer to the adjacency list of the graph.
				       iii) node_index: Index of the node from which DFS will start.
				       iv) visited: Pointer to an array (indexed by node indices) indicating the list of nodes already visited by the DFS. A node is visited when the DFS reaches the 						   node for the first time.  visited[i] = 1 if the node i has been visited, otherwise visited[i] = 0.
				        
				 Output: i) A list of nodes reachable by the DFS from the starting node. Assume/ note that a node is reachable from itself. 
				 	   visited array should be updated accordingly.
 */
list_node* dfs_explore(int order, list_node** adjacency_list, int node_index, int * visited){
	
	int child_index;
	list_node* ptr_list = NULL;
	list_node* ptr_list2 = NULL;
	list_node* ptr_new = NULL;
	list_node* reachable_set = NULL;
	
	
	ptr_list = adjacency_list[node_index];
	visited[node_index] = 1;
	

	
	while (ptr_list != NULL){
		child_index = ptr_list -> node_index;
		if (visited[child_index] == 0){
			ptr_new = dfs_explore (order, adjacency_list, child_index, visited);
			ptr_list2 = ptr_new;
			while (ptr_list2 -> ptr_sibling != NULL){
				ptr_list2 = ptr_list2-> ptr_sibling;
			}
			ptr_list2->ptr_sibling = reachable_set;
			reachable_set = ptr_new;
			
		}
		ptr_list = ptr_list -> ptr_sibling;	
			
			 
	}
	
	ptr_new = create_node(node_index);
	ptr_new -> ptr_sibling = reachable_set;
	reachable_set = ptr_new;
	
	return reachable_set;
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


/******************************************************************************** Scetion 3: DSA Lab 13 Tasks***************************************************************************************/

/********************************************* Task 1: DFS & Strongly Connected Components************************************************************************/

/*Task 1(a): dfs_explore_with_finish_time: Perform DFS from a given node and record finish time at each reachable node.*/
/*		Input
/*			i) order: order of the graph*/
/*			ii) adjacency_list: pointer to the adjacency list of the graph*/
/*			iii) node_index: index of the root node (starting node) of DFS.*/
/*			iv) visited: pointer to an array indexed by the nodes of the graph. j-th element of the array is 1 if the j-th node has*/
/*					been visited (i.e., the DFS has reached the node); it is 0 otherwise.*/
/*			v) clk: pointer to clock counter.*/
/*			vi) finish_order: pointer to an array where the vertices are arranged in the reverse order of the respective finish times of DFS at the nodes. If finish_order[i1] = v1 and finish_order[i2] =v2, where   i1 > i2, then the DFS has finished at node v1 before finishing at node v2.	*/
/*		Output */
/*			Update the clk counter, and the arrays visited and finish_order appropriately. */
/*			*/
/*			i) j-th element of the visited array should be set to 1 when the DFS reaches the j-th node.*/
/*			ii) clk counter should be incremented by 1 upon finishing of the DFS at the node.*/
/*			iii) finish_order array should be updated to include j in the appropriate order when the DFS finishes at node j.*/
/*				*/

int dfs_explore_with_finish_time(int order, list_node** adjacency_list, int node_index, int * visited, int* clk,  int * finish_order){
	
	
	return 0;
	
}

/*Task 1(b): finish_time_order. Order the nodes of a given digraph as per the finish time of a DFS on it. */
/*		Input*/
/*			i) order: order of the graph*/
/*			ii) adjacency_list: pointer to the adjacency list of the graph*/
/*		Output*/
/*			i) pointer to an array where the vertices are arranged as per finish time of DFS in the reverse order. If finish_order[i1] = v1 and finish_order[i2] =v2, where   i1 > i2, then the DFS has finished at node v1 before finishing at node v2.*/

int* finish_time_order (int order, list_node** adjacency_list){
	

	int * finished_order;


	return finished_order;
		
}
/*Task 1(c): strong_components. Given a digraph list its strong components. (Hint: You may have to use the functions )*/
/*	Input*/
/*		i) order: order of the graph*/
/*		ii) adjacency_list: adjacency list of the graph*/
/*	Output  i) pointer to a list of components, where each component is given by the list of its vertices.*/

list_node** strong_components(int order, list_node** adjacency_list){
	
	
	list_node** ptr_scc;
	
	return ptr_scc;
	
}
/************************************************************* Task 2:  BFS & Single Source Shortest Path ************************************************************/


/*********** Task 2(a): Queue Routines*******************************/

/*In the following implement a Queue ADT on a linked-list. The items in the queue will be of list_node type. */


typedef struct {
	list_node* ptr_front;
	list_node* ptr_rear;
	int size;	
} Queue;

/*Task 2(a)[i]: init_queue. Initialize the queue.*/
Queue init_queue(){
	Queue new_queue;
	
	return new_queue;
}

/*Task 2(a)[ii]: enque. Given a queue and an item, add the item to the queue.*/

int enque (Queue* ptr_queue, int item){
	   
	   return 0;
	   
	   
}

/*Task 2(a)[iii]: deque. Given a queue perform the dequeue operation.*/

int deque (Queue* ptr_queue){
	
	
	return temp;
	
}

int print_queue(Queue q){
	int i;
	list_node* ptr_temp;
	ptr_temp = q.ptr_front;
	for (i =0; i< q.size; i++){
		printf("%d ", ptr_temp->node_index);
		ptr_temp = ptr_temp -> ptr_sibling;
		
	}
}

/******************************************************************************************************************************************/

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
/*			   no parent. */
typedef struct {
	int* ptr_sp_length;
	int* ptr_parent;
}BFS_Data;

BFS_Data BFS(int order, list_node** adjacency_list, int node_index){

	
	BFS_Data bfs_lists;
	
	return bfs_lists;
	
}
/*Task 2(c): sssp (single source shortest path). Given the adjacency list of a digraph and a source node print the distance of every other node from the source node, */
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

	
	
	return 0;
}


/****************************************************************************************************************************************************************/

/****************************************************************************************************************************************************************/

int main(){

	list_node** adjacency_list;
	list_node* list;
	list_node** scc;
	int order, i, j;
	int * ptr_topo_order;

	char graph1[] = "dfs_dir_1";
	char graph2[] = "dfs_dir_2";
	char graph3[] = "dfs_dir_3";
	char graph4[] = "undir_1";
	

	




/*********************** Task 1********************************************/
	
/*	printf("**********************Testing Tasks 1(a) and 1(b) ********************\n");*/

/*        int* dfs_finish_order;*/
/*        */
/*        printf("****Running Task 1(a) and 1(b) on Graph 1*******\n\n");*/
/*        adjacency_list = create_adjacency_list(graph1,&order);*/
/*	dfs_finish_order = (int*) malloc (order* sizeof(int));*/
/*        dfs_finish_order = finish_time_order (order, adjacency_list);*/
/*        printf("Ordering the nodes according to DFS finish time\n\n");*/
/*        for (i =0; i< order; i++){*/
/*        	printf("%d", dfs_finish_order[order-1-i]);*/
/*        }*/
/*        printf("\n\n");*/
/*        free_adjacency_list(adjacency_list, order);*/
/*        free(dfs_finish_order);*/
/*        */
/*        printf("****Running Task 1(a) and 1(b) on Graph 2****\n\n");*/
/*        adjacency_list = create_adjacency_list(graph2,&order);*/
/*	dfs_finish_order = (int*) malloc (order* sizeof(int));*/
/*        dfs_finish_order = finish_time_order (order, adjacency_list);*/
/*        printf("Ordering the nodes according to DFS finish time\n\n");*/
/*        for (i =0; i< order; i++){*/
/*        	printf("%d", dfs_finish_order[order-1-i]);*/
/*        }*/
/*        printf("\n\n");*/
/*        free_adjacency_list(adjacency_list, order);*/
/*        free(dfs_finish_order);*/
/*        */
/*        printf("****Running Task 1(a) and 1(b) on Graph 3****\n\n");*/
/*        adjacency_list = create_adjacency_list(graph3,&order);*/
/*	dfs_finish_order = (int*) malloc (order* sizeof(int));*/
/*        dfs_finish_order = finish_time_order (order, adjacency_list);*/
/*        printf("Ordering the nodes according to DFS finish time\n\n");*/
/*        for (i =0; i< order; i++){*/
/*        	printf("%d", dfs_finish_order[order-1-i]);*/
/*        }*/
/*        printf("\n\n");*/
/*        free_adjacency_list(adjacency_list, order);*/
/*        free(dfs_finish_order);*/

	
/*	printf("**********************Testing Task 1(c) ********************\n");*/
/*	*/
/*        printf("****Running Task 1(c) on Graph 1****\n\n");*/
/*	adjacency_list = create_adjacency_list(graph1,&order);*/
/*	*/
/*	scc = strong_components(order, adjacency_list);*/
/*	printf("Strong components \n");*/
/*	*/
/*	for(i=0; i< order; i++){*/
/*		if (scc[i] != NULL){*/
/*			printf("\n");*/
/*			print_list(scc[i]);*/
/*		}*/
/*	}*/
/*	printf("\n\n");*/
/*	free_adjacency_list(adjacency_list, order);*/
/*	free_adjacency_list(scc, order);*/
/*	*/
/*	*/
/*	*/
/*	printf("****Running Task 1(c) on Graph 2****\n\n");*/

/*	adjacency_list = create_adjacency_list(graph2,&order);*/
/*	*/
/*	scc = strong_components(order, adjacency_list);*/
/*	printf("\n Strong components \n");*/
/*	*/
/*	for(i=0; i< order; i++){*/
/*		if (scc[i] != NULL){*/
/*			printf("\n");*/
/*			print_list(scc[i]);*/
/*		}*/
/*	}*/
/*	printf("\n\n");*/
/*	free_adjacency_list(adjacency_list, order);*/
/*	free_adjacency_list(scc, order);*/
/*	*/
/*	printf("****Running Task 1(c) on Graph 3****\n\n");*/
/*	adjacency_list = create_adjacency_list(graph3,&order);*/
/*	*/
/*	scc = strong_components(order, adjacency_list);*/
/*	*/
/*	printf("Strong components \n");*/
/*	*/
/*	for(i=0; i< order; i++){*/
/*		if (scc[i] != NULL){*/
/*			printf("\n");*/
/*			print_list(scc[i]);*/
/*		}*/
/*	}*/
/*	*/
/*	free_adjacency_list(adjacency_list, order);*/
/*	free_adjacency_list(scc, order);*/
/*	*/
/*	printf("\n\n");*/
/*************** Task 2 ************************************/

/*************** Task 2(a)****************************/
/*	printf("*******************Testing task 2(a)*********************\n");*/
/*	Queue q;*/
/*	int num_items = 8;*/
/*	int half_num_items = num_items/2;*/
/*	int item, num;*/
/*	*/
/*	q = init_queue();*/
/*	srand(time(0));*/
/*	*/
/*	*/
/*	for (i = 0; i< num_items; i++){*/
/*		*/
/*		item  = rand()% (num_items+1); */
/*		printf ("Adding %d to the queue\n", item);*/
/*		enque(&q, item);*/
/*	}*/
/*	printf("Printing the items of the queue\n");*/
/*	print_queue(q);*/
/*	printf("Dequeuing ...\n");*/
/*	for(i =0;i < half_num_items; i++){*/
/*		j = deque(&q);*/
/*		printf("Dequeued %d\n", j);*/
/*	}*/
/*	printf("Size of the queue = %d\n", q.size);*/
/*	printf("Printing the items of the queue\n");*/
/*	print_queue(q);*/
/*	j = deque(&q);*/
/*	*/
/*	while(j != -1){*/
/*		printf("Dequed %d\n", j);*/
/*		j = deque(&q);*/
/*	}*/
/*	if(q.size == 0){*/
/*		printf("Queue is empty \n");*/
/*	}*/

 /*************** Task 2(b) ****************************/
/* 	printf("*******************Testing task 2(b)*********************\n");*/
/* 	BFS_Data bfs;*/
/* 	int index =0;*/
/* 	*/
/* 	printf("****Running Task 2(b) on Graph 1****\n\n");*/
/* 	adjacency_list = create_adjacency_list(graph1, &order);*/
/* 	bfs = BFS(order, adjacency_list, index);*/
/* 	printf ("Shortest path list for BFS with source = %d\n\n", index);*/
/* 	for (j =0; j< order; j++){*/
/* 		printf("%d -- %d\n",j, bfs.ptr_sp_length[j]);*/
/* 	}*/
/* 	printf ("Parent list for BFS with source = %d\n\n", index);*/
/* 	for (j =0; j< order; j++){*/
/* 		printf("%d -- %d\n",j, bfs.ptr_parent[j]);*/
/* 	}*/
/* 	free_adjacency_list(adjacency_list, order);*/
/*	printf("\n\n");*/
/*	*/
/*	printf("****Running Task 2(b) on Graph 2****\n\n");*/
/*	adjacency_list = create_adjacency_list(graph2, &order);*/
/* 	bfs = BFS(order, adjacency_list, index);*/
/* 	printf ("Shortest path list for BFS with source = %d\n\n", index);*/
/* 	for (j =0; j< order; j++){*/
/* 		printf("%d -- %d\n",j, bfs.ptr_sp_length[j]);*/
/* 	}*/
/* 	printf ("Parent list for BFS with source = %d\n\n", index);*/
/* 	for (j =0; j< order; j++){*/
/* 		printf("%d -- %d\n",j, bfs.ptr_parent[j]);*/
/* 	}*/
/* 	free_adjacency_list(adjacency_list, order);*/
/*	printf("\n\n");*/
/*	*/
/*	printf("****Running Task 2(b) on Graph 3****\n\n");*/
/*	adjacency_list = create_adjacency_list(graph3, &order);*/
/* 	bfs = BFS(order, adjacency_list, index);*/
/* 	printf ("Shortest path list for BFS with source = %d\n\n", index);*/
/* 	for (j =0; j< order; j++){*/
/* 		printf("%d -- %d\n",j, bfs.ptr_sp_length[j]);*/
/* 	}*/
/* 	printf ("Parent list for BFS with source = %d\n\n", index);*/
/* 	for (j =0; j< order; j++){*/
/* 		printf("%d -- %d\n",j, bfs.ptr_parent[j]);*/
/* 	}*/
/* 	free_adjacency_list(adjacency_list, order);*/
/*	printf("\n\n");*/
/* 	*/
/* 	printf("****Running Task 2(b) on Graph 4****\n\n");*/
/* 	adjacency_list = create_adjacency_list(graph4, &order);*/
/* 	bfs = BFS(order, adjacency_list, index);*/
/* 	printf ("Shortest path list for BFS with source = %d\n\n", index);*/
/* 	for (j =0; j< order; j++){*/
/* 		printf("%d -- %d\n",j, bfs.ptr_sp_length[j]);*/
/* 	}*/
/* 	printf ("Parent list for BFS with source = %d\n\n", index);*/
/* 	for (j =0; j< order; j++){*/
/* 		printf("%d -- %d\n",j, bfs.ptr_parent[j]);*/
/* 	}*/
/* 	free_adjacency_list(adjacency_list, order);*/
/*	printf("\n\n");*/
 /*************** Task 2(c) ****************************/
 
/* 	printf("******************Task 2(c)*****************\n");	*/
/* 	*/
/* 	printf("****Running Task 2(c) on Graph 1****\n\n");*/
/*	adjacency_list = create_adjacency_list(graph1, &order);*/
/*	sssp(order, adjacency_list,0);*/

/*	free_adjacency_list(adjacency_list, order);*/
/*	printf("\n\n");*/
/*	*/
/*	printf("****Running Task 2(c) on Graph 2****\n\n");*/
/*	adjacency_list = create_adjacency_list(graph2, &order);*/
/*	sssp(order, adjacency_list,0);*/

/*	free_adjacency_list(adjacency_list, order);*/
/*	printf("\n\n");*/
/*	*/
/*	printf("****Running Task 2(c) on Graph 3****\n\n");*/
/*	adjacency_list = create_adjacency_list(graph3, &order);*/
/*	sssp(order, adjacency_list,0);*/
/*	free_adjacency_list(adjacency_list, order);*/
/*	printf("\n\n");*/
/*	*/
/*	printf("****Running Task 2(c) on Graph 4****\n\n");*/
/*	adjacency_list = create_adjacency_list(graph4, &order);*/
/*	sssp(order, adjacency_list,0);*/
/*	free_adjacency_list(adjacency_list, order);*/
/*	printf("\n\n");*/




	return 0;
}
	

	
	
