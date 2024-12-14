#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"
#include "utils.h"


int price (char_matrix yard, point * garden, int len){
    int perimeter = 0;
    point cell, neighbour;
    for (int i = 0; i < len; i++)
    {
        perimeter += 4;
        cell = garden[i];
        for (int side = 0; side < NUM_CARDINAL_DIRECTIONS; side++)
        {
            neighbour = add_points(cell, CARDINAL_DIRECTIONS[side]);
            if (in_mat(neighbour,yard) && yard.mat[neighbour.i][neighbour.j] == yard.mat[cell.i][cell.j])
            {
                perimeter --; 
            }
            
        }
        
    }

    return len * perimeter;
    
}

bool in_point (point a, point* group, int len){
    for (int i = 0; i < len; i++)
    {
        if (a.i == group[i].i && a.j == group[i].j)
        {
            return true;
        }
        
    }
    return false;
}


int connex (char_matrix M){
    //number of connex composantes
    int nc = 0, len = 0, size_of_curr;
    char c;
    point next = {0,0}, neighbour, cell;
    point * group = malloc(M.m * M.n * sizeof(point));
    while (len < M.m * M.n)
    {
        cell = next;
        size_of_curr = 1;
        group [len++] = cell;
        c = M.mat[cell.i][cell.j];

    }
    
    
}

point ** connex (char_matrix M){

}