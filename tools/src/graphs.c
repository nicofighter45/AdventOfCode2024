#include "graphs.h"

Graph* create_graph(int vertices_nb){
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices_nb = vertices_nb;
    graph->adjacency_matrix = (int**)malloc(vertices_nb * sizeof(int*));
    for(int i = 0; i < vertices_nb; i++){
        graph->adjacency_matrix[i] = (int*)malloc(vertices_nb * sizeof(int));
    }
    return graph;
}

void free_graph(Graph* graph){
    for(int i = 0; i < graph->vertices_nb; i++){
        free(graph->adjacency_matrix[i]);
    }
    free(graph->adjacency_matrix);
    free(graph);
}
