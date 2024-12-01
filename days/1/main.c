#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "fast_filter.h"


Array* create_array(int size) {
    Array *array = malloc(sizeof(Array));
    array->data = malloc(size*sizeof(int));
    array->size = size;
    return array;
}

int distance(Array *arr1, Array *arr2, int i){
    int distance = 0;
    for (int l = 0; l < i; l++)
    {
        distance += abs(arr1->data[l] - arr2->data[l]);
    }
    return distance;
}

int similarity(Array *arr1, Array *arr2, int k){
    int similarity = 0;
    int l = 0;
    for (int i = 0; i < k; i++)
    {
        for(int j = l; j < k; j++){
            if(arr1->data[i] > arr2->data[j]){
                l++;
            }else if(arr1->data[i] == arr2->data[j]){
                similarity+=arr1->data[i];
                l++;
            }else{
                break;
            }
        }
    }
    return similarity;
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    int *a1 = (int *)malloc(10000 * sizeof(int));
    int *a2 = (int *)malloc(10000 * sizeof(int));
    char ch;
    char *chars = (char *)malloc(10 * sizeof(char));
    int i, j, k = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            a2[j] = atoi(chars);
            j++;
            k = 0;
            chars = (char *)malloc(10 * sizeof(char));
        }
        else if (ch == ' ')
        {
            if(k > 0){
                a1[i] = atoi(chars);
                i++;
                k = 0;
                chars = (char *)malloc(10 * sizeof(char));
            }else{
                k = 0;
            }
            
        }
        else
        {
            chars[k] = ch;
            k++;
        }
    }
    fclose(file);
    free(chars);
    
    Array *arr1 = create_array(i);
    Array *arr2 = create_array(j);
    for (int l = 0; l < i; l++)
    {
        arr1->data[l] = a1[l];
    }
    for (int l = 0; l < j; l++)
    {
        arr2->data[l] = a2[l];
    }

    arr1 = fast_filter(arr1);
    arr2 = fast_filter(arr2);



    printf("Distance: %d\nSimilarity: %d", distance(arr1, arr2, i), similarity(arr1, arr2, i));
    
    return 0;
}