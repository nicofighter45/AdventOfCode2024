#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"
#include "utils.h"

struct xpoint
{
    long i,j;
};
typedef struct xpoint xpoint;

struct xint_list{
    int n;
    long* l;
};
typedef struct xint_list xint_list;

xint_list int_to_xint_list (int_list l){
    long * xl = malloc(l.n * sizeof(long));
    for (int i = 0; i < l.n; i++)
    {
        xl[i] = l.l[i];
    }
    free(l.l);
    return (xint_list){l.n,xl};
}


int digits_in(long a){
    int i = 0;
    while (a > 0)
    {
        a = a/10;
        i++;
    }
    
    return i;
    
}


xpoint split (long stone){
    int d = digits_in(stone);
    if (d % 2 != 0)
    {
        printf("tried spliting a stone of odd digit lenghts\n");
    }
    int p = power(10,(d/2));
    long stone_l = stone / p;
    long stone_r = stone - stone_l * p;

    return (xpoint){stone_l,stone_r};
}


int next (long stone, int step){
    // we stop after 75 steps
    if (step == 40)
    {
        return 1;
    }
    // if stone has a 0 inscribed on it, it turns to a 1
    else if (stone == 0)
    {
        return next(1,(step + 1));
    }
    // if stone has even numaber of digits, it gets split
    else if (digits_in(stone) % 2 == 0)
    {
        return next(split(stone).i, (step + 1)) + next(split(stone).j, (step + 1));
    }
    // otherwise, it gets multiplied by 2k24
    else
    {
        return next(2024 * stone,(step + 1));
    }
}


int main(){
    char* filename = "input.txt";
    int_list shor_stones = text_to_int_list(filename);
    xint_list l_stones = int_to_xint_list(shor_stones);
    int total = 0;
    for (int i = 0; i < l_stones.n; i++)
    {
        total += next(l_stones.l[i],0);
        printf("finished stone %d of %d\n",i,l_stones.n);
    }
    printf("total namber of stones is : %d\n",total);
    free(l_stones.l);
    return 0;
}