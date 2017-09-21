/*
 * main.c
 *
 *  Created on: Oct 17, 2016
 *      Author: yychu
 */

#include "generate_graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int V = strtol(argv[1],NULL,10);
	char* file_name = argv[2];
    /*for (int i = 1; i < argc; ++i)
    {
        printf("argv %s \n",argv[i]);
        if (strcmp(argv[i],"-h")==0)
        {
            
        }
    }*/
    
	srand(time(NULL));

    
	struct graph* graph = create_graph(V);
	add_edge(graph, 0, 1);
	add_edge(graph, 0, 2);
	add_edge(graph, 1, 2);
	//printGraph(graph);
	for(int i=0;i<V-3;i++) {
		add_node(graph);
		//printGraph(graph);
	}
    if (strcmp(argv[3],"-h")==0) {
        
        create_histogram(graph,argv[4]);
    }
	print_file(graph,file_name);
	//print_histo(graph);
}

