#ifndef COMMON_STRUCTURES_H
#define COMMON_STRUCTURES_H

# include <stdbool.h>

//struct declarations

struct point
{
    int i;
    int j;
};

typedef struct point point;



struct char_matrix
{
    int n;
    int m;
    char ** mat;
};

typedef struct char_matrix char_matrix;

struct sterr
{   
    char* s;
    int b;
};

typedef struct sterr sterr;

/*a sterr lets a function output a string, while also having an output code, for a potential error, or added info*/

struct graph{
    int n;
    int * elements;
    int ** adjacency_matrix;
};

typedef struct graph graph;

struct int_list{
    int n;
    int* l;
};

typedef struct int_list int_list;

struct int_int_list{
    int n;
    int_list* ll;
};

typedef struct int_int_list int_int_list;


// Array of all unit directions

#define NUM_DIRECTIONS 8
extern const point DIRECTIONS[NUM_DIRECTIONS];

#define NUM_CARDINAL_DIRECTIONS 4
extern const point CARDINAL_DIRECTIONS[NUM_CARDINAL_DIRECTIONS];

#endif // COMMON_STRUCTURES_H