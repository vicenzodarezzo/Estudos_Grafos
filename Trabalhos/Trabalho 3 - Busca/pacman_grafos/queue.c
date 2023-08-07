//
// Modelagem Computacional em Grafos - SCC0216
// Trabalho 2 - Pacman
// Enzo Nunes Sedenho - 13671810
// Gabriel da Costa Merlin - 12544420
// Vicenzo D'Arezzo Zilio - 13671790

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

struct queue
{
    int start, end, total;
    int items[MAX];
};

Queue_t *queue_create(void)
{
    Queue_t *temp = malloc (sizeof(Queue_t));
    assert(temp != NULL);

    temp->start = 0;
    temp->end = 0;
    temp->total = 0;

    return temp;
}

bool is_full_queue(Queue_t *Q)
{
    if(Q != NULL)
    {
        if(Q->total == MAX)
            return true;
        return false;
    }
    else
    {
        return false;
    }
}

bool is_empty_queue(Queue_t *Q)
{
    if(Q != NULL)
    {
        if(Q->total == 0)
            return true;
        return false;
    }
    else
    {
        return false;
    }
}

void enqueue(Queue_t *Q, int e)
{
    if(!is_full_queue(Q))
    {
        Q->items[Q->end] = e;
        Q->end = (Q->end + 1) % MAX;
        Q->total++;
    }
    else
        printf("Enqueue error!\nFull queue\n");
}

int dequeue(Queue_t *Q)
{
    int item;
    if(!is_empty_queue(Q))
    {
        item = Q->items[Q->start];
        Q->start = (Q->start + 1) % MAX;
        Q->total--;
        return item;
    }else{
        printf("Dequeue error!\nEmpty queue\n");
        return -1;
    }
}

void queue_destroy(Queue_t **Q)
{
    int removed;
    
    if(Q != NULL && *Q != NULL)
    {
        while(!is_empty_queue(*Q)) removed = dequeue(*Q);
        
        free(*Q);
        *Q = NULL;
    }
}
