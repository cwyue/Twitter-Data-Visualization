/*
 * generate_graph.h
 *
 *  Created on: Oct 16, 2016
 *      Author: yychu
 */

#ifndef SRC_GENERATE_GRAPH_H_
#define SRC_GENERATE_GRAPH_H_

struct graph_node{
	int dest;
	struct graph_node* next;
};

struct graph_head{
	double num_degree;
	struct graph_node* head;
};

struct graph{
	int num_node;
	int highest_degree;
	double num_degree;
	int current_num_node;
	struct graph_head* graph_array;
};

void print_file(struct graph* graph,char* filename);
void create_histogram(struct graph* graph,char* filename);
void add_node(struct graph*graph);
void print_histo(struct graph* graph);
struct graph* create_graph(int n);
void add_edge(struct graph* graph, int source, int dest);
void add_directed_edge(struct graph* graph, int source, int dest);
void free_graph(struct graph* graph);

#endif /* SRC_GENERATE_GRAPH_H_ */
