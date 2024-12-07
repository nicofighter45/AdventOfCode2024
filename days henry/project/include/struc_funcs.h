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
@brief prints a readable version of the int_list
@param l is the list we are printing
@return nothing, simply prints l.
*/
void print_int_int_list(int_int_list l);

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

#endif // STRUC_FUNCS_H