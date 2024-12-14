#ifndef FILES_UTILS_H
#define FILES_UTILS_H

#include "common_structures.h"
#include "struc_funcs.h"

//function declarations

/*
@brief Read the number of lines in a file
@param filename is the name of the file
@return number of lines in file
*/
int number_of_lines(char*filename);

/*
@brief gives the lenght of the longest line in file
@param filename is the name of the file
@return number of characters in the longest line
*/
int max_len_lines(char*filename);

/*
@brief reads a file and transforms it into a matrix
where m[i][j] is the jth character on the ith line
@param filename is the name of the file
@return a char_matrix
*/
char_matrix text_to_matrix(char*filename);

/*
@brief reads a file and transforms it into a graph
specifically looking for i|j patterns interpreted as i->j in the graph
@param filename is the name of the file
@return graph with number of elements, elements, and adjacency matrix
*/
graph text_to_graph(char* filename);

/*
@brief reads a file and transforms it into an int_int_ilst of the numbers
@param filename is the name of the file
@return an int-int list of the numbers in the file
*/
int_int_list text_to_int_int_list(char* filename);

/*
@brief reads a file and transforms it into an int_ilst of the numbers
@param filename is the name of the file
@return an int list of the numbers in the file
*/
int_list text_to_int_list(char* filename);

/*
@brief reads a file and gives the number of numbers on every line
@param filename is the name of the file
@return an int_list with the number of numbers on every line
*/
int_list nb_num_on_lines(char* filename);

/*
@brief reads a file and finds every occuring number in it
@param filename is the name of the file
@return a pointer to allocated memory space to every number in the text
*/
int_list all_num_in_text(char* filename);

/*
@brief reads a file and gives how many characters are in it
@param filename is the name of the file
@return the number of characters in a text
*/
int nb_char (char* filename);

#endif // FILES_UTILS_H