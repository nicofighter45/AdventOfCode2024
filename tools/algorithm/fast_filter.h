#pragma once
#include <stdlib.h>
#include "array.h"

Array* fast_filter(Array* array) {
    Array* filtered_array = create_array(array->size);    
    for(int i = 0; i<array->size; i++){
        int min = array->data[0];
        int min_index = 0;
        for(int j = 1; j<array->size; j++){
            if (array->data[j] < min)
            {
                min = array->data[j];
                min_index = j;
            }
        }
        filtered_array->data[i] = min;
        array->data[min_index] = INT_MAX;
    }
    return filtered_array;
}