//
// Modelagem Computacional em Grafos - SCC0216
// Trabalho 2 - Pacman
// Enzo Nunes Sedenho - 13671810
// Gabriel da Costa Merlin - 12544420
// Vicenzo D'Arezzo Zilio - 13671790

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include "graph.h"

// ENUM to represent the variety of pacman's steps -------------------------

typedef enum {
    up, down, left, right
} Steps_t;

// Pacman Functions:  ------------------------------------------

// retraces the ancestor vector to determinate the next step for the pacman and its position
int determinating_nextStep(int phantom_position, int pacman_position, int * ancestor);

// conditional increment of the steps list
void atualizing_pacmanSteps(Steps_t * pacman_steps, int next_step, int pacman_position, int dimension);

// read from the standard input one char coded to one of the ghost movements. Based in this information,
// determinates where will be the ghost indicator replaced, returning the number of the vertice related
// to the postion
int atualizing_phantom_move_from_input(int phantom_position, int dimension);

// generates the output for the program. Has two cases, one for when the pacman finds its way to the
// ghost, other for when the ghost isn`t accessible for the pacman.
void generating_output(int pacman_position, int phantom_position, Steps_t * pacman_steps);

void input_reading(int * phantom_postion, int * pacman_position, int * max_steps, int dimension);

// Main Function: ------------------------------------------

int main(void) {
    
    /* READING THE INPUT AND CREATING THE GRAPH STRUCTURE : */
    
    int dimension;
    int ** matrix;
    int pacman_position;
    int phantom_position;
    int max_steps;
    Graph_t * graph;
    int * ancestor;
    
    scanf(" %d", &dimension);

    matrix = alocate_square_matrix(dimension);
    fill_matrix(matrix, dimension);

    graph = graph_create(pow(dimension, 2), 1);
    graph_cartesian_association(graph, matrix, dimension);
    delete_matrix(matrix, dimension);
    
    // Storing the pacman and the phantom position and locating it in the graph
    input_reading(&phantom_position, &pacman_position, &max_steps, dimension);

    Steps_t pacman_steps[4];
    pacman_steps[up] = 0;
    pacman_steps[down] = 0;
    pacman_steps[left] = 0;
    pacman_steps[right] = 0;
    
    // The list ancestor will be the precursor of the decision structure when traversing the graph.
    // each location of the vector the predecessor vertex, marking its id in the graph. If it has no
    // predecessor, it stores a logical value of -1
    
    ancestor = (int *) malloc((get_n_nodes(graph) + 1) * sizeof(int));

    /* PERSECUTION LOOP :
     * The first loop represents the persecution. In this case, as the ghost moves, the breadth
     * search is redone in orther to be able to connect the path between the two postions.
     */
    for (int n_pacman_steps = 0; n_pacman_steps < max_steps; n_pacman_steps++) {
        
        ancestor = BFS(graph, pacman_position, ancestor);
        
        int next_step = determinating_nextStep(phantom_position, pacman_position, ancestor);
        
        atualizing_pacmanSteps(pacman_steps, next_step, pacman_position, dimension);
        
        pacman_position = next_step;
        
        //checking if the pacman and the ghost shares the same postion
        if(pacman_position == phantom_position) break;
        
        phantom_position = atualizing_phantom_move_from_input(phantom_position, dimension);
        
    }
    
    
    /* FINAL MOVEMENT :
     * Now that the ghost doesn`t move anymore, we need to verify if it position is
     * accessible for the pacman and, if it is, finds the path and take it`s course.
     * Therefore, for this heuristic, only one breadth search is enough.
     */
    
    ancestor = BFS(graph, pacman_position, ancestor);
    
    while (ancestor[phantom_position] != -1 && pacman_position != phantom_position) {

        int next_step = determinating_nextStep(phantom_position, pacman_position, ancestor);
        
        atualizing_pacmanSteps(pacman_steps, next_step, pacman_position, dimension);
        
        // atualizing the pacman postion to continue the path running
        pacman_position = next_step;
    }
    
    generating_output(pacman_position, phantom_position, pacman_steps);

    free(ancestor);
    graph_delete(&graph);
}

// Functions definition :  ---------------------

void input_reading(int * phantom_postion, int * pacman_position, int * max_steps, int dimension){
    
    // Storing the pacman and the phantom position and locating it in the graph
    int x, y;
    scanf(" %d %d", &x, &y);
    *pacman_position = calculate_id(dimension, x, y);
    scanf(" %d %d", &x, &y);
    *phantom_postion = calculate_id(dimension, x, y);

    scanf(" %d", max_steps);
}



void generating_output(int pacman_position, int phantom_position, Steps_t * pacman_steps){
    if (pacman_position == phantom_position){
        
        int total_steps = pacman_steps[up] + pacman_steps[down] + pacman_steps[left] + pacman_steps[right];
        
        printf("Número de passos: %d\n", total_steps);
        printf("Movimentos para cima: %d\n", pacman_steps[up]);
        printf("Movimentos para baixo: %d\n", pacman_steps[down]);
        printf("Movimentos para esquerda: %d\n", pacman_steps[left]);
        printf("Movimentos para direita: %d\n", pacman_steps[right]);
        
    } else {
        printf("Não foi possível achar um caminho\n");
    }
}



int atualizing_phantom_move_from_input(int phantom_position, int dimension){
    char char_aux;
    int phantom_result;
    fscanf(stdin, " %c", &char_aux);
    
    switch(char_aux){
        case 'U':
            phantom_result = (phantom_position - dimension) % (int) pow(dimension, 2);
            break;
        case 'D':
            phantom_result = (phantom_position + dimension) % (int) pow(dimension, 2);
            break;
        case 'L':
            phantom_result = (phantom_position - 1) % (int) pow(dimension, 2);
            break;
        case 'R':
            phantom_result = (phantom_position + 1) % (int) pow(dimension, 2);
            break;
        default:
            fprintf(stdout, "Error in phantom movement reading\n");
            exit(1);
            break;
    }
    
    return phantom_result;
}



void atualizing_pacmanSteps(Steps_t * pacman_steps, int next_step, int pacman_position, int dimension){
    
    if(next_step == pacman_position - 1){
        pacman_steps[left]++;
    } else if(next_step == pacman_position + 1){
        pacman_steps[right]++;
    } else if(next_step == pacman_position - dimension){
        pacman_steps[up]++;
    } else if(next_step == pacman_position + dimension){
        pacman_steps[down]++;
    }
}



int determinating_nextStep(int phantom_position, int pacman_position, int * ancestor){
    
    int next_step = phantom_position;
    
    // retracing the ancestor list to calculate the first move
    while(ancestor[next_step] != pacman_position){
        if(ancestor[next_step] != -1 ){
            next_step = ancestor[next_step];
        }else{
            next_step = pacman_position;
            break;
        }
    }
    
    return next_step;
}
