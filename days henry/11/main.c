#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"
#include "utils.h"

struct xpoint
{
    long i,j;
};
typedef struct xpoint xpoint;

struct xint_list{
    int n;
    long* l;
};
typedef struct xint_list xint_list;

xint_list int_to_xint_list (int_list l){
    long * xl = malloc(l.n * sizeof(long));
    for (int i = 0; i < l.n; i++)
    {
        xl[i] = l.l[i];
    }
    free(l.l);
    return (xint_list){l.n,xl};
}

void print_xint_list (xint_list l){
    if (l.n < 1)
    {
        printf("tried printing list of outliers but it is empty\n");
        return;
    }
    
    for (int i = 0; i < l.n; i++)
    {
        printf("%ld ",l.l[i]);
    }
    printf("\nprinted list is of length %d\n",l.n);
}

void copy_int_list (int_list a, int_list b){
    if (a.n != b.n)
    {
        printf("Could not copy lists of different lengths\n");
    }
    
    for (int i = 0; i < a.n; i++)
    {
        a.l[i] = b.l[i];
    }
    return;
}


void append(int **array, int *size, int value) {
    // Increase the size of the array
    *array = realloc(*array, (*size + 1) * sizeof(int));
    if (*array == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    // Add the new element
    (*array)[*size] = value;
    // Increment the size
    (*size)++;
}

void appendl(long **array, int *size, long value) {
    // Increase the size of the array
    *array = realloc(*array, (*size + 1) * sizeof(long));
    if (*array == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    // Add the new element
    (*array)[*size] = value;
    // Increment the size
    (*size)++;
}

void initialize (int_list a){
    for (int i = 0; i < a.n; i++)
    {
        a.l[i] = 0;
    }
    return;
}

int digits_in(long a){
    int i = 0;
    while (a > 0)
    {
        a = a/10;
        i++;
    }    
    return i;
    
}

const long big_number = 10000000;

xpoint split (long stone){
    int d = digits_in(stone);
    if (d % 2 != 0)
    {
        printf("tried spliting a stone of odd digit lenghts\n");
    }
    int p = power(10,(d/2));
    long stone_l = stone / p;
    long stone_r = stone - stone_l * p;

    return (xpoint){stone_l,stone_r};
}


void print_stones (int_list field, xint_list outliers){
    for (int i = 0; i < field.n; i++)
    {
        for (int j = 0; j < field.l[i]; j++)
        {
            printf("%d ",i);
        }
        
    }
    printf("\nthere are %d outliers\n",outliers.n);
    
    printf("\n");
}

void next (long stone,int nb, int_list next_field,int_list nb_next_outliers,xint_list next_outliers){   
    // if stone has a 0 inscribed on it, it turns to a 1
    if (stone == 0)
    {
        next_field.l[1] += nb;
        return;
    }
    // if stone has even numaber of digits, it gets split
    else if (digits_in(stone) % 2 == 0)
    {
        next_field.l[split(stone).i] += nb;
        next_field.l[split(stone).j] += nb;
        return;
    }
    // otherwise, it gets multiplied by 2k24
    else
    {
        long new_stone = 2024 * stone;
        if (new_stone >= big_number)
        {
            printf("it is becauase of %ld that we are using outliers\n",stone);
            appendl(&next_outliers.l,&next_outliers.n,new_stone);
            append(&nb_next_outliers.l,&nb_next_outliers.n,nb);
            printf("first of the outliers is %ld\n",next_outliers.l[0]);
            print_int_list(nb_next_outliers);
            print_xint_list(next_outliers);
            return;
        }        
        else{
            next_field.l[new_stone] += nb;
            return;
        }
    }
}

void step (int_list field, int_list next_field ,int_list nb_outliers,xint_list outliers,int_list nb_next_outliers,xint_list next_outliers){
    //move the temp to the new
    copy_int_list(field,next_field);
    initialize(next_field);
    //same for the outliers
    free(outliers.l);
    free(nb_outliers.l);

    outliers.n = next_outliers.n;
    outliers.l = malloc(outliers.n * sizeof(long));
    if (outliers.l == NULL) {
        perror("Failed to allocate memory for outliers");
        exit(EXIT_FAILURE);
    }
    memcpy(outliers.l, next_outliers.l, outliers.n * sizeof(long));

    nb_outliers.n = nb_next_outliers.n;
    nb_outliers.l = malloc(nb_outliers.n * sizeof(long));
    if (nb_outliers.l == NULL) {
        perror("Failed to allocate memory for nb_outliers");
        exit(EXIT_FAILURE);
    }
    memcpy(nb_outliers.l, nb_next_outliers.l, nb_outliers.n * sizeof(long));

    free(next_outliers.l);
    free(nb_next_outliers.l);
    next_outliers = (xint_list){0, NULL};
    nb_next_outliers = (int_list){0, NULL};



    for (int i = 0; i < field.n; i++)
    {
        if (field.l[i] != 0)
        {
            next(i,field.l[i],next_field,nb_next_outliers,next_outliers);
        }

    }
    for (int i = 0; i < outliers.n; i++)
    {
        printf("this happende\n");
        next(outliers.l[i],nb_outliers.l[i],next_field,nb_next_outliers,next_outliers);
    }
    return;
}

int_list make_first (char * filename){
    int_list stones = text_to_int_list(filename);
    int* nfieldl = malloc(big_number * sizeof(int));
    int_list nfield = (int_list){big_number,nfieldl};
    initialize(nfield);
    for (int i = 0; i < stones.n; i++)
    {
        nfield.l[stones.l[i]] ++;
    }
    return nfield;
}

int main(){
    char* filename = "test.txt";
    int nb_steps = 5;
    int* fieldl = malloc(big_number * sizeof(int));
    int_list field = (int_list){big_number,fieldl};
    int_list next_field = make_first(filename);
    int_list nb_outliers = (int_list){0,NULL};
    xint_list outliers = (xint_list){0,NULL};
    int_list nb_next_outliers = (int_list){0,NULL};
    xint_list next_outliers = (xint_list){0,NULL};

    for (int i = 0; i < nb_steps; i++)
    {
        print_stones(next_field,next_outliers);
        step (field,next_field ,nb_outliers,outliers,nb_next_outliers,next_outliers);
        printf("this is happening right after that message\n");
        
        printf("-------------------------- end of step %d\n",i+1);
    }
    printf("total nymber of stones is %d\n",sum(next_field));
    free(next_field.l);
    free(field.l);
    return 0;
}