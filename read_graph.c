/*
 * read_graph.c
 *
 *  Created on: 2016Äê10ÔÂ19ÈÕ
 *      Author: Administrator
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"
#include "network_analysis.h"




void create_graph(char* fileName,PGRAPH pGraph){
	char* name=fileName;
	char oneLine[20];//a string to store information of one line of file

	char* number1;
	char* number2;
	//this two variables stores the id number of one node temporarily

	int source_number=0;

	FILE* in_file=fopen(name,"r");
	if(in_file==NULL){
		printf("cannot open the file!\n");
		exit(EXIT_FAILURE);
	}


	/*read the first line and get the number of nodes(N);
	 * here I use strtok() function to read one digital number from
	 * one line. The separator is " N=\n";
	 * initialize the graph list with this "N";
	 * */
	if(fgets(oneLine,20,in_file)==NULL){
		printf("this file doesn't record node numbers!");
	}else{
		number1 = strtok(oneLine," N=\n");
		if(number1!=NULL){
			int node_number=atoi(number1);
			init_graph(node_number,pGraph);
		}
	}


	/* read the subsequent lines. In each line, it stores the id number
	 * of a source node(the left one) in "number1" variable and
	 * the id number of one of its neighbor(the right one) in "number2".
	 * Add the neighbor node to the adjacency list of source node.
	 */
	while(fgets(oneLine,20,in_file)!=NULL&&source_number<pGraph->node_number){
		number1 = strtok(oneLine," ,\n");
		number2 = strtok(NULL," ,\n");
		if(number1!=NULL&&number2!=NULL){
			add_neighbour(pGraph,atoi(number1),atoi(number2));
		}


	}

	return;
}
