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

/** It is a built-in function in the hierholzer algorithm that, with a stack corresponding to the eulerian cycle, print it correctly.
 */
void eulerian_path_printing(Stack_t * s, int inicial_vertice);

/** It is an algorithm used to find a eulerian cycle in a eulerian graph. If the corresponding graph isnt eulerian, it return false, ending the process and printing "Não\n". If it is, it print "Sim\n" and use 2 stacks to run the graph and store the pathing, that is printed in the end of the process with the eulerian_path_printing  funcion. The ideia is to run through every connected component of the graph, following the eulerian path law, until it finds an sink vertice; then it returns by the created path, storing and calculating the resulting cycle.
 
 */
/** The hierlozer algorithm it self can verify if the graph is an eulerian cycle?
    Yes, it can. The algorithm pass every vertice before it finish the pathing, so if one of the vertices doesnt follow the parity rule in the vertices degree.
 */
/** How it manages to doesnt pass through brigde edges?
    The algorithm mimics the operation of the depth search by traversing all edges that make up a connected component of the graph. Then these bridges edges will only be traversed at the end, to complete the cycle.
 */
void hierholzer(Graph_t * g, int inicial_vertice);

void print_graph(Graph_t * graph);

#endif /* graph_h */
