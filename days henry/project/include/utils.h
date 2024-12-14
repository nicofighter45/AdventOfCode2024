#ifndef UTILS_H 
#define UTILS_H

#include <stdbool.h>

#include "common_structures.h"

/*
@brief tells me if e is in l
@param l is an int_lsit
@param e is the element we are looking for in l
@return a boolean : whether e is in l or not
*/
bool in (int_list l, int e);

/*
@brief tells me if e is in l
@param l is the int list
@return a list of all unique items of 
*/
int_list unique (int_list l);

/*
@brief gives me the index of i in l, -1 if i not in l
@param l is the int list
@param e is the int whose index we are looking for
@return index of i in l, -1 if i not in l
*/
int index (int_list l, int e);

/*
@brief tells me if c is in s
@param c is the char we are looking for in s
@param s is the string we are looking for c in 
@param len_s is the lenght of s , you can use strlen from string.h if you do not know
@return a boolean wheter c is in s or not
*/
bool char_in_str (char c,char* s,int len_s);

/*
@brief gives me tahe coordinates of vector a->b
@param a is the first point
@param ab os the second point 
@return a point(vector) of a->b
*/
point vect (point a, point b);

/*
@brief gives me all the combinations of 2 ints < n
@param n is the read this ^
@return a point list of these couples. 
*/
point *all_couples (int n);

/*
@brief gives the square of the norm of a vector
@param v is the vector
@return the square of teh norm of the cector
*/
int norm_sq (point v);

/*
@brief removes all occurences of a char in a char*
@param c is the char we are removing from s
@param s is the str we are removing c from
@return a new string, void of c, (!! s has been freed)
*/
char * rm_occ (char c,char* s);

/*
@brief gives the sum of all numbers in a list
@param l is the list we are summing elts from
@return the sum of the elts of l.
*/
int sum (int_list l);

/*
@brief gives the number of digits of an int
@param a is the number we are looking at
@return the number of digits of an int
*/
int nb_digits(int a);

/*
@brief gives me a ** b
@param a is the base
@param b is the exponenet
@return a ^ b;
*/
int power(int a,int b);

#endif //UTILS_H
