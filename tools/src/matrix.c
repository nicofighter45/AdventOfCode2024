#include <stdlib.h>
#include "matrix.h"

Matrix* create_matrix(int i, int j){
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->i = i;
    matrix->j = j;
    matrix->data = (int**)malloc(i * sizeof(int*));
    for(int k = 0; k < j; k++){
        matrix->data[i] = (int*)malloc(j * sizeof(int));
    }
    return matrix;
}

void free_matrix(Matrix* matrix){
    for(int i = 0; i < matrix->i; i++){
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}
