#include "generate_graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct graph* create_graph(int n) {
	struct graph* graph = (struct graph*) malloc(sizeof(struct graph));
	graph->num_node= n;
	graph->current_num_node = 3;
	graph->num_degree = 0;
	graph->highest_degree = 0;
	graph->graph_array = (struct graph_head*) malloc(n*sizeof(struct graph_head));

	for (int i = 0;i<n;i++){
		graph->graph_array[i].head = NULL;
		graph->graph_array[i].num_degree = 0;
	}
	return graph;
}

void add_node(struct graph*graph) {
	double random_num = (double)rand()/(double)(RAND_MAX+1.0);
	double cumulative = 0;
	double temp = 0;
	int assigned = 0;
	int i = 0;
	while (assigned!=1 && i < graph->current_num_node){
		cumulative = cumulative + (graph->graph_array[i].num_degree/graph->num_degree);
		if(random_num>=temp && random_num<=cumulative){
			add_edge(graph,i, graph->current_num_node);
			graph->current_num_node++;
			assigned = 1;
		}
		i++;
		temp = cumulative;
	}
}

void add_edge(struct graph* graph, int source, int dest){
	graph->num_degree+=2;
	struct graph_node* new_node1 = (struct graph_node*) malloc(sizeof(struct graph_node));
	new_node1->dest = dest;
	new_node1->next = NULL;
	graph->graph_array[source].num_degree++;
	if(graph->graph_array[source].num_degree > graph->highest_degree){
		graph->highest_degree=graph->graph_array[source].num_degree;
	}
	new_node1->next = graph->graph_array[source].head;
	graph->graph_array[source].head = new_node1;

	struct graph_node* new_node2 = (struct graph_node*) malloc(sizeof(struct graph_node));
	new_node2->dest = source;
	new_node2->next = NULL;
	graph->graph_array[dest].num_degree++;
	if(graph->graph_array[dest].num_degree > graph->highest_degree){
		graph->highest_degree=graph->graph_array[dest].num_degree;
	}
	new_node2->next = graph->graph_array[dest].head;
	graph->graph_array[dest].head = new_node2;
}

void add_directed_edge(struct graph* graph, int source, int dest){
	graph->num_degree+=1;
	struct graph_node* new_node1 = (struct graph_node*) malloc(sizeof(struct graph_node));
	new_node1->dest = dest;
	new_node1->next = NULL;
	graph->graph_array[source].num_degree++;
	if(graph->graph_array[source].num_degree > graph->highest_degree){
		graph->highest_degree=graph->graph_array[source].num_degree;
	}
	new_node1->next = graph->graph_array[source].head;
	graph->graph_array[source].head = new_node1;
}

void free_graph(struct graph* graph){
	if(graph != 0){
		if(graph->graph_array !=0){
			for(int i=0; i<graph->num_node;i++){
				struct graph_node* graph_head = graph->graph_array[i].head;
				while(graph_head!=0) {
					struct graph_node* temp = graph_head;
					graph_head = graph_head->next;
					free(temp);
				}
			}
			free(graph->graph_array);
		}
		free(graph);
	}
}

void create_histogram(struct graph* graph,char* file_name){
	int size = graph->highest_degree;
	//Use a graph to store the histogram
	struct graph* histo = create_graph(size);

	for(int i = 0; i < graph->num_node;i++) {
		int degree = graph->graph_array[i].num_degree;
		//histo->graph_array[degree-1].num_degree++;
		add_directed_edge(histo,degree-1,i);
	}
	print_file(histo,file_name);
}

void print_histo(struct graph* graph) {
    int v;
    for (v = 0; v < graph->num_node; ++v)
    {
        struct graph_node* pCrawl = graph->graph_array[v].head;
        printf("\n i = %d", v);
        printf(" num = %d list:",(int)graph->graph_array[v].num_degree);
        while (pCrawl)
        {
            printf("%d,", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
    }
    printf("\n");
    printf("\n");
}

void print_file(struct graph* graph,char* filename) {
	FILE *fp;
	char file_name[30];
	strcat(filename,".txt");
	fp = fopen(filename,"w+");
    int v;
    fprintf(fp,"N = %d \n",graph->num_node);
    for (v = 0; v < graph->num_node; ++v)
    {

        struct graph_node* pCrawl = graph->graph_array[v].head;
        //fprintf(fp,"\ni = %d ", v);
        //fprintf(fp,"list:",(int)graph->graph_array[v].num_degree);
        while (pCrawl)
        {
            fprintf(fp,"%d,%d \n",v, pCrawl->dest);
            pCrawl = pCrawl->next;
        }
    }
    fclose(fp);
}
