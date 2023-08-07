//
// Modelagem Computacional em Grafos - SCC0216
// Trabalho 2 - Pacman
// Enzo Nunes Sedenho - 13671810
// Gabriel da Costa Merlin - 12544420
// Vicenzo D'Arezzo Zilio - 13671790

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// The value was chosen through the cases possibilities.
// In this way, the biggest board handled by the algorithm
// is the one with 1000 dimension in each axis.
#define MAX 1000000

typedef struct queue Queue_t;

Queue_t *queue_create(void);

bool is_empty_queue(Queue_t *Q);

bool is_full_queue(Queue_t *Q);

void enqueue(Queue_t *Q, int e);

int dequeue(Queue_t *Q);

void queue_destroy(Queue_t **Q);

#endif
