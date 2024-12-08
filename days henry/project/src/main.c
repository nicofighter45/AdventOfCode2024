#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"

// this code is not meant to be read, I have copied all the code from the libs, and chaged int for long long
// there is an x in front of every long long structure becuase there are already "l"s everywherea
//-----------------------------------------------------------------------------
struct xint_list{
    int n;
    long long* l;
};
typedef struct xint_list xint_list;

struct xint_int_list{
    int n;
    xint_list* ll;
};
typedef struct xint_int_list xint_int_list;
//----------------------------------------------------------------------------

// from files_utils ----------------------------------------------------------

xint_int_list text_to_xint_int_list(char* filename){

    int_list ln = nb_num_on_lines(filename);

    xint_list * ll = malloc (ln.n * sizeof(xint_list));;

    for (int i = 0; i < ln.n; i++)
    {
        ll[i].n = ln.l[i];
        ll[i].l = malloc(ln.l[i] * sizeof(long long));
    }

    FILE*f = fopen(filename,"r");

    // check that the file opened correctly

    if (f == NULL)
    {
        perror("could not open file");
    }


    int i = 0, j = 0;
    long long tempn = 0;
    char c;
    bool in_number = false;

    while ((c = fgetc(f)) != EOF)
    {
        if (isdigit(c))
        {
            if (in_number)
            {
                tempn *= 10;
                tempn += c - '0'; // is like doing atoi(c)
            }
            else
            {   
                in_number = true;
                tempn = c - '0';
            }
            
        }
        else if (in_number)
        {
            ll[i].l[j++] = tempn;
            in_number = false;
        }
        if (c == '\n')
        {
            ll[i++].l[j] = tempn;
            j = 0;
        }
        
    }

    if (in_number)
    {
        ll[i].l[j] = tempn; 
    }
    
    fclose(f);

    xint_int_list l = (xint_int_list){ln.n,ll};

    return l;
}

//-----------------------------------------------------------------------------------
//from struc funcs; : 

xint_list rm_elt_xl(xint_list l, int i){
    long long* new_l = malloc((l.n-1 )* sizeof(long long));
    int found = 0;
    for (int j = 0; j < l.n-1; j++)
    {
        found += (i == j);
        new_l[j] = l.l[j + found]; 
    }
    return (xint_list){l.n-1,new_l};
}

int digits_in(long long a){
    int i = 0;
    while (a > 0)
    {
        a = a/10;
        i++;
    }
    
    return i;
    
}
long long conc (long long a,long long b){
    int db = digits_in(b);
    for (int i = 0; i < db; i++)
    {
        a *= 10;
    }
    return a + b;
    
}

bool operate_report (xint_list report, long long start){
    if (report.n < 1)
    {
        perror ("report is to short\n");
        return false;
    }
    
    if (report.n == 1)
    {
        return report.l[0] == start ;
    }
    long long e = report.l[1];
    xint_list shorter_report = rm_elt_xl(report,1);

    int p = operate_report(shorter_report, e + start);
    int m = operate_report(shorter_report, e * start);
    int q = operate_report(shorter_report, conc(start,e));
    free (shorter_report.l);
    return m || p || q;
}



int main(){

    char* filename = "input.txt";
    xint_int_list L = text_to_xint_int_list(filename);

    long long e;

    long long total = 0;
    xint_list temp;

    for (int i = 0; i < L.n; i++)
    {
        temp = rm_elt_xl(L.ll[i],1);
        e = L.ll[i].l[1];
        if (operate_report(temp,e))
        {
            total += temp.l[0];
        }
        free(temp.l);
        printf("filed through report %d\n",i);
    }
    
    printf("%lld is the total\n",total);

    return 0;
}