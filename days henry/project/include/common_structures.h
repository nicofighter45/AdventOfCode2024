#ifndef COMMON_STRUCTURES_H
#define COMMON_STRUCTURES_H

# include <stdbool.h>

//struct declarations

struct point
{
    int i;
    int j;
};


/**
 * @brief this is your basic int * int tuple often representing a point
 * @param i is the first coordinate of the point
 * @param j is the second coordiante
 */
typedef struct point point;



struct char_matrix
{
    int n;
    int m;
    char ** mat;
};


/**
 * @brief this lets me hold an char matrix of shape nxm
 * @param n is the height of the matrix
 * @param m is the width of the matrix
 * @param mat is the actual char ** holding the info
 */
typedef struct char_matrix char_matrix;

struct int_matrix
{
    int n,m;
    int ** mat;
};


/**
 * @brief this lets me hold an int matrix of shape nxm
 * @param n is the height of the matrix
 * @param m is the width of the matrix
 * @param mat is the actual int ** holding the info
 */
typedef struct int_matrix int_matrix;

struct sterr
{   
    char* s;
    int b;
};


/**
 * @brief this lets me hold a string and a potential error code (that explains st_err)
 * @param s is the char*
 * @param b is the error code (usually 0 or 1 so boolean)
 */
typedef struct sterr sterr;

/*a sterr lets a function output a string, while also having an output code, for a potential error, or added info*/

struct graph{
    int n;
    int * elements;
    int ** adjacency_matrix;
};


/**
 * @brief this is a representation of a graph through adjacency matrix
 * @param n integer is the number of elements, so also the shape of the matrix (nxn)
 * @param elements is an int* and gives the tags of the elements
 * @param adjacency_matrix is an int **, of shape nxn where adj_mat[i][j] <=> elements[i]-->elemtsns[j]
 */
typedef struct graph graph;

struct int_list{
    int n;
    int* l;
};


/**
 * @brief this lets me hold a list of integers
 * @param n integer is the number of elements in the list
 * @param l is the actual int list
 */
typedef struct int_list int_list;

struct int_int_list{
    int n;
    int_list* ll;
};


/**
 * @brief this lets me hold a list of variable sized int lists
 * @param n integer is the number of int_lists i am holding
 * @param ll is the list of int_lists
 */
typedef struct int_int_list int_int_list;

struct point_list{
    int n;
    point* l;
};


/**
 * @brief this lets me hold a point lists
 * @param n integer is the lenght of said point list
 * @param l is a point *, the point list 
 */
typedef struct point_list point_list;

struct point_point_list{
    int n;
    point_list* pl;
};


/**
 * @brief this lets me hold a list of point lists
 * @param n integer is the number point_lists there are
 * @param pl is a point_list* pointing to the point list 
 */
typedef struct point_point_list point_point_list;



struct point_set{
    int n; /**< the number of points in the set */
    int_list nb_elts;
    point_list representatives;
};

/**
 * @brief this lets me hold a set of points, to act as a helper for keeping connex parts
 * @param n is the number of representaives
 * @param nb_elts is an int list, where for representative I, there are nb_elts[i] elements in the set
 * @param representatives a point_list gives me a representative for connex part i 
 */
typedef struct point_set point_set;

struct cpile{
    char * pile;
    int height, max_height;
};

/**
 * @brief this lets me hold a pile of chars
 * @param pile is the  actual list of chars
 * @param height tells me the current height of the pile
 * @warning this height starts at 0 does not mean that the pile is empty (its not coded well (¬_¬))
 * @param max_height is the total hiehgt allocated to the pile, to not surpass
 */
typedef struct cpile cpile;

struct ppile{
    point * pile;
    int height, max_height;
};


/**
 * @brief this lets me hold a pile of points
 * @param pile is the  actual list of points
 * @param height tells me the current height of the pile
 * @warning this height starts at 0 does not mean that the pile is empty (its not coded well (¬_¬))
 * @param max_height is the total hiehgt allocated to the pile, to not surpass
 */
typedef struct ppile ppile;


// Array of all unit directions

#define NUM_DIRECTIONS 8
extern const point DIRECTIONS[NUM_DIRECTIONS];

#define NUM_CARDINAL_DIRECTIONS 4
extern const point CARDINAL_DIRECTIONS[NUM_CARDINAL_DIRECTIONS];

#endif // COMMON_STRUCTURES_H