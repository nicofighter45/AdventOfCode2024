#include <stdlib.h>
#include <stdio.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"

point next_step(char_matrix map, point man, point *direction){
    if (!in_mat(man,map))
    {
        printf("the man is not in the map\n");
        return (point){-1,-1};
        
    }
    else if (!in_mat(add_points(man,*direction),map))
    {
        printf("the man has left the map\n");
        return (point){-1,-1};
    }
    else
    {
        if ((map.mat[add_points(man,*direction).i][add_points(man,*direction).j] == '#'))
        {
            rotate_vector_r(direction);
            return man;
        }
        
        else{
            return add_points(man,*direction);
        }

    }
    
    
}

int main(){
    char *filename = "input.txt";
    char_matrix map = text_to_matrix(filename);
    point man = find_char(map,'^');
    point direction = {-1,0}; // up in regards with matrices
    char_matrix reference = empty_mat(map.n,map.m);
    int count = 0;

    do
    {
        if (reference.mat[man.i][man.j] == '.')
        {
            count += 1;
            reference.mat[man.i][man.j] = 'x';
            //print_mat(reference);
        }
        man = next_step(map,man,&direction);
    } while (man.i>=0);
    printf("the man went to %d different square\n",count);
    free_mat(reference);
    free_mat(map);
    return 0;
}