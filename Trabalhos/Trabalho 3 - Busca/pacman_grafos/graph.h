//
// Modelagem Computacional em Grafos - SCC0216
// Trabalho 2 - Pacman
// Enzo Nunes Sedenho - 13671810
// Gabriel da Costa Merlin - 12544420
// Vicenzo D'Arezzo Zilio - 13671790

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

typedef enum {
    white, gray, black
} Color_t;


// CARTESIAN MATRIX FUNCTIONS:
// ---> cartesian matrix is a matrix that represents points in the cartesian plane or space.
// ---> in our case, it represents points in the plane as a logic value of 0 - free space
// ---> or 1 - occupied space.

int **alocate_square_matrix(int n);

/** Fill an allocated matrix through an line-per-line read on the standard input;
 */
void fill_matrix(int **matrix, int n);

void delete_matrix(int **matrix, int n);

/** Check conection between to cartesian point in the matrix representation.
    The possibility of exceed the limits of the matrix alocation is also tested.
 */
bool check_conection(int **matrix, int n, int i1, int j1, int i2, int j2);

/** Knowing how the points are arrenged in the input matrix, the graphs vertices
    are ennumerated from 0 to the square of the dimension. The function receives the
    values of each axis and return the number of the respective vertice in the graph.
 */
int calculate_id(int n, int i, int j);




// GRAPH SETUP FUNCTIONS:

/** Returns a graph with capacity dictated by the parameters.
 */
Graph_t * graph_create(int n_vertice, int n_edges);

/** Insert an edge in the dictated vertices. To form a non-oriented graph, you should call this function two times, one for each variantian of the sorted pair (starting vertice, destiny vertice).
 */
Graph_t * graph_insert_oriented_edge( Graph_t * g, int id_vertice, int destiny);

/** Liberate all the pointers used to form the graph TAD.
 */
void graph_delete(Graph_t ** g);

bool graph_verify_conection(Graph_t * g, int id_vertice, int id_destiny);

void print_graph(Graph_t * graph);

Edge_t *get_initial_edge(Graph_t *g, int position);

int get_n_nodes(Graph_t *g);

/** Function that relates the input reading of the cartesian matrix to the graph, asserting
    each of the conections in the current vertice.
 */
void graph_cartesian_association(Graph_t *graph, int **matrix, int n);



// BREADTH SEARCH FUNCTIONS:

/** A Breadth search algorithm that uses a system of coloring (defined as an enum in the header file) to find and process the vertices
    in the search tree. As it runs the graph by it's width, the algortihm process the predecessor of each vertice colored as black.
    This information is stored in an integer vector passad to the function in it's calling.
 */
int *BFS(Graph_t *g, int begin, int *ancestor);


#endif /* graph_h */
