/*
 * graph.c
 *
 *  Created on: 2016Äê10ÔÂ19ÈÕ
 *      Author: Administrator
 */
#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#include "network_analysis.h"

void init_graph(int N,PGRAPH pGraph){ //initialize the graph
	pGraph->node_number=N;
	pGraph->diameter=0;
	pGraph->pList=(PSOURCE)malloc(N*sizeof(SOURCE));
	if(pGraph->pList==NULL){
		exit(-1);
	}
	for(int i=0;i<N;i++){
		pGraph->pList[i].pNeighbour=NULL;
		pGraph->pList[i].farList=NULL;
		pGraph->pList[i].max_distance=0;
	}
}


//add one neighbour node to the adjacency linked list of a source node
void add_neighbour(PGRAPH pGraph,int source,int neighbour){
	if(source>=pGraph->node_number){
		printf("source number can't be greater than %d!\n",pGraph->node_number-1);
		return;
	}

	PNODE pNew=(PNODE)malloc(sizeof(NODE));
	//allocate storage for a new neighbor node

	if(pNew==NULL){
		exit(-1);
	}
	pNew->node_number=neighbour;
	pNew->pNext=NULL;

	//add this new node to the neighbor list of source node
	PNODE temp=pGraph->pList[source].pNeighbour;
	if(temp==NULL){
		pGraph->pList[source].pNeighbour=pNew;
	}else{
		while(temp->pNext!=NULL){
			temp=temp->pNext;
		}
		temp->pNext=pNew;
	}
}




//free the storage for the adjacency linked list of one source node
void clear_neighbours(PGRAPH pGraph,int source){
	if(pGraph->pList[source].pNeighbour==NULL){ //if there are no far nodes..
		return;
	}else{
		PNODE temp=pGraph->pList[source].pNeighbour->pNext;
		while(temp!=NULL){
			temp=temp->pNext;
			free(pGraph->pList[source].pNeighbour->pNext);
			pGraph->pList[source].pNeighbour->pNext=temp;
		}
		free(pGraph->pList[source].pNeighbour);
		pGraph->pList[source].pNeighbour=NULL;

	}
}

//free the storage for the whole graph
void clear_graph(PGRAPH pGraph){
	for(int i=0;i<pGraph->node_number;i++){
		clear_neighbours(pGraph,i);
		free(pGraph->pList[i].farList);
		pGraph->pList[i].farList=NULL;
	}
	free(pGraph->pList);
	pGraph->pList=NULL;
}

//print the information of one graph into console
void show_graph(PGRAPH pGraph){
	int N=pGraph->node_number;
	printf("graph diameter=%d\n",pGraph->diameter);
	for(int i=0;i<N;i++){
		printf("node%d: ",i);
		printf("max distance=%d   ",pGraph->pList[i].max_distance);
		printf("farthest nodes:");
		for(int j=0;j<pGraph->pList[i].number_of_far;j++){
			printf("%d,",pGraph->pList[i].farList[j]);
		}
		PNODE temp2=pGraph->pList[i].pNeighbour;
		printf("\tneighbors:");
		while(temp2!=NULL){
			printf("%d,",temp2->node_number);
			temp2=temp2->pNext;
		}
		printf("\n");
	}
}


/*write the information of a graph(diameter of the graph,
 * and the farthest nodes from each source node) into a file.
*/
void output_file(PGRAPH pGraph,char* fileName){
	FILE* out_file=fopen(fileName,"w");
	if(out_file==NULL){
		printf("cannot open the file!\n");
		exit(EXIT_FAILURE);
	}

	//use fprintf() function to write information into the file
	fprintf(out_file,"Graph diameter=%d\n",pGraph->diameter);

	for(int i=0;i<pGraph->node_number;i++){
		fprintf(out_file,"node number=%d: ",i);
		fprintf(out_file,"max distance=%d   ",pGraph->pList[i].max_distance);
		fprintf(out_file,"farthest nodes:");
		for(int j=0;j<pGraph->pList[i].number_of_far;j++){
			fprintf(out_file,"%d,",pGraph->pList[i].farList[j]);
		}

		fprintf(out_file,"\n");
	}


		fflush(out_file);
		fclose(out_file); //close the file after wrting information


}

