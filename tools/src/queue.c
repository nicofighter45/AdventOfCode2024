#include "queue.h"
#include "array.h"
#include <stdio.h>

Queue* create_queue(int size){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->data = (int *)malloc(size * sizeof(int));
    queue->size = size;
    queue->front = queue->rear = 0;
    queue->nb_of_elements = 0;
    queue->size = size;
    return queue;
}

void push(Queue *q, int value){
    if(q->rear == q->size){
        fprintf(stderr, "Error: Queue is full, cannot push element.\n");
        return;
    }
    q->data[q->rear] = value;
    q->rear++;
    q->nb_of_elements++;
}

int pop(Queue *q){
    if(q-> front == q->rear){
        fprintf(stderr, "Error: Queue is empty, cannot pop element.\n");
        return -1;
    }
    else{
        int value = q->data[q->front];
        q->front++;
        q->nb_of_elements--;
        return value;
    }
}

void free_queue(Queue *q){
    free(q->data);
    free(q);
}

Array* queue_to_array(Queue *q){
    Array *array = create_array(q->nb_of_elements);
    int i;
    for(i = 0; i < q->nb_of_elements; i++){
        array->data[i] = q->data[q->front + i];
    }
    return array;
}
