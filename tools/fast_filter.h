#pragma once
#include <stdlib.h>
#include "array.h"

Array* fast_filter(Array* array) {
    Array* filtered_array = malloc(sizeof(Array));
    filtered_array->data = malloc(array->size);
    filtered_array->size = array->size;
    filtered_array->elements_nb = array->elements_nb;
    if (filtered_array->data == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    
    for(int i = 0; i<array->elements_nb; i++){
        int min = array->data[0];
        int min_index = 0;
        for(int j = 1; j<array->elements_nb; j++){
            if (array->data[j] < min)
            {
                min = array->data[j];
                min_index = j;
            }
        }
        filtered_array->data[i] = min;
        array->data[min_index] = INT_MAX;
        printf("Min: %d\n", min);
    }

    return filtered_array;
    // Don't forget to free the memory after using it by using free(filtered_array)
}