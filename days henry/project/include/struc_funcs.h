#ifndef STRUC_FUNCS_H
#define STRUC_FUNCS_H

# include <stdbool.h>

#include"common_structures.h"

// function declarations

/*
@brief prints a readable point in the standard output
@param p is the point we are printing
@return nothing, simply prints.
*/
void print_point(point p);

/*
@brief prints a readable matrix in the standard output
@param M is the char_matrix we are printing 
@return nothing, simply prints.
*/
void print_mat(char_matrix M);

/*
@brief prints a readable version of the adjacency matrix of the graph
@param G is the graph we are printing
@return nothing, simply prints G.
*/
void print_graph(graph G);

/*
@brief prints a readable version of the int_int_list
@param l is the list we are printing
@return nothing, simply prints l.
*/
void print_int_list(int_list l);

/*
@brief rotates a vector 90 degrees to the right. 
@param vector is the vector we are rotating
@return nothing, modification is in place.
*/
void rotate_vector_r(point *vector);

/*
@brief prints a readable version of the int_list
@param l is the list we are printing
@return nothing, simply prints l.
*/
void print_int_int_list(int_int_list l);

/*
@brief finds elemetnc c in char_matrix M
@param M is the matrix we are looking inside of
@param c is the char we are looking for
@return the location of c in M, -1,-1 if it did not find it.
*/
point find_char(char_matrix M, char c);

/*
@brief finds all symbols of M
@param M is the matrix we are looking inside of
@return the list of all symbols in a matrix
*/
char* all_symbols(char_matrix M);

/*
@brief finds all occurences of c in M
@param M is the matrix we are looking inside of
@param c is the character we are looking for
@return point* of all occurences of c in M
*/
point * find (char_matrix M, char c);

/*
@brief finds all occurences of c in M
@param M is the matrix we are looking inside of
@param c is the character we are looking for
@return point* of all occurences of c in M
*/
int count (char_matrix M, char c);

/*
@brief adds an arc to the graph from point i to point j
@param g is the graph we are adding an arc to 
@return nothing, simply adds the arc
*/
void add_arc(graph g, int i, int j);

/*
@brief removes an arc to the graph from point i to point j
@param g is the graph we are removeing the arc from 
@return nothing, simply removes the arc
*/
void rm_arc(graph g, int i, int j);

/*
@brief removes element i from int list l
@param l is the initial int_list
@param i is the index of the nujmber we want to remove
@return a new int_list (do not forget to free it !!)
*/
int_list rm_elt_l(int_list l, int i);

/*
@brief says if there is an arc in the graph from point i to point j
@param g is the graph we are checking
@param i is the start of the arc
@param j is the end of the arc
@return boolean, if there is an arc between i and j
*/
bool is_arc(graph g, int i, int j);

/*
@brief tells us if i is a root of g (no incoming arrows)
@param g is the graph we are checking
@param e is the element we are checking for
@return boolean, if i is a root of g
*/
bool is_root(graph g, int e);

/*
@brief makes subgraph of all elements other than e
@param g is the graph we are removing e from
@param e is the element we are removing
@return new graph without e in it
*/
graph rm_elt(graph g, int e);

/*
@brief frees the allocated space for the matrix
@param M is the char_matrix we are freeing
@return nothing, simply frees
*/
void free_mat(char_matrix M);

/*
@brief gives a matrix of . of shape n,m
@return a char_matrix
*/
char_matrix empty_mat(int n,int m);

/*
@brief frees the allocated space for the int_int_list
@param l is the list of lists we are freeing
@return nothing, simply frees
*/
void free_ii_list(int_int_list l);

/*
@brief frees the allocated space for the adjacency matrix
as well as the elements
@param g is the graph we are freeing
@return nothing, simply frees
*/
void free_graph(graph g);

/*
@brief deeply copies everything in a graph
@param g is the graph we are copying
@return a new graph, completely new
*/
graph copy_graph(graph g);

/*
@brief creates the subgraph of g taking only elements of l
@param g is the graph we are taking from
@param l is the elements we are keeping
@return the subgraph we are looking for
*/
graph sub_graph(graph g,int_list l);


/*
@brief adds the coordinates of both points
@param a is the first point 
@param b is the second point 
@return a point of coordinates which are the sum of point a's and point b's
*/
point add_points(point a,point b);

/*
@brief scales up a point by a factor of h
@param h is the scaling factor
@param p is the point we are scaling
@return a point of coordinates h*p.i,h*p.j
*/
point scale (int h,point p);

/*
@brief tells whether a coordinate is in a matrix
@param p is the coordinate we are checking for 
@param M is the matrix we are checking
@return a boolean, p.i >= 0 && p.i < M.n && p.j >= 0 && p.j < M.m
*/
bool in_mat(point p, char_matrix M);

/*
@brief gives the top value of a cpile and removes it
@param p is the pile we are depiling
@return an int, the top element of the pile
*/
char cdepile(cpile cp);

/*
@brief initializes a pile with one element
@param a is the point we are starting the pile with
@param max_height is the maximum height the pile will be able to hold
@reaturn ppile according to specifications
*/
ppile initialize_ppile (point a, int max_height);

/*
@brief tells me whether a pile is empty
@param p is the pile we are checking for
@return a boolean
*/
bool is_empty_ppile (ppile p);

/*
@brief prints a human_readable format of a ppile
@param p is the ppile we are printing
@return nothing, simply prints
*/
void print_ppile (ppile p);

/*
@brief aknowledging that this goes against the philosophy of piles, and not caring:
@param p is the pile we are looking in
@param a is the point we aare looking fojr in ppile p
@return boolean waheather a is in p or not
*/
bool is_in_ppile (ppile p, point a);

/*
@brief transforms a ppile to a point list of appropriate height
@param p is the ppile we are transforing
@return a point_list of the elements of p;
*/
point_list ppile_to_point_list (ppile p);

/*
@brief piles up the yet unseen neighbours of a connex part of the matrix
@param M char_matrix is the matrix wse are looking through
@param a point is the connex part we are going to explore
@param seen is an unsigned char ** bitmap of M
@param neighbours is the ppile we are going to add to of the neighbours 
@return point_list of a's connex part
*/
point_list niehgbours_of_connex  (char_matrix M, point a, unsigned char ** seen, ppile neighbours);

/*
@brief gives the connexc parts of a char_matrix
@param M is the matrix we are looking at
@return a point_point_list p, where p.n is tshe number of connex parts, p.pl[i] is a representative, and p.l[i] is the nubmer of elts in that connex part. 
*/
point_set connex_parts (char_matrix M);



#endif // STRUC_FUNCS_H