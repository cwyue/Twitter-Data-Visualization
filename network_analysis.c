/*
 * network_analysis.c
 *
 *  Created on: 2016年10月24日
 *      Author: Administrator
 */
/*
 * network_anlysis.c
 *
 *  Created on: 2016年10月19日
 *      Author: Administrator
 */
#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#include "network_analysis.h"




/*Calculate the max_distance of all nodes in the graph and find
 * the diameter of the whole graph;
 * Create a "information array" to temporarily store the distance from
 * one specific source node to all other nodes, and "states" of all nodes;
 * At the beginning of each iteration, initialize this "information array"
 * and gradually update the information as the FIFO queue works.
 * */
void network_diameter(PGRAPH pGraph){
	PINFO pInfo=(PINFO)malloc(pGraph->node_number*sizeof(INFO));
	QUEUE fifo;
	init_queue(&fifo);
	for(int i=0;i<pGraph->node_number;i++){
		one_diameter(pGraph,i,pInfo,&fifo);
	}
	free(pInfo);
	//free the storage for "information array" after all distances are calculated
	pInfo=NULL;
	free(fifo.pHead);
}



/*Initialize the "information array".
 * Set all distances and states to 0,
 * except that the state of source node is "1"(added to the FIFO queue)
 * */
void init_infoList(PINFO pInfo,int N,int source){
	for(int i=0;i<N;i++){
		pInfo[i].distance=0;
		if(i==source){
			pInfo[i].state=1;
		}else{
			pInfo[i].state=0;
		}
	}
}


//calculate the max distance from one source node to all other nodes
void one_diameter(PGRAPH pGraph,int source,PINFO pInfo,PQ pQ){
	//initialize the "information array"
	init_infoList(pInfo,pGraph->node_number,source);

	//add the source node to FIFO queue
	add_event(pQ,source);

	//initialize max_distance and number of farthest nodes
	int max_distance=0;
	//number_of_far is a count number for farthest nodes
	int number_of_far=0;


	/*When the FIFO queue is not empty, in each iteration pop one
	 * node, set its state into "2"(already processed), update the
	 * state and distance of its neighbors in state "0" and add it
	 * to the FIFO queue;
	 * If distance of some node equals current max_distance, the
	 * count number for farthest nodes increases by 1;
	 * If distance of some node is greater than current max_distance,
	 * update current max_distance and reset number_of_far to 1;
	 * */
	while(pQ->pHead->pNext!=NULL){
		int current_node=pop_node(pQ);
		pInfo[current_node].state=2;
		PNODE temp=pGraph->pList[current_node].pNeighbour;
		while(temp!=NULL){
			if(pInfo[temp->node_number].state==0){
				pInfo[temp->node_number].state=1;
				pInfo[temp->node_number].distance=pInfo[current_node].distance+1;
				if(pInfo[temp->node_number].distance>max_distance){
					max_distance=pInfo[temp->node_number].distance;
					number_of_far=1;
				}else if(pInfo[temp->node_number].distance==max_distance){
					number_of_far++;
				}
				add_event(pQ,temp->node_number);
			}
			temp=temp->pNext;

		}

	}
	//record the max_distance and number_of_far into the graph list
	pGraph->pList[source].max_distance=max_distance;
	pGraph->pList[source].number_of_far=number_of_far;

	//add farthest nodes to the "far nodes array" of this source node
	add_far_node(pGraph,source,pInfo);


	/*If max_distance of this source node is larger than the diameter
	 * of the whole graph, then update the diameter;
	*/
	if(max_distance>pGraph->diameter){
		pGraph->diameter=max_distance;
	}
}

//initialize the FIFO queue and let its pHead point to a head node
void init_queue(PQ pQ){
	pQ->pHead=(PFNODE)malloc(sizeof(FNODE));
	if(pQ->pHead==NULL){
		exit(-1);
	}
	pQ->pHead->pNext=NULL;
}


//add one node to be processed into the FIFO queue
void add_event(PQ pQ,int node_number){
	PFNODE pNew=(PFNODE)malloc(sizeof(FNODE));
	if(pNew==NULL){
		exit(-1);
	}
	pNew->pNext=NULL;
	pNew->id=node_number;
	PFNODE temp=pQ->pHead;
	while(temp->pNext!=NULL){
		temp=temp->pNext;
	}
	temp->pNext=pNew;
}

//delete the first node in the FIFO queue and return its id number
int pop_node(PQ pQ){
	if(pQ->pHead->pNext==NULL){
		printf("no node in the queue!\n");
		return -1;
	}
	PFNODE temp=pQ->pHead->pNext;
	int node_number=temp->id;
	pQ->pHead->pNext=temp->pNext;
	free(temp);
	return node_number;
}

//show all nodes in the FIFO queue (used for program test)
void show_queue(PQ pQ){
	PFNODE temp=pQ->pHead->pNext;
	while(temp!=NULL){
		printf("%d",temp->id);
		temp=temp->pNext;
	}
	printf("\n");
}


/*create an "far nodes array" to store id number of the farthest nodes
 * from a source node. The length of this array is already recorded
 * in the variable "number_of_far";
 * Scan the "information array" of a source node and add one node to
 * the "far nodes array" if the distance of this node from the source
 * node equals "max_distance" of the source node.
*/
void add_far_node(PGRAPH pGraph,int source,PINFO pInfo){
	int number_of_far=pGraph->pList[source].number_of_far;
	if(number_of_far==0){
		return;
	}
	pGraph->pList[source].farList=(int *)malloc(number_of_far*sizeof(int));
	if(pGraph->pList[source].farList==NULL){
		exit(-1);
	}
	int j=0;
	for(int i=0;i<pGraph->node_number;i++){
		if(pInfo[i].distance==pGraph->pList[source].max_distance){
			pGraph->pList[source].farList[j]=i;
			j++;
		}
	}
}


