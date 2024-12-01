#include "stack.h"
#include <stdio.h>

Stack* create_pile(int size){
    Stack* pile = (Stack*)malloc(sizeof(Stack));
    pile->data = (int*)malloc(size*sizeof(int));
    pile->size = pile->size;
    pile->nb_of_elements = 0;
    return pile;
}

void push(Stack* pile, int element){
    if(pile->nb_of_elements + 1 > pile->size){
        fprintf(stderr, "Error: Stack is full, cannot push element.\n");
        return;
    }
    pile->data[pile->nb_of_elements] = element;
    pile->nb_of_elements++;
}

int pop(Stack* pile){
    if(pile->nb_of_elements == 0){
        fprintf(stderr, "Error: Stack is empty, cannot pop element.\n");
        return -1;
    }
    pile->nb_of_elements--;
    return pile->data[pile->nb_of_elements];
}

void free_pile(Stack* pile){
    free(pile->data);
    free(pile);
}

void print_pile(Stack* pile){
    for(int i = 0; i < pile->nb_of_elements; i++){
        printf("%d ", pile->data[i]);
    }
    printf("\n");
}
