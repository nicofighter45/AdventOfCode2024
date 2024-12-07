#include "../include/common_structures.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/struc_funcs.h"
#include "../include/utils.h"

// List of all unit directions
const point DIRECTIONS[NUM_DIRECTIONS] = {
    { 1,  0},  // Right
    { 0,  1},  // Up
    {-1,  0},  // Left
    { 0, -1},  // Down
    { 1,  1},  // Up-right
    {-1,  1},  // Up-left
    {-1, -1},  // Down-left
    { 1, -1}   // Down-right
};

// List of 4 cardinal directions
const point CARDINAL_DIRECTIONS[NUM_CARDINAL_DIRECTIONS] = {
    { 0,  1},  // Up
    { 1,  0},  // Right
    { 0, -1},  // Down
    {-1,  0},  // Left
};

void print_point(point p){
    printf("point is (%d;%d)\n",p.i,p.j);
    return;
}

void print_mat(char_matrix M){
    if (M.n < 1 || M.m < 1)
    {
        printf("canot print empty matrix of size %dx%d\n",M.n,M.m);
        return;
    }

    for (int i = 0; i < M.n; i++)
    {
        printf("%c",M.mat[i][0]);
        for (int j = 1; j < M.m; j++)
        {
            printf(" %c",M.mat[i][j]);
        }
        printf("\n");
        
    }
    return;
}


void print_int_list(int_list l){
    if (l.n < 1)
    {
        printf("canot print empty list of size %d\n",l.n);
        return;
    }

    for (int i = 0; i < l.n; i++)
    {
        printf("%d ",l.l[i]);        
    }
    printf("\nprinted list is of lenght %d\n",l.n);
    return;
}

void print_int_int_list(int_int_list l){
    for (int i = 0; i < l.n; i++)
    {
        for (int j = 0; j < l.ll[i].n; j++)
        {
            printf("%d ",l.ll[i].l[j]);
        }

        printf("\n");
    }
    
}

void free_mat(char_matrix M){
    for (int i = 0; i < M.n; i++)
    {
        free(M.mat[i]);
    }
    free(M.mat);
}

void free_ii_list(int_int_list iil){
    for (int i = 0; i < iil.n; i++)
    {
        free(iil.ll[i].l);
    }
    free(iil.ll);
}

void free_graph(graph g){
    for (int i = 0; i < g.n; i++)
    {
        free(g.adjacency_matrix[i]);
    }
    free(g.adjacency_matrix);

    free(g.elements);
}

point find_char(char_matrix M, char c){
    for (int i = 0; i < M.n; i++)
    {
        for (int j = 0; j < M.m; j++)
        {
            if (M.mat[i][j] == c)
            {
                return (point){i,j};
            }
            
        }
        
    }
    printf("could not find %c in matrix M : \n",c);
    print_mat (M);
    return (point){-1,-1};
}

graph copy_graph(graph g){
    int* new_el = malloc(g.n * sizeof(int));
    int ** new_adj_mat = malloc(g.n * sizeof(int*));
    for (int i = 0; i < g.n; i++)
    {
        new_el[i] = g.elements[i];
        new_adj_mat[i] = malloc(g.n * sizeof(int));
        for (int j = 0; j < g.n; j++)
        {
            new_adj_mat[i][j] = g.adjacency_matrix[i][j];
        }
        
    }
    return (graph){g.n,new_el,new_adj_mat};
}

graph sub_graph(graph g,int_list l){
    int* new_el = malloc(l.n * sizeof(int));
    int ** new_adj_mat = malloc(l.n * sizeof(int*));
    int ni = 0,nj = 0;
    for (int i = 0; i < g.n; i++)
    {   
        if (in(l,g.elements[i]))
        {
            new_el[ni] = g.elements[i];
            new_adj_mat[ni] = malloc(l.n * sizeof(int));
            for (int j = 0; j < g.n; j++)
            {   
                if (in(l,g.elements[j]))
                {
                    new_adj_mat[ni][nj++] = g.adjacency_matrix[i][j];
                }
                
            }
            nj = 0;
            ni ++;
        }
        
        
    }
    return (graph){l.n,new_el,new_adj_mat};
}

void rotate_vector_r(point *vector){
    int temp = vector->i;
    vector->i = vector->j;
    vector->j = -temp;
}

char_matrix empty_mat(int n,int m){
    char ** mat = malloc(n * sizeof(char*));
    char_matrix M = (char_matrix){n,m,mat};
    for (int i = 0; i < n; i++)
    {
        M.mat[i] = malloc(m * sizeof(char));
        for (int j = 0; j < m; j++)
        {
            M.mat[i][j] = '.';
        }
        
    }
    
    return M;
}

bool is_root(graph g, int e){

    if (!in((int_list){g.n,g.elements},e))
    {
        printf("tried to see if %d was root in graph, yet is not an element\n",e);
        return false;
    }
    
    int ie = index((int_list){g.n,g.elements},e);

    for (int i = 0; i < g.n; i++)
    {
        if (g.adjacency_matrix[i][ie])
        {
            return false;
        }
           
    }
    
    return true;
    
}

graph rm_elt(graph g, int e){
    if (!in((int_list){g.n,g.elements},e) || g.n == 0)
    {
        printf("tried to remove %d, yet is not an element of graph\n",e);
        return g;
    }
    int* new_elements = malloc((g.n -1)* sizeof(int));
    
    int ni = 0;
    for (int i = 0; i < g.n; i++)
    {
        if (g.elements[i] != e)
        {
            new_elements[ni++] = g.elements[i];
        }
    }
    //print_int_list((int_list){g.n - 1,new_elements});
    return sub_graph(g,(int_list){g.n - 1,new_elements});
}

point add_points(point a, point b){
    point res;
    res.i = a.i + b.i;
    res.j = a.j + b.j;
    return res;
}

point scale(int h,point p){
    point res;
    res.i = h * p.i;
    res.j = h * p.j;
    return res;

}

bool in_mat(point p, char_matrix M){
    return (p.i >= 0 && p.i < M.n && p.j >= 0 && p.j < M.m);
    }


void print_graph(graph G){
        if (G.n < 1)
    {
        printf("canot print empty graph of size %dx%d\n",G.n,G.n);
        return;
    }


    printf("--------------------------\n");
    printf("graph has elements : \n");



    for (int i = 0; i < G.n; i++)
    {
        printf ("%d:%d ",i,G.elements[i]);
    }
    
    printf("\n\nAnd adjacency matrix:\n");

    for (int i = 0; i < G.n; i++)
    {
        printf("%d",G.adjacency_matrix[i][0]);
        for (int j = 1; j < G.n; j++)
        {
            printf(" %d",G.adjacency_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n--------------------------\n");
    return;
}

void add_arc(graph g, int i, int j){
    if (i < 0 || i >= g.n || j < 0 || j >= g.n ){
        printf("trying to add arc to elements that do not fit: there are %d elements in the graph, yet i = %d and j = %d\n",g.n,i,j);
        return;
    }
    g.adjacency_matrix[i][j] = 1;
    return;
}


void rm_arc(graph g, int i, int j){
    if (i < 0 || i >= g.n || j < 0 || j >= g.n ){
        printf("trying to remove arc to elements that do not fit: there are %d elements in the graph, yet i = %d and j = %d\n",g.n,i,j);
        return;
    }
    if (g.adjacency_matrix[i][j] == 0){
        printf("there was no arc to be removed between %d and %d",i,j);
    }
    g.adjacency_matrix[i][j] = 0;
    return;
}


bool is_arc(graph g, int i, int j){
    if (i < 0 || i >= g.n || j < 0 || j >= g.n ){
        printf("trying to check if %d->%d is an arc yet there are only %d elements in the graph\n",i,j,g.n);
        return false;
    }
    return (g.adjacency_matrix[i][j] == 1);
}