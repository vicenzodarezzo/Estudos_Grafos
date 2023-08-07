//
//  graph.h
//  Trabalho 1 - Grafos
//  Created by Vicenzo D’Arezzo on 31/03/23.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

// GRAPH STRUCTURES:

typedef struct edge Edge_t;

typedef struct vertice Vertice_t;

typedef struct graph Graph_t;

// STACK STRUCTURES:

typedef struct stack Stack_t;



//INT STACK FUNCTIONS:

/** create the stack pointer for the data structure */
Stack_t * stack_create(int lenght);

/** assert if the stack is empty */
bool is_empty(Stack_t *  s);

 /** assert if the stack is full */
bool is_full(Stack_t *  s);

 /** insert an int i in the top of the stack */
bool push(Stack_t * s, int i);

 /** remove the top int of the stack */
int pop(Stack_t * s);

 /** releases all pointer used in the stack data strucutere */
void stack_destroy(Stack_t ** s);

 /** print the correspondent stack */
void stack_show(Stack_t * s);

/** search an integer id in the given stack */
bool is_on_stack(Stack_t * s, int id);


//GRAPH FUNCTIONS:

/** Returns a graph with capacity dictated by the parameters.
 */
Graph_t * graph_create(int n_vertice, int n_edges);

/** Insert an edge in the dictated vertices. To form a non-oriented graph, you should call this function two times, one for each variantian of the sorted pair (starting vertice, destiny vertice).*/
Graph_t * graph_insert_oriented_edge( Graph_t * g, int id_vertice, int destiny);

/** Liberate all the pointers used to form the graph TAD.
 */
void graph_delete(Graph_t ** g);


bool graph_verify_conection(Graph_t * g, int id_vertice, int id_destiny);

/** In a non-oriented Graph, running the linked list isnt enough to atualize a flag associated to an edge, because there is an
    corresponding edge in the destiny linked list too. In that way, this function search anda atualize the destiny - vertice a - in the linked list, changing the especified edge.
 */
Graph_t * graph_notOriented_atualizeEdge(Graph_t *g, int id_vertice_a, int id_vertice_b);

void print_graph(Graph_t * graph);

/** Tarjan algorihtm is a method to find the Strongly Coneccted Components in a Graph (SCC). The heuristic relays on the properties
 of the Deapth First Search, that apply an order of discovery in the vertices and, with the recursio stack, allows us to study the conectivity
 of the vertices in the callback of the recursive calls. This information is described in the discovery_id and pre_order values, built along
 the search with the support of a auxiliar stack.
    In the end, each set of vertices with matching pre-order values signifies a SCC.
    The return value correponds to the number of founded sccs.
 */
int tarjan_SCC(Graph_t * g);

/** A procedure to show each of the strongly coneccted components of the graph in asceding order. For this, it runs the graph linnearly in the vertices, and, for the ones that are contained in a non-trivial-scc, calculates the corresponding scc squence, sorting it by the quickSort
    algorihtm implemented in stdlib.h.
 */
void printSCCs(Graph_t * g, int scc_counter);

#endif /* graph_h */
