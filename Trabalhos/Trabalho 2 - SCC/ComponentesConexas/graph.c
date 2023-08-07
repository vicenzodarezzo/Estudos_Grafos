//
//  graph.c
//  Trabalho 1 - Grafos
//  Created by Vicenzo D’Arezzo on 31/03/23.
//

#include "graph.h"


// ---------------------------------------------------------
// ---------------------------------------------------------
// GRAPH STRUCTURES :
// ---------------------------------------------------------
// ---------------------------------------------------------

struct edge{
    int destiny;
    struct edge * next_edge;
};

struct vertice{
    int n_edges;
    Edge_t * inicial_edge;
    Edge_t * final_edge;
    int discovery_id; // discovery time value determined by the DFS
    int pre_order; // iddentifier of an SCC by the Tarjan's alg
    bool stack_flag; // used in the depth stack in the Tarjan's alg.
    bool visited_flag; // used in the DFS to reboot the search in a new component
    bool non_trivial_scc_member;
};

struct graph{
    int n_vertices;
    int n_edges;
    Vertice_t * vertice_vec;
};

// ---------------------------------------------------------
// ---------------------------------------------------------
// STACK STRUCTURES
// ---------------------------------------------------------
// ---------------------------------------------------------

struct stack{
    int * vec;
    int lenght;
    int top;
};

// ---------------------------------------------------------
// ---------------------------------------------------------
// STACK FUNCTIONS:
// ---------------------------------------------------------
// ---------------------------------------------------------

Stack_t * stack_create(int lenght){
    Stack_t * s = malloc(sizeof(Stack_t));
    assert(s);
    s->lenght = lenght;
    s->vec = malloc(sizeof(int) * lenght);
    assert(s->vec);
    s->top = -1;
    return s;
}

bool is_empty(Stack_t *  s){
    return (s->top < 0 ? true : false);
}

bool is_full(Stack_t *  s){
    return (s->top == s->lenght - 1 ? true : false);
}

bool push(Stack_t * s, int i){
    if(is_full(s)) return false;
    s->vec[++s->top] = i;
    return true;
}

int pop(Stack_t * s){
    if(is_empty(s)) return -1;
    else return s->vec[s->top--];
}

void stack_destroy(Stack_t ** s){
    free((*s)->vec);
    free(*s);
    *s = NULL;
}

void stack_show(Stack_t * s){
    while(!is_empty(s)){
        printf(" %d", pop(s));
    }
}

bool is_on_stack(Stack_t * s, int id){
    if(!is_empty(s)){
        for(int i = 0; i <= s->top; i++){
            if(s->vec[i] == id) return true;
        }
    }
    return false;
}

// ---------------------------------------------------------
// ---------------------------------------------------------
// GRAPH FUNCTIONS:
// ---------------------------------------------------------
// ---------------------------------------------------------

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
        g->vertice_vec[i].pre_order = 0;
        g->vertice_vec[i].stack_flag = false;
        g->vertice_vec[i].visited_flag = false;
        g->vertice_vec[i].non_trivial_scc_member = false;
    }
    return g;
}

Graph_t * graph_insert_oriented_edge( Graph_t * g, int id_vertice, int destiny){
    assert(g);
    
    //inicializing new edge
    Edge_t * edge_temp = malloc(sizeof(Edge_t));
    assert(edge_temp);
    edge_temp->destiny = destiny;
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
        printf("Vertice %d : discovery : %d | pre_order : %d\n", i, graph->vertice_vec[i].discovery_id, graph->vertice_vec[i].pre_order);
        Edge_t * aresta_aux = graph->vertice_vec[i].inicial_edge;
        while(aresta_aux != NULL){
            printf("\t%d --> %d\n", i, aresta_aux->destiny);

            aresta_aux = aresta_aux->next_edge;
        }
    }
}
// ---------------------------------------------------------
// ---------------------------------------------------------
// FINDING SCC FUNCTIONS :
// ---------------------------------------------------------
// ---------------------------------------------------------

void depth_recursion(Graph_t * g, int id_vertice, Stack_t * s, int * counter, int * scc_counter){
    
    Vertice_t * v = &g->vertice_vec[id_vertice];
    
    // SETTING UP THE VERTICE
    v->visited_flag = true;
    v->discovery_id = v->pre_order = *counter;
    push(s, id_vertice);
    v->stack_flag = true;
    
    *counter = *counter + 1; // atualizing the counter
    
    // BUILDING THE SEARCH TREE
    Edge_t * edge_runner = v->inicial_edge;
    
    while(edge_runner != NULL){
        
        if(!g->vertice_vec[edge_runner->destiny].visited_flag){
            depth_recursion(g, edge_runner->destiny, s, counter, scc_counter);
        }
        
        // Recursion callback -> to find the SCC in the graph, we need to match the vertices
        // through its pre-order value. For this, we use the callback of the searching to
        // match all vertices that have the connection to the least vertice id in the searching
        // tree ;
        
        if(is_on_stack(s, edge_runner->destiny)){
            v->pre_order = v->pre_order < g->vertice_vec[edge_runner->destiny].pre_order ?
            v->pre_order : g->vertice_vec[edge_runner->destiny].pre_order;
        }
        
        edge_runner = edge_runner->next_edge;
        
    }
    
    // VERIFYING IF THE CURRENT VERTICE IS THE START OF AN SCC
    if(v->discovery_id == v->pre_order){
        int top_vertice = -1 ;
        int scc_members_counter = 0;
        
        while(!is_empty(s) && top_vertice != id_vertice){
            top_vertice = pop(s);
            g->vertice_vec[top_vertice].stack_flag = false;
            g->vertice_vec[top_vertice].non_trivial_scc_member = true;
            scc_members_counter++;
        }
        
        // identifying vertices in non trivial SCCs
        if(scc_members_counter > 1) v->non_trivial_scc_member = true;
        
        *scc_counter = *scc_counter + 1;
    }
}

int tarjan_SCC(Graph_t * g){
    
    Stack_t * stack = stack_create(g->n_vertices);
    int counter = 0;
    int scc_counter = 0;
    
    for(int i = 0; i < g->n_vertices; i++){
        if(!g->vertice_vec[i].visited_flag){
            depth_recursion(g, i, stack, &counter, &scc_counter);
        }
    }
    
    stack_destroy(&stack);
    
    return scc_counter;
}

int int_comparator(const void * a, const void * b){
    return * (int *) a > * (int *) b ? 1 : -1 ;
}

int * computingSCCs(Graph_t * g, int * v_counter, int pre_order){
    
    *v_counter = 0;
    int * scc = NULL;
    
    for (int i = 0; i < g->n_vertices; i++){
        
        if(g->vertice_vec[i].pre_order == pre_order){
            scc = (int *) realloc(scc, sizeof(int) * (*v_counter + 1));
            assert(scc);
            scc[*v_counter] = i;
            (*v_counter)++;
            g->vertice_vec[i].visited_flag = false;
        }
    }
    
    qsort(scc, *v_counter, sizeof(int), int_comparator);
    
    return scc;
}


void printSCCs(Graph_t * g, int scc_counter){
    
    /*
     For implementation porpouse, this function will reuse the visited
     flag contained in the vertice registry, now, in this locality,
     meaning if the vertice was already printed.
     We know by the definition of the BFS that all of the vertices were
     visited in Tarjan's Alg, so, all of them, after the calling of
     the function, are marked with true;
     */
    
    int * scc_buffer = NULL;
    int v_counter;
    
    //printing the number of sccs :
    fprintf(stdout, "%d\n", scc_counter);
    
    // Finding the heads of the existing SCCs
    for(int i = 0 ; i < g->n_vertices ; i++){
        
        // checking if the vertice wasn't already printed
        if(g->vertice_vec[i].visited_flag){
            
            if(g->vertice_vec[i].non_trivial_scc_member){
                
                scc_buffer = computingSCCs(g, &v_counter, g->vertice_vec[i].pre_order);
                
                for(int j = 0; j < v_counter - 1; j++) fprintf(stdout, "%d ", scc_buffer[j]);
                fprintf(stdout, "%d\n", scc_buffer[v_counter - 1]);
                
                free(scc_buffer);
                
            }else{
                printf("%d\n", i);
            }
        }
    }
}
