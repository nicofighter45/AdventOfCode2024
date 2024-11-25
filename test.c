#include <stdio.h>
#include <stdlib.h>
#include "tools/fast_filter.h"
#include "tools/factorial.h"
#include "tools/array.h"

int main(){
    int list[] = {2, 1, 4, 6, 1};
    Array array = {list, sizeof(list), sizeof(list)/sizeof(int)};
    Array* filtered_array = fast_filter(&array);
    for (int i = 0; i<filtered_array->elements_nb; i++){
        printf("%d\n", filtered_array->data[i]);
    }
    free(filtered_array);
    printf("Factorial of 5 is %d\n", factorial(5));
    return 0;
}