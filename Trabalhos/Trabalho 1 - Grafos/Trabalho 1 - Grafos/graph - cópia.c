//
//  graph.c
//  Trabalho 1 - Grafos
//  Created by Vicenzo D’Arezzo on 31/03/23.
//

#include "graph.h"

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

// STACK STRUCTURES

struct stack{
    int * vec;
    int lenght;
    int top;
};


// STACK FUNCTIONS:

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

// GRAPH FUNCTIONS:

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

Graph_t * graph_notOriented_atualizeEdge(Graph_t *g, int id_vertice_a, int id_vertice_b){
    Edge_t * interation_pointer = g->vertice_vec[id_vertice_a].inicial_edge;
    while(interation_pointer != NULL){
        if(interation_pointer->destiny == id_vertice_b){
            interation_pointer->eulerian_flag = true;
            break;
        }else{
            interation_pointer = interation_pointer->next_edge;
        }
    }
    return g;
}

void eulerian_path_printing(Stack_t * s, int inicial_vertice){
    int top = pop(s);
    if(top == inicial_vertice){
        printf("%d", top);
        stack_show(s);
        printf(" %d\n", inicial_vertice);
    }else{
        printf("%d %d", inicial_vertice, top);
        stack_show(s);
        printf("\n");
    }
}

void hierholzer(Graph_t * g, int inicial_vertice){
    
    int current_vertice = inicial_vertice;
    Stack_t * vertices_stack = stack_create(g->n_edges);
    Stack_t * output_stack = stack_create(g->n_edges);
    bool path_existence;
    bool eulerian_graph = true;
    Edge_t * interation_pointer;
    
    
    push(vertices_stack, current_vertice);
    
    while(!is_empty(vertices_stack) && eulerian_graph){
        current_vertice = vertices_stack->vec[vertices_stack->top];
        interation_pointer = g->vertice_vec[current_vertice].inicial_edge;
        path_existence = false;
        
        //Checking the parity of the edges number in each vertice, to assert that
        //The graph is an eulerian cycle. If it isn`t, we stop the algorithm
        if(g->vertice_vec[current_vertice].n_edges % 2 == 1) eulerian_graph = false;
        
        // pushing free edge`s destiny in the vertices stack
        while(interation_pointer != NULL && eulerian_graph){
            if(interation_pointer->eulerian_flag == false){
                path_existence = true;
                //atualize the eulerian flag
                g = graph_notOriented_atualizeEdge(g, interation_pointer->destiny, current_vertice);
                interation_pointer->eulerian_flag = true;
                //push in the vertice stack:
                push(vertices_stack, interation_pointer->destiny);
                break;
            }
            
            interation_pointer = interation_pointer->next_edge;
        }
        
        if(!path_existence && eulerian_graph){
            // in the case of a satureted vertice, we put it
            // in the output stack to form the eulerian cycle
            pop(vertices_stack);
            push(output_stack, current_vertice);
        }
    }
    
    printf(eulerian_graph ? "Sim\n" : "Não\n");
    if(eulerian_graph) eulerian_path_printing(output_stack, inicial_vertice);
    
    stack_destroy(&vertices_stack);
    stack_destroy(&output_stack);
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
