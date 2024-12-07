#pragma once

#include "array.h"

typedef struct Queue {
    int *data;
    int front, rear, size, nb_of_elements;
} Queue;

Queue* create_queue(int size);

void push(Queue *q, int value);

int pop(Queue *q);

void free_queue(Queue *q);

Array* queue_to_array(Queue *q);
