#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/common_structures.h"
#include "../include/struc_funcs.h"
#include "../include/files_utils.h"
#include "../include/parsing.h"

int is_XMAS (char*s){
    return (strcmp("XMAS",s) == 0);
}

bool is_MAS (char*s){
    return (strcmp("MAS",s) == 0 || strcmp("SAM",s) == 0 );
}

int is_X_MAS (char_matrix m){
    bool b = false;
    if (m.m == 3 && m.n == 3)
    {
    point dup = {-1,1};
    point ddown = {1,1};

    sterr su = make_str_in_mat(m,3,(point){0,0},ddown);
    sterr sd = make_str_in_mat(m,3,(point){2,0},dup);

    if (su.b == 0 || sd.b == 0)
    {
        printf("did not manage to make string from matrix of len 3\n");
    }
    b =is_MAS(su.s) && is_MAS(sd.s);
    }
    
    return b;

}


int main (){
    int len_XMAS = 4;
    char_matrix M = text_to_matrix("input.txt");
    printf("the word XMAS comes up %d times\n",map_subwords(M,len_XMAS,is_XMAS));
    printf("the X-MAS pattern comes up %d times\n",map_submatrices(M,(point){3,3},is_X_MAS));
    free_mat(M);
    return 0;
}

/*
the word XMAS comes up 2514 times
the X-MAS pattern comes up 1888 times
*/