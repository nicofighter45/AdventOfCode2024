#include "array.h"

Array* create_array(int size) {
    Array *array = malloc(sizeof(Array));
    array->data = malloc(size*sizeof(int));
    array->size = size;
    return array;
}

void free_array(Array* array) {
    free(array->data);
    free(array);
}
