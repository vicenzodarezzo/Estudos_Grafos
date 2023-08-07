//
//  main.c
//  Trabalho 1 - Grafos
//  Created by Vicenzo D’Arezzo on 31/03/23.
//

#include <stdio.h>
#include "graph.h"

// FUNCTIONS:

// Read data from the specifc file and manages to open and close it correctly:
Graph_t * read_data(char file_name[100]){
    
    FILE * f;
    int n_vertices, n_edges;
    int aux_start, aux_destiny;
    
    f = fopen(file_name, "r");
    assert(f);
    fscanf(f, "%d %d\n", &n_vertices, &n_edges);
    Graph_t * g = graph_create(n_vertices, n_edges);
    
    while(!feof(f)){
        fscanf(f, "%d %d\n", &aux_start, &aux_destiny);
        // we call the insertion function two times because our graph is not oriented ;
        g = graph_insert_oriented_edge(g, aux_start, aux_destiny);
        g = graph_insert_oriented_edge(g, aux_destiny, aux_start);
    }
    
    fclose(f);
    return g;
}


int main(int argc, const char * argv[]) {
    
    // reading the name of the text file ;
    char file_name[100];
    fscanf(stdin, "%s", file_name);
    fflush(stdin);

    // passes the file info to the Graph data structure ;
    Graph_t * g = read_data(file_name);

    // find and print the eulerian path if the graph is eulerian ;
    hierholzer(g, 0);

    graph_delete(&g);
    
    return 0;
}
