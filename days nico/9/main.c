#include "get_text_file.h"
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

typedef long long ulong;

void showArray(int* array, int total_length){
    for(int i = 0; i < total_length; i++){
        if(array[i] == -1){
            printf(".");
        }else{
            printf("%d", array[i]);
        }
    }
    printf("\n");
}

ulong first(File file){
    ulong total = 0;
    int total_length = 0;
    int* ini_array = (int*)malloc(file.size_of_line[0] * sizeof(int));
    for(int i = 0; i < file.size_of_line[0]; i++){
        ini_array[i] = (int) file.matrice[0][i] -48;
        total_length += ini_array[i];
    }
    int* array = (int*)malloc(total_length * sizeof(int));
    int decal = 0;
    for(int i = 0; i < file.size_of_line[0]; i++){
        if(i%2 == 1){
            for(int j = 0; j < ini_array[i]; j++){
                array[j+decal] = -1;
            }
        }else{
            int index = (int) (i+1)/2;
            for(int j = 0; j < ini_array[i]; j++){
                array[j+decal] = index;
            }
        }
        decal += ini_array[i];
    }
    
    int last_non_null = total_length-1;
    for(int i = 0; i < last_non_null; i++){        
        if(array[i] == -1){
            for(int j = last_non_null; j > i; j--){
                if(array[j] != -1){
                    array[i] = array[j];
                    array[j] = -1;
                    last_non_null = j-1;
                    break;
                }
            }
        }
    }
    
    int b = 0;
    for(int i = 0; i < total_length; i++){
        if(array[i] == -1){
            b = 1;
            continue;
        }
        ulong temp = i * array[i];
        total += temp;
    }
    
    return total;
}

ulong second(File file){
    ulong total = 0;
    int total_length = 0;
    int total_ids = (int) (file.size_of_line[0]+1)/2;
    int* ini_array = (int*)malloc(file.size_of_line[0] * sizeof(int));
    for(int i = 0; i < file.size_of_line[0]; i++){
        ini_array[i] = (int) file.matrice[0][i] -48;
        total_length += ini_array[i];
    }
    int* array = (int*)malloc(total_length * sizeof(int));
    int* positions = (int*) malloc(total_ids * sizeof(int));
    int decal = 0;
    for(int i = 0; i < file.size_of_line[0]; i++){
        if(i%2 == 1){
            for(int j = 0; j < ini_array[i]; j++){
                array[j+decal] = -1;
            }
        }else{
            int index = (int) (i+1)/2;
            positions[index] = decal;
            for(int j = 0; j < ini_array[i]; j++){
                array[j+decal] = index;
            }
        }
        decal += ini_array[i];
    }
    for(int i = total_ids -1; i > -1; i--){
        int size = ini_array[2*i];
        int space = 0;
        for(int j = 0; j < positions[i]; j++){
            if(array[j] == -1){
                space++;
                if(space == size){
                    for(int k = 0; k < size; k++){
                        array[j-(size-1)+k] = array[positions[i]+k];
                        array[positions[i]+k] = -1;
                    }
                    break;
                }
            }else{
                space = 0;
            }

        }
    }    
    
    int b = 0;
    for(int i = 0; i < total_length; i++){
        if(array[i] == -1){
            b = 1;
            continue;
        }
        ulong temp = i * array[i];
        total += temp;
    }
    
    return total;
}

int main(){
    File file = *createFile("input.txt");
    printf("First: %lld\n", first(file));
    printf("Second: %lld\n", second(file));

    return 1;
}