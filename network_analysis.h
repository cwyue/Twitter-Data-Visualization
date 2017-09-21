/*
 * network_analysis.h
 *
 *  Created on: 2016Äê10ÔÂ19ÈÕ
 *      Author: Administrator
 */
#include "graph.h"
#ifndef NETWORK_ANALYSIS_H_
#define NETWORK_ANALYSIS_H_

/* struct "info" is the element of the "information array" for one
 * specific source node. It stores the state (whether this node has been
 * processed in the FIFO queue).
 * I use 0,1,2 to represent "not processed", "added into FIFO", and
 * "already processed".
 * int "distance" stores the distance from this node to the source node.
 * */
typedef struct info{
	int state;
	int distance;
}INFO,*PINFO;


//the element in the fifo queue
typedef struct fifoNode{
	int id;
	struct fifoNode *pNext;
}FNODE,*PFNODE;

/*the struct "fifoQueue" has a pointer to a head node
*/
typedef struct fifoQueue{
	PFNODE pHead;
}QUEUE,*PQ;

void init_queue(PQ pQ);//initialize the FIFO queue

void add_event(PQ pQ,int node_number);//add one node into the FIFO queue

int pop_node(PQ pQ);
//delete one node from the queue and return its id number

void show_queue(PQ pQ);//show the nodes in the queue (used for test)

void network_diameter(PGRAPH pGraph);
//calculate the max_distance of all noedes and the diameter of graph

void init_infoList(PINFO pInfo,int N,int source);
//initialize the "information array" for one specific source node

void one_diameter(PGRAPH pGraph,int source,PINFO pInfo,PQ pQ);
//calculate the max_distance of one specific source

void add_far_node(PGRAPH pGraph,int source,PINFO pInfo);
//add farthest nodes of one source node into its "far nodes array"

#endif /* NETWORK_ANALYSIS_H_ */
