#include <stdio.h>
#include <stdlib.h>
#include "fast_filter.h"
#include "factorial.h"
#include "array.h"

int main(){
    int list[] = {2, 1, 4, 6, 1};
    Array array = {list, sizeof(list)};
    Array* filtered_array = fast_filter(&array);
    for (int i = 0; i<filtered_array->size; i++){
        printf("%d\n", filtered_array->data[i]);
    }
    free_array(filtered_array);
    printf("Factorial of 5 is %d\n", factorial(5));
    return 0;
}