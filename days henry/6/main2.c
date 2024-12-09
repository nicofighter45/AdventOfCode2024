#include <stdlib.h>
#include <stdio.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"


point next_step(char_matrix map, point man, point *direction,int *dir){
    if (!in_mat(man,map))
    {
        printf("the man is not in the map\n");
        return (point){-1,-1};
        
    }
    else if (!in_mat(add_points(man,*direction),map))
    {
        //printf("the man has left the map\n");
        return (point){-1,-1};
    }
    else
    {
        if ((map.mat[add_points(man,*direction).i][add_points(man,*direction).j] == '#'))
        {
            rotate_vector_r(direction);
            *dir = (*dir +1) % NUM_CARDINAL_DIRECTIONS;
            return man;
        }
        
        else{
            return add_points(man,*direction);
        }

    }
    
    
}

void initialise_refs(char_matrix * refs){
    for (int i = 0; i < refs[0].n; i++)
    {
        for (int j = 0; j < refs[0].m; j++)
        {
            for (int k = 0; k < NUM_CARDINAL_DIRECTIONS; k++)
            {
                refs[k].mat[i][j] = '.';
            }
            
        }
        
    }
    return;

}

bool is_looped (char_matrix map,char_matrix * refs){
    point direction = {-1,0}; // up in regards with matrices
    point man = find_char(map,'^');
    initialise_refs(refs);

    int dir = 0;
    do
    {
        if (refs[dir].mat[man.i][man.j] == '.')
        {
            refs[dir].mat[man.i][man.j] = 'x';
        }
        else
        {
            return true;
        }
        man = next_step(map,man,&direction,&dir);
    } while (man.i>=0);

    //printf("there was no loop\n");

    return false;
}

int main(){
    char *filename = "input.txt";
    char_matrix map = text_to_matrix(filename);
    int count = 0;
    //print_mat(map);
    //printf("\n");

    char_matrix reference_up = empty_mat(map.n,map.m);
    char_matrix reference_right = empty_mat(map.n,map.m);
    char_matrix reference_down = empty_mat(map.n,map.m);
    char_matrix reference_left = empty_mat(map.n,map.m);
    char_matrix refs[NUM_CARDINAL_DIRECTIONS] = {
        reference_up,
        reference_right,
        reference_down,
        reference_left};

    for (int i = 0; i < map.n; i++)
    {
        for (int j = 0; j < map.m; j++)
        {
            if (map.mat[i][j] != '#' && map.mat[i][j] != '^')
            {
                map.mat[i][j] = '#';
                //print_mat(map);
                if (is_looped(map,refs))
                {
                    count++;
                }
                map.mat[i][j] = '.';
            }
            
        }
        
    }
    
    printf("there are %d loops\n",count);
    free_mat(map);
    return 0;
}


// 1663 loops, took 6 seconds to find;