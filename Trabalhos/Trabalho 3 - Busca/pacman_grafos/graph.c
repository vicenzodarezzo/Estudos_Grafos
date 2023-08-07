//
// Modelagem Computacional em Grafos - SCC0216
// Trabalho 2 - Pacman
// Enzo Nunes Sedenho - 13671810
// Gabriel da Costa Merlin - 12544420
// Vicenzo D'Arezzo Zilio - 13671790

#include "graph.h"
#include "queue.h"

// GRAPH STRUCTURES :

struct edge{
    int destiny;
    bool eulerian_flag;
    struct edge * next_edge;
};

struct vertice{
    int n_edges;
    Edge_t * inicial_edge;
    Edge_t * final_edge;
};

struct graph{
    int n_vertices;
    int n_edges;
    Vertice_t * vertice_vec;
};


// CARTESIAN MATRIX SETUP FUNCTIONS --------------------------------------------------

int **alocate_square_matrix(int n) {
    int **matrix = (int **) malloc(n * sizeof(int *));
    assert(matrix);
    for(int i = 0; i < n; i++){
        matrix[i] = (int *) malloc(n * sizeof(int));
        assert(matrix[i]);
    }

    return matrix;
}

void fill_matrix(int **matrix, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf(" %d", &matrix[i][j]);
        }
    }
}

void delete_matrix(int **matrix, int n){
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

bool check_conection(int **matrix, int n, int i1, int j1, int i2, int j2){
    if(i2 == -1 || j2 == -1)
        return false;

    if(i2 >= n || j2 >= n)
        return false;
    
    if(matrix[i1][j1] == 1 || matrix[i2][j2] == 1)
        return false;

    return true;
}

int calculate_id(int n, int i, int j){
    return (i * n) + j;
}

// GRAPH SETUP FUNCTIONS: --------------------------------------------------

Graph_t * graph_create(int n_vertice, int n_edges){
    Graph_t * g = malloc(sizeof(Graph_t));
    assert(g);
    g->n_vertices = n_vertice;
    g->n_edges = n_edges;
    g->vertice_vec = malloc(n_vertice * sizeof(Vertice_t));
    assert(g->vertice_vec);
    for (int i = 0; i < n_vertice; i++){
        g->vertice_vec[i].n_edges = 0;
        g->vertice_vec[i].inicial_edge = g->vertice_vec[i].final_edge = NULL;
    }
    return g;
}

Graph_t * graph_insert_oriented_edge( Graph_t * g, int id_vertice, int destiny){
    assert(g);
    
    //inicializing new edge
    Edge_t * edge_temp = malloc(sizeof(Edge_t));
    assert(edge_temp);
    edge_temp->destiny = destiny;
    edge_temp->eulerian_flag = false;
    edge_temp->next_edge = NULL;
    
    // asserting if the edge already exist in the edges_vec:
    if(graph_verify_conection(g, id_vertice, destiny)){
        free(edge_temp);
        return g;
    }
    
    //updating the list and conecting the new edge
    if(g->vertice_vec[id_vertice].inicial_edge == NULL){
        //empty list case:
        g->vertice_vec[id_vertice].inicial_edge = edge_temp;
    }else{
        g->vertice_vec[id_vertice].final_edge->next_edge = edge_temp;
    }
    g->vertice_vec[id_vertice].final_edge = edge_temp;
    g->vertice_vec[id_vertice].n_edges++;
    
    return g;
}

// Auxiliar function used to erase each pointer in a linked list
void recursive_erasing(Edge_t * end, Edge_t * current){
    if(current == end){
        free(end);
    }else{
        recursive_erasing(end, current->next_edge);
        free(current);
    }
}

bool graph_verify_conection(Graph_t * g, int id_vertice, int id_destiny){
    
    bool returned_flag = false;
    
    Edge_t * edge_pointer = g->vertice_vec[id_vertice].inicial_edge;
    
    while (edge_pointer != NULL){
        if(edge_pointer->destiny == id_destiny){
            returned_flag = true;
            break;
        } else edge_pointer = edge_pointer->next_edge;
    }
    
    return returned_flag;
}

void graph_delete(Graph_t ** g){
    assert(g && *g);
    //for each vertice, we need to be able to free all the edge pointers. In that way, the recursion run through the list, using the back of the stack to delete the current pointer, being able the remove all of them.
    for(int i = 0; i < (*g)->n_vertices; i++) recursive_erasing((*g)->vertice_vec[i].final_edge, (*g)->vertice_vec[i].inicial_edge);
    
    free((*g)->vertice_vec);
    free(*g);
    *g = NULL;
}

void print_graph(Graph_t * graph) {
    for(int i = 0; i < graph->n_vertices; i++){
        Edge_t * aresta_aux = graph->vertice_vec[i].inicial_edge;
        while(aresta_aux != NULL){
            printf("%d --> %d\n", i, aresta_aux->destiny);

            aresta_aux = aresta_aux->next_edge;
        }
    }
}

Edge_t * get_initial_edge(Graph_t *g, int position){
    return g->vertice_vec[position].inicial_edge;
}

int get_n_nodes(Graph_t *g) {
    return g->n_vertices;
}

void graph_cartesian_association(Graph_t *graph, int **matrix, int n) {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(check_conection(matrix, n, i, j, i, j - 1)){
                graph_insert_oriented_edge(graph, calculate_id(n, i, j), calculate_id(n, i, j - 1));
            }

            if(check_conection(matrix, n, i, j, i, j + 1)){
                graph_insert_oriented_edge(graph, calculate_id(n, i, j), calculate_id(n, i, j + 1));
            }

            if(check_conection(matrix, n, i, j, i - 1, j)){
                graph_insert_oriented_edge(graph, calculate_id(n, i, j), calculate_id(n, i - 1, j));
            }
                
            if(check_conection(matrix, n, i, j, i + 1, j)){
                graph_insert_oriented_edge(graph, calculate_id(n, i, j), calculate_id(n, i + 1, j));
            }

        }
    }
}


// BREADTH SEARCH FUNCTIONS : --------------------------------------------------

int isAdjListEmpty(Graph_t *G, int V){
    if (V >= G->n_vertices) {
       return(1);
    }
    else {
         if (G->vertice_vec[V].inicial_edge == NULL){
            return(1);
         }
         else{
            return(0);
         }
    }
}

Edge_t* firstInAdjList(Graph_t *G, int V){
    if (V >= G->n_vertices) {
       return(NULL);
    }
    else {
         return(G->vertice_vec[V].inicial_edge);
    }
}

void NextInAdjList(Graph_t *G, Edge_t **adj, Edge_t **prox, int *FimListaAdj) {
     * adj = * prox;
     * prox = (* prox)->next_edge;
     if (* prox == NULL)
        * FimListaAdj = 1;
}

void iter_bfs(Graph_t *graph, int node, Color_t color[], int ancestor[]) {
    int flag_end_list;
    Edge_t *edge, *aux;

    Queue_t *queue = queue_create();

    color[node] = gray;

    enqueue(queue, node);

    while (!is_empty_queue(queue)) {
        node = dequeue(queue);

        if (!isAdjListEmpty(graph, node)){
            aux = firstInAdjList(graph, node);
            flag_end_list=0;

            while (!flag_end_list) {
                NextInAdjList(graph, &edge, &aux, &flag_end_list);

                if (color[edge->destiny] == white) {
                    color[edge->destiny] = gray;
                    ancestor[edge->destiny] = node;
                
                    enqueue(queue, edge->destiny);
                }
            }
        }
        color[node]=black;
    }

    queue_destroy(&queue);
}

int *BFS(Graph_t *g, int begin, int *ancestor) {
    int number_nodes = g->n_vertices;
    Color_t color[number_nodes + 1];

    // Inicializando tudo como não visitado
    for (int node = 0; node < number_nodes; node++) {
        color[node] = white;
        ancestor[node] = -1;
    }

    iter_bfs(g, begin, color, ancestor);

    return ancestor;
}
