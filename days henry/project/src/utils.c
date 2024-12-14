#include <stdlib.h>
#include <string.h>
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

bool char_in_str (char c,char* s,int len_s){
    for (int i = 0; i < len_s; i++)
    {
        if (c == s[i])
        {
            return true;
        }
        
    }
    return false;
}

point vect (point a, point b){
    return (point){b.i-a.i,b.j-a.j};
}

point * all_couples (int n){
    //see all couples as the sub_triangle of N^2 (there are n(n+1)/2)
    point * couples = malloc((n * (n - 1) / 2)* sizeof(point));
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            couples[k++] = (point){i,j};
        }
        
    }
    return couples;
}

int norm_sq (point v){
    return v.i*v.i+v.j*v.j;
}

char * rm_occ (char c,char* s){
    char *new_s = malloc((strlen(s)-1) * sizeof(char) + 1);
    int k = 0;
    int len_s = strlen(s);
    for (int i = 0; i < len_s; i++)
    {
        if (s[i] == c)
        {
            k ++;
        }
        else
        {
            new_s[i - k] = s[i];
        }
        
        
    }

    if (k == 0)
    {
        printf("character %c is not present in %s",c,s);
        return s;
    }
    new_s[strlen(s) - k] = '\0';
    free (s);
    return new_s;
}

int sum (int_list l){
    int total = 0;
    for (int i = 0; i < l.n; i++)
    {
        total += l.l[i];
    }
    return total;
    
}

int nb_digits(int a){
    int i = 0;
    while (a > 0)
    {
        a = a/10;
        i++;
    }
    
    return i;
}

int power(int a,int b){
    if (b < 0)
    {
        printf("tried a negative exponent\n");
    }
    int res = 1;
    for (int i = 0; i < b; i++)
    {
        res *= a;
    }
    return res;
}