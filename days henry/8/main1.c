#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"
#include "utils.h"

char_matrix make_ref(char_matrix M){
    char **ref = malloc(M.n * sizeof(char*));
    for (int i = 0; i < M.n; i++)
    {
        ref[i] = malloc (M.m * sizeof(char));
        for (int j = 0; j < M.m; j++)
        {
            ref[i][j] = '.';
        }
        
    }
    return (char_matrix){M.n,M.m,ref};
}

// the following code added all points that respect the distance rule, not only the ones on the line
/*
int add_antinodes (char_matrix reference, point a, point b){
    int added = 0, dist_a, dist_b;
    point curr;
    bool must_add;
    for (int i = 0; i < reference.n; i++)
    {
        curr.i  = i;
        for (int j = 0; j < reference.m; j++)
        {   
            curr.j = j;
            must_add = true;
            must_add  = must_add && reference.mat[i][j] != '#';
            // we use the sqaure of the norm to stay within int land
            dist_a = norm_sq(vect(a,curr));
            dist_b = norm_sq(vect(b,curr));
            must_add = must_add && (dist_a == 2*dist_b || dist_b == 2*dist_a); 
            if (must_add)
            {
                added ++;
                printf("%d,%d has an antinode from points (%d,%d) and (%d,%d)\n",i,j,a.i,a.j,b.i,b.j);
                reference.mat[i][j] = '#';
            }
            
        }
        
    }

    return added;
    
}
*/

int add_antinode (char_matrix reference, point a, point b){
    point v = vect(a,b);

    //first antinode position would be behind a:
    point a_node_a = add_points(a,scale(-1,v));
    if (in_mat(a_node_a,reference))
    {
        if (reference.mat[a_node_a.i][a_node_a.j] != '#')
        {
            reference.mat[a_node_a.i][a_node_a.j] = '#';
            return 1;
        }
        
    }
    return 0;
}


int main(){
    char * filename = "input.txt";
    char_matrix M = text_to_matrix(filename);
    char * symbs = rm_occ('.',all_symbols(M));
    int nb_symbs = strlen(symbs);

    printf("there are %d symbols on the map : %s \n",nb_symbs,symbs);

    // we make a shadow of the first matrix to find the antinodes
    char_matrix ref = make_ref(M);

    point* all_occurences;
    point* couples;
    int nb_occ, nb_couples,marginal_add;
    char c;
    int total = 0;
    for (int i = 0; i < nb_symbs; i++)
    {
        c = symbs[i];
        marginal_add = 0;
        printf("adding antinodes for symbol %c\n",c);
        // which there are n(n-1)/ 2 of 
        nb_occ = count(M,c);
        couples = all_couples(nb_occ);
        nb_couples = nb_occ * (nb_occ - 1) / 2;
        all_occurences = find(M,c);

        for (int j = 0; j < nb_couples; j++)
        {   
            marginal_add += add_antinode(ref,all_occurences[couples[j].i],all_occurences[couples[j].j]);
            marginal_add += add_antinode(ref,all_occurences[couples[j].j],all_occurences[couples[j].i]);
        }
        total += marginal_add;
        printf("just added %d antinodes for %c : \n",marginal_add,c);
        
    }
    
    printf("there are a total of %d antinodes on the map\n",total);

    //time to free all athe used pointers.
    free_mat(ref);
    free_mat(M);
    free(all_occurences);
    free(couples);

    return 0;
}

/*answer is 367*/