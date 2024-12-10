#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"
#include "utils.h"

struct point_list
{
    int n;
    point* l;
};
typedef struct point_list point_list;

void print_point_list (point_list a){
    for (int i = 0; i < a.n; i++)
    {
        printf("%d:(%d,%d)_",i,a.l[i].i,a.l[i].j);
    }
    printf("\n");
    return ;
}


point_list copy_first (point* a, int len){
    point* b = malloc(len* sizeof(point));
    for (int i = 0; i < len; i++)
    {
        b[i] = a[i];
    }
    return (point_list){len,b};
}

bool in_first (point p, point* a, int len){
    for (int i = 0; i < len; i++)
    {
        if (a[i].i == p.i && a[i].j == p.j)
        {
            return true;
        }
        
    }
    return false;
}

point_list unique_points(point_list a){
    point up[a.n];
    int nb_unique = 0;
    for (int i = 0; i < a.n; i++)
    {   
        if (!in_first (a.l[i],up,nb_unique))
        {
            up[nb_unique ++] = a.l[i];
        }
    }
    free(a.l);
    return copy_first(up,nb_unique);
    
}

point_list step (char_matrix map, point_list starts){
    point next[4 * starts.n];
    int nb_next = 0;
    point step;
    for (int i = 0; i < starts.n; i++)
    {
        for (int d = 0; d < NUM_CARDINAL_DIRECTIONS; d++)
        {
            step = add_points(starts.l[i],CARDINAL_DIRECTIONS[d]);
            // following expression makes sure the step size is 1;
            if (in_mat(step,map) && map.mat[step.i][step.j] - map.mat[starts.l[i].i][starts.l[i].j] == 1)
            {
                next[nb_next ++] = step;
            }   
        }
        
    }
    point_list u = unique_points(copy_first(next,nb_next));
    return u;
}


int score_th(char_matrix map,point trailhead){
    // there are 9 steps to be taken to go from a a trailhead to a trailend
    //printf("treating trailhead (%d,%d):\n",trailhead.i,trailhead.j); ---- un - comment for clarity
    point_list positions = {1,&trailhead};
    //print_point_list(positions); ---------------------------------------- un - comment for clarity
    for (int st = 0; st < 9; st++)
    {
        positions = step(map,positions);
        //print_point_list(positions); ------------------------------------ un - comment for clarity
    }
    point_list u = unique_points(positions);
    int score = u.n;
    free (u.l);
    return score;
}

int add_all_trailheads(char_matrix map){
    point* trailheads = find(map,'0');
    int nb_trailheads = count(map,'0');
    printf("%d trailheads were found\n",nb_trailheads);
    int total = 0;

    for (int i = 0; i < nb_trailheads; i++)
    {
        total += score_th(map,trailheads[i]);
    }
    return total;
}

int main(){
    char * filename = "input.txt";
    char_matrix map = text_to_matrix(filename);

    print_mat(map);

    printf("the score is %d\n",add_all_trailheads(map));

    return 0;
}