#pragma once

#include "array.h"

typedef struct Graph
{
    int** adjacency_matrix;
    int vertices_nb;
} Graph;

Graph* create_graph(int vertices_nb);

void free_graph(Graph* graph);
