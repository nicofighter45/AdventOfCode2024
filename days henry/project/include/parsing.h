#ifndef PARSING_H
#define PARSING_H

#include "common_structures.h"
#include "struc_funcs.h"

//function declarations


/*
@brief gives the word read when starting at i,j in a matrix of shape n,m.
@param M is a char_matrix, see common_structures.h
@param expected_len is the length of the string we are searching for, if that is possible
@param deb is the starting point
@param dir is a vector pointing in the direction of travel
@return a sterr with the characters and output code 0 if it failed, otherwise, output is 1
*/
sterr make_str_in_mat(char_matrix M, int expected_len,point deb,point dir);

/*
@brief gives the sub char_matrix of top left corner i,j in a matrix of shape n,m.
@param M is a char_matrix, see common_structures.h
@param shape is the size of the submatrix we want (i lines and j columns)
@param deb is the starting point
@return the desired sub_matrix.
*/
char_matrix make_submat_in_mat(char_matrix M, point shape,point deb);

/*
@brief applies f to every subword of M of length expected_len, and adds up the total
@param M is a char_matrix, see common_structures.h
@param expected_len is the length of the string we are searching for, if that is possible
@param f is the function we are mapping to the entire matrix
@return the summ of all outputs of f
*/
int map_subwords(char_matrix M, int expected_len,int (*f)(char*));

/*
@brief applies f to every submatrix of M of given shape, and adds up the total
@param M is a char_matrix, see common_structures.h
@param shape is the shape of the submatrices we are mapping for
@param f is the function we are mapping to the entire matrix
@return the summ of all outputs of f
*/
int map_submatrices(char_matrix M, point shape,int (*f)(char_matrix));

/*
@brief applies f to every element of l.l
@param l is the list we are mappint
@param f is the function we are mapping to the entire list
@return nothing, modifications are in place
*/
void map_int_list(int_list l,int (*f)(int));

/*
@brief specificlly for day5 of the advent of code
@param filename is the name of the file we are parsing through
@return int, read the name of the function
*/
int number_of_lines_with_commas(char * filename);

/*
@brief specificlly for day5 of the advent of code
finds the length of lists formated as i,j,k....z\n in f
@param filename is the name of the file we are parsing through
@return int_list containing the lenght of reports. 
*/
int_list length_of_reports(char * filename);

/*
@brief specificlly for day5 of the advent of code
gives a list of list of reports  i,j,k....z\n in f
@param filename is the name of the file we are parsing through
@return int_list containing the lenght of reports. 
*/
int_int_list fill_reports(char * filename);

#endif // PARSING_H