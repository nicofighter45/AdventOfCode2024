#pragma once

typedef struct Matrix
{
    int** data;
    int i;
    int j;
} Matrix;

Matrix* create_matrix(int i, int j);

void free_matrix(Matrix* matrix);
