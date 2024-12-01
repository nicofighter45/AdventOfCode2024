#pragma once

#include "queue.h"
#include "array.h"
#include "graphs.h"
#include "matrix.h"
#include <stdlib.h>

Array *breadth_first_search(Graph *graph, int initial_vertex, int final_vertex)
{
    if (initial_vertex == final_vertex)
    {
        Array *array = create_array(1);
        array->data[0] = final_vertex;
        return array;
    }
    int i;
    int current_vertex;
    Array *visited = create_array(graph->vertices_nb);
    Queue *queue = create_queue(graph->vertices_nb);
    Array *optimal_path;
    Matrix *path = create_matrix(graph->vertices_nb, graph->vertices_nb + 1);
    for (int i = 0; i < path->i; i++)
    {
        path->data[i][0] = 1;              // all paths have one vertex at the begging
        path->data[i][1] = initial_vertex; // this vertex is the initial vertex
    }
    push(queue, initial_vertex);
    while (queue->nb_of_elements > 0)
    {
        current_vertex = pop(queue);
        if (visited->data[current_vertex] == 0)
        {
            visited->data[current_vertex] = 1;
            for (i = 0; i < graph->vertices_nb; i++)
            {
                if (graph->adjacency_matrix[current_vertex][i] == 1)
                {
                    int size_of_path = path->data[current_vertex][0] + 1;
                    for (int j = 1; j < size_of_path; j++)
                    {
                        path->data[i][j] = path->data[current_vertex][j];
                    }
                    path->data[i][0] = size_of_path;
                    path->data[i][size_of_path] = current_vertex;
                    if (i == final_vertex)
                    {
                        optimal_path = create_array(path->data[i][0]);
                        for (int j = 1; j < size_of_path; j++)
                        {
                            optimal_path->data[j - 1] = path->data[i][j];
                        }
                        queue->nb_of_elements = 0;
                        break;
                    }
                    push(queue, i);
                }
            }
        }
    }
    free_array(visited);
    free_queue(queue);
    free_matrix(path);
    return optimal_path;
}
