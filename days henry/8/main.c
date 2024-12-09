#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"
#include "utils.h"

/**
 * to do :
 * all symbols in char_matrix-------------------------------------------------OK
 * point * count (char martrix, char c) gives me the positions of all  -------OK
 * 
 * point vect (point a, point b)----------------------------------------------OK
 * point * all_couples(int n);------------------------------------------------OK
 * 
 * in main : make reference---------------------------------------------------OK
 * int add_antinodes (char_matrix reference, point a, point b)----------------OK
 * gives the amount of added antinodes to a reference for an antenna couple.--OK 
 * 
 */

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

int add_antinode (char_matrix reference, point a, point b){
    point v = vect(a,b);
    int added_antinodes = 0;
    //first antinode is on a;
    point a_node_a = a;

    do
    {
        
        if (reference.mat[a_node_a.i][a_node_a.j] != '#')
        {
            reference.mat[a_node_a.i][a_node_a.j] = '#';
            added_antinodes ++;
        }
        a_node_a = add_points(a_node_a,v);
    } while (in_mat(a_node_a,reference));
    return added_antinodes;
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

/*answer is 1285*/