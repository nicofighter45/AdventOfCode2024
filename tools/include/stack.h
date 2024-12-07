#pragma once

typedef struct Stack
{
    int* data;
    int size;
    int nb_of_elements;
} Stack;

Stack* create_pile(int nb_of_elements);

void push(Stack* pile, int element);

int pop(Stack* pile);

void free_pile(Stack* pile);

void print_pile(Stack* pile);
