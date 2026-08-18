/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 10 | 22/Feb/2024
	Tasks:		1,2,3
	
	Aim: 		1. Construct DFS tree/forest
			2. Print the vertices of a graph in a certain order (specified in Task 5 below)
			3. Delete DFS tree/ forest
	
*/

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

/*Node data structure for the DFS tree/ forest.*/
typedef struct node {
	int node_index;                             // Index label of the node as given by the adjacency matrix
	struct node* ptr_children_list;             // Pointer to the list of its children in the DFS tree
	struct node* ptr_sibling;                   // Pointer to its next sibling in the DFS tree
	
} node;

/* Create a new DFS tree node and return a pointer to it.
Input: Index of the node.
Output: Pointer to the node or NULL if the node creation fails.*/

node* create_node (int node_index){
	node* ptr_new_node = (node*) malloc (sizeof (node));
	if (ptr_new_node != NULL){
		ptr_new_node-> node_index = node_index;
		ptr_new_node->ptr_children_list = NULL;
		ptr_new_node->ptr_sibling = NULL;
	}
	return ptr_new_node;
}


/* Helper function to print the DFS tree. Print the list of edges of the DFS tree in u--v format*/
/*Input: Pointer to the root node of the tree*/


int print_dfs_tree(node* root_node){
	node* ptr_children;
	
	ptr_children = root_node-> ptr_children_list;

	while (ptr_children != NULL){
		printf ("%d--%d\n", root_node->node_index, ptr_children->node_index);
		print_dfs_tree(ptr_children);
		ptr_children = ptr_children-> ptr_sibling;
	}
	
	return 0;
}
/*Helper function to print the list of edges of the forest in  u--v format. Edge lists
for separate trees are separated by newlines.*/
/*Input: Pointer to the root node of the tree*/

int print_dfs_forest(node* ptr_node_list){
	node* ptr_temp = ptr_node_list;
	while (ptr_temp != NULL){
		print_dfs_tree(ptr_temp);
		ptr_temp = ptr_temp -> ptr_sibling;
		printf("\n \n");
	
	}
	return 0;
}



/* Build DFS Tree. 
Input:   Order of the graph, pointer to its adjacency matrix, pointer to an array indicating the marked vertices/nodes,
	 index of the root node of the tree 
Output: Pointer to the root node of the tree.	 */



node* build_dfs_tree (int order, int** adj_mat, int node_index,  int* marked){

	node* ptr_current_node = create_node(node_index);
	
	marked[node_index] = 1;
	printf("%d ", node_index);
	int* v = adj_mat[node_index];

	for(int x=0; x<order; x++){
		if(marked[x] == 0 && v[x] == 1){
			
			node* temp = build_dfs_tree(order, adj_mat, x, marked);
			// ptr_current_node->ptr_children_list = temp;
			if(ptr_current_node->ptr_children_list != NULL){
				node* curr = ptr_current_node->ptr_children_list;
				while(curr->ptr_sibling != NULL)
					curr = curr->ptr_sibling;
				curr->ptr_sibling = temp;
			}
			else
				ptr_current_node->ptr_children_list = temp;
		}

	}

	return ptr_current_node;
}

	
/*Task 1: Build DFS Forest*/
/*Input: Order of the graph and pointer to the adjacency matrix of the graph*/
/*Output: Pointer to the list of root nodes of the DFS trees of the forest */

node* build_dfs_forest (int order, int ** adj_mat){

	node* ptr_root_node_list = create_node(0);

	int* marked = calloc(order, sizeof(int));
	for(int i=0; i<order; i++){
		if(marked[i] == 0){
			node* temp = build_dfs_tree(order, adj_mat, i, marked);
			if(ptr_root_node_list->ptr_sibling != NULL){
				node* curr = ptr_root_node_list->ptr_sibling;
				while(curr->ptr_sibling != NULL)
					curr = curr->ptr_sibling;
				curr->ptr_sibling = temp;
			}
			else
				ptr_root_node_list->ptr_sibling = temp;
		}
	}
	
	
	return ptr_root_node_list;
}

/*Task 2: Order the vertices of the graph in such a way so that each vertex has at least one neighbour to its right except for C number of vertices where C is the*/
/*number of component of the graph.*/

/*Example output: u, v, w, x, y, z*/
/*In the above example u has at least one neighbour among {v,w,x,y,z}. Similarly v has at least one neighbout among {w,x,y,z}, and so on.*/

/*Input: Order and pointer to the adjacency matrix of the graph.*/

int print_with_right_neighbour (int order, int** adj_mat){
	
	int* marked = calloc(order, sizeof(int));
	
	for(int i=0; i<order; i++){
		if(marked[i] == 0){
			node* tree = build_dfs_tree(order, adj_mat, i, marked);
			printf("\n");
		}
	}

	return 0;
}


/*Delete DFS tree: Delete the DFS tree by freeing all its nodes systematically. The function should print the index of the node getting deleted.

Example output: 

Deleting node 7
Deleting node 12
      :
      :
      :
	 
Input: Pointer to the root node of the tree.*/

int delete_dfs_tree(node* ptr_root_node){

	if(ptr_root_node != NULL){
		while(ptr_root_node->ptr_children_list != NULL){
			node* temp = ptr_root_node->ptr_children_list;
			ptr_root_node->ptr_children_list = ptr_root_node->ptr_children_list->ptr_sibling;
			delete_dfs_tree(temp);
		}


		if(ptr_root_node->ptr_children_list == NULL){
			printf("Deleting %d node\n", ptr_root_node->node_index);
			free(ptr_root_node);
		}
	}
	// printf("Hit here\n");

	return 0;
}
/* Task 3: Delete the DFS forest by freeing all its nodes component-wise. The function should print the index of the node getting deleted with the nodes
belonging to the same component clubbed together. Add newlines to separate the components.

Example output: 

Deleting node 6
      :
      :
Deleting node 12

Deleting node 4
       :
       :
Deleting node 2

In the above example nodes 6,..., 12 belong to the same component and nodes 4,..., 2 belong to some other component.	 
Input: Pointer to the root node of the tree.*/

int delete_dfs_forest(node* ptr_node_list){
	if(ptr_node_list != NULL){
		while(ptr_node_list->ptr_sibling != NULL){
			node* temp = ptr_node_list->ptr_sibling;
			ptr_node_list->ptr_sibling = ptr_node_list->ptr_sibling->ptr_sibling;
			delete_dfs_tree(temp);
			printf("\n");
		}
		// printf("Deleting node %d\n", ptr_node_list->node_index);
		// free(ptr_node_list);
		// printf("1234\n");
	}
	else
		return 0;

	
}
int main(){

	int** adj_mat;
	int order, i, j;
	FILE* graph_data;
	char* row;
	node* ptr_forest;

/*Read the adjacency matrix from the given file*/

	graph_data = fopen ("graph_3","r"); // Open the file in read-only mode

	if (graph_data != NULL){

		fscanf(graph_data,"%d", &order);
		adj_mat = (int**)malloc(order* sizeof(int*));
		row = malloc((order+2) * sizeof(char));
		fgets(row,(order+2), graph_data);
		
		for (i = 0; i < order; i++){
			fgets(row,(order+2), graph_data);
			adj_mat[i] = malloc(order * sizeof(int));
			for (j=0; j < order; j++){
				adj_mat[i][j] = row[j] - '0';
			} 
		} 

		fclose(graph_data);
		
	}


/*/*Test Task 4:	*/
	ptr_forest= build_dfs_forest(order, adj_mat);
	print_dfs_forest(ptr_forest);
/*	*/
/*	printf("\n\n");*/
/*/*Test Task 5:	*/
	print_with_right_neighbour (order, adj_mat);

/*/*Test Task 6:*/
	delete_dfs_forest(ptr_forest);
	
	return 0;
}
