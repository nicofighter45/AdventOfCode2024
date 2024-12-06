#pragma once

typedef struct Array
{
    int* data;
    int size;
} Array;

Array* create_array(int size);

void free_array(Array* array);
