#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"

// this uses ints, but we need to use long longs for it to work, :( so its time to recode everything

bool operate_report (int_list report, int start){
    if (report.n < 1)
    {
        perror ("report is to short\n");
        return false;
    }
    
    if (report.n == 1)
    {
        return report.l[0] == start ;
    }
    int e = report.l[1];
    int_list shorter_report = rm_elt_l(report,1);

    int m = operate_report(shorter_report, e * start);
    int p = operate_report(shorter_report, e + start);
    free (shorter_report.l);
    return m || p;
}

int main(){
    char* filename = "input.txt";
    int_int_list L = text_to_int_int_list(filename);

    int e;

    int total = 0;
    int_list temp;

    for (int i = 0; i < L.n; i++)
    {
        printf("report i is :\n");
        print_int_list(L.ll[i]);
        temp = rm_elt_l(L.ll[i],1);
        e = L.ll[i].l[1];
        if (operate_report(temp,e))
        {
            total += temp.l[0];
            printf("%d is valid\n", temp.l[0]);
            printf("curr total is %d\n",total);
        }
        free(temp.l);
        printf("filed through report %d\n",i);
    }
    
    printf("%d is the total\n",total);

    free_ii_list(L);

    printf("freeing worked \n");
    return 0;
}