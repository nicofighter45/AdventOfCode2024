#include <stdlib.h>
#include <stdio.h>
#include "array.h"

int number_of_safe_reports(int **matrice){
    int total = 0;
    for(int i = 0; i <1000; i++){
        int growing = 0;
        for(int j = 1; j<matrice[i][0]-1; j++){
            int increase = matrice[i][j+1]-matrice[i][j];
            if(increase > 3){
                break;
            }
            if(increase < -3){
                break;
            }
            if(increase == 0){
                break;
            }
            if(j == 1){
                    if(increase > 0){
                        growing = 1;
                    }else{
                        growing = -1;
                    }
                }else{
                    int temp = 0;
                    if(increase > 0){
                        temp = 1;
                    }else{
                        temp = -1;
                    }
                    if(temp != growing){
                        break;
                    }
                }

            if(j == matrice[i][0]-2){
                total+=1;
            }
        }
    }
    return total;
}

int checkArray(int *array, int size)
{
    int growing = 0;
    for (int j = 0; j < size - 1; j++)
    {
        int increase = array[j + 1] - array[j];
        if (increase > 3 || increase < -3 || increase == 0)
        {
            return 0;
        }
        if (j == 0)
        {
            if (increase > 0)
            {
                growing = 1;
            }
            else
            {
                growing = -1;
            }
        }
        else
        {
            int temp = 0;
            if (increase > 0)
            {
                temp = 1;
            }
            else
            {
                temp = -1;
            }
            if (temp != growing)
            {
                break;
            }
        }

        if (j == size - 2)
        {
            return 1;
        }
    }
    return 0;
}

int problem_dumper(int** matrice){
    int total = 0;
    for(int i = 0; i <1000; i++){
        int size = matrice[i][0]-1;
        int* array = (int*) malloc(sizeof(int)*(size));
        for(int k = 0; k<size; k++){
            array[k] = matrice[i][k+1];
        }
        if(checkArray(array, size) == 1){
            total+=1;
            free(array);
            continue;
        }
        free(array);
        for(int j = 0; j < size; j++){
            int* array = (int*) malloc(sizeof(int)*(size-1));
            int deviation = 0;
            for (int k = 0; k < size-1; k++)
            {
                if(k==j){
                    deviation = 1;
                }
                array[k] = matrice[i][k + 1 + deviation];
            }
            if (checkArray(array, size-1) == 1)
            {
                total += 1;
                break;
            }
            free(array);
        }
    }
    return total;
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    int** matrice = (int**) malloc(sizeof(int*)*1000);
    for(int l = 0; l < 1000; l++){
        matrice[l] = (int*) malloc(sizeof(int)*10);
    }
    char ch;
    char *chars = (char *)malloc(3 * sizeof(char));
    int k = 0;
    int j = 1;
    int i = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n' || ch == ' ')
        {
            matrice[i][j] = atoi(chars);
            if(ch == '\n'){
                matrice[i][0] = j+1;
                i++;
                j = 0;
            }
            j++;
            k = 0;
            chars = (char *)malloc(3 * sizeof(char));
        }
        else
        {
            chars[k] = ch;
            k++;
        }
    }
    fclose(file);
    free(chars);
    
    

    printf("Number of safe reports: %d\nNumber of report with dumper: %d", number_of_safe_reports(matrice), problem_dumper(matrice));

    return 0;
}