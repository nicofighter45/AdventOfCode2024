#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "common_structures.h"



bool in (int_list l, int e){
    for (int i = 0; i < l.n; i++)
    {
        if (l.l[i] == e)
        {
            return true;
            }
    }
    return false;
}

int_list unique (int_list l){

    if (l.n < 1)
    {   
        printf("there are no unique elements in list l of lenght %d\n",l.n);
        return l;
    }

    
    int_list u = {l.n,malloc(l.n*sizeof(int))};

    for (int i = 0; i < l.n; i++)
    {
        u.l[i] = l.l[0];
    }

    int len = 1;

    for (int i = 0; i < l.n; i++)
    {
        if (!in(u,l.l[i]))
        {
            u.l[len++] = l.l[i];
        }
        
    }

    int_list nu = {len,malloc(len*sizeof(int))};

    for (int i = 0; i < len; i++)
    {
        nu.l[i] = u.l[i];
    }

    free(u.l);
    return nu;
    
}

int index (int_list l, int e){
    for (int i = 0; i < l.n; i++)
    {
        if (l.l[i] == e)
        {
            return i;
            }
    }
    return -1;
}