/*
 * graph.h
 *
 *  Created on: 2016Äê10ÔÂ19ÈÕ
 *      Author: Administrator
 */

#ifndef GRAPH_H_
#define GRAPH_H_

/** struct "node" is used to store the id of each node
 * and a pointer to the next node
 */
typedef struct node{
	int node_number;
	struct node* pNext;
}NODE,*PNODE;


/** struct "sourceNode" is the element in the graph's list and it stores
 * the basic information of this node;
 * int max_distance stores the max distance from this source node
 * to any other node; int * farList points to an array which stores the
 * id number of the farthest nodes from this source node;
 * pNeighbour is a pointer to the first neighbour of this source node;
 * "number_of_far" stores the number of farthest nodes from source node
 */

typedef struct sourceNode{
	int max_distance;
	int * farList;
	int number_of_far;
	PNODE pNeighbour;
}SOURCE,*PSOURCE;

/** struct "graph" has a pointer to the list of struct "sourceNode"
 * "node_number" records how many nodes are in this graph;
 * "diameter" stores the diameter of this graph
 */

typedef struct graph{
	int node_number;
	int diameter;
	PSOURCE pList;
}GRAPH,*PGRAPH;


void init_graph(int N,PGRAPH pGraph); //initialize the graph list

void add_neighbour(PGRAPH pGraph,int source,int neighbour);
//add one neighbour node to the adjacency linked list of a source node

void show_graph(PGRAPH pGraph);

void clear_neighbours(PGRAPH pGraph,int source);
//free the storage for one adjacency linked list

void clear_graph(PGRAPH pGraph);

void create_graph(char* fileName,PGRAPH);
//read the content of one file and create a graph accordingly

void output_file(PGRAPH pGraph,char* fileName);
//write the information of graph into a file

#endif /* GRAPH_H_ */
