//
//  main.c
//  ComponentesConexas
//
//  Created by Vicenzo D’Arezzo on 31/05/23.
//

#include "graph.h"

// Read data from the specifc file and manages to open and close it correctly:
Graph_t * read_data(void){
    
    int n_vertices, n_edges;
    int aux_start, aux_destiny;
    
    // -> graph informations
    fscanf(stdin, "%d %d", &n_vertices, &n_edges);
    Graph_t * g = graph_create(n_vertices, n_edges);
  
    
    while(n_edges-- > 0){
        fscanf(stdin, " %d %d", &aux_start, &aux_destiny);
        g = graph_insert_oriented_edge(g, aux_start, aux_destiny);
    }

    return g;
}



int main(int argc, const char * argv[]) {
    
    int scc_counter;
    
    Graph_t * graph = read_data();
    
    scc_counter = tarjan_SCC(graph);
    
    printSCCs(graph, scc_counter);
    
    graph_delete(&graph);
    
    
    return 0;
}
