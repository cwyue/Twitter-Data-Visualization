/*
 * main.c
 *
 *  Created on: 2016Äê10ÔÂ20ÈÕ
 *      Author: Administrator
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"
#include "network_analysis.h"

int main(int argc,char *argv[ ]){
	/*
	char* inFile="graph10.txt";
	GRAPH graph;
	create_graph(inFile,&graph);
	network_diameter(&graph);
	show_graph(&graph);
	clear_graph(&graph);
	*/
	char* inFile=argv[1];

	GRAPH graph;
	create_graph(inFile,&graph);
	network_diameter(&graph);
	if(argc>=4){
		if(strcmp(argv[2],"-o")==0){
			char* outFile=argv[3];
			output_file(&graph,outFile);
		}
	}else{
		printf("%d\t%d\n",graph.node_number,graph.diameter);
	}
	clear_graph(&graph);

	return 0;

}

