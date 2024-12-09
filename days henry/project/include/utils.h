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

#endif //UTILS_H
