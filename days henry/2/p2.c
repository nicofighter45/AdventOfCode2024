#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int number_of_lines_in_file(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("did not managae to open the document\n");
    }
    int number_of_lines = 0;

    while (!feof(f))
    {
        if (fgetc(f) == '\n')
        {
            number_of_lines += 1;
        }
    }
    fclose(f);
    return number_of_lines;
}

bool is_safe (int* report, int len){
    if (len <= 1)
    {
        return true;
    }
    int last_int = report [0], next_int = 0, diff = 0;
    
    bool desc = true, incr = true;

    for (int i = 1; i < len; i++)
    {
        next_int = report[i];
        diff = next_int - last_int;

        if (abs(diff) > 3)
        {   //printf("this report is not safe because the differeance betaween %d and %d is over 3\n",last_int,next_int);
            return false;
        }
        desc = desc && diff > 0;
        incr = incr && diff < 0;
        last_int = next_int;
    }

    return (incr || desc);
    
}

int* report_no_jth (int* report, int len, int j){
    int *new_report = malloc ((len-1)*sizeof(int));
    /*copying the report without the j_th entry*/

    for (int a = 0; a < j; a++)
    {
        new_report[a] = report[a];
    }
    for (int a = j; a < len-1; a++)
    {
        new_report[a] = report[a+1];
    }
    return new_report;

}

void print_list(int *L, int len)
{
    if (len < 1)
    {
        printf("tried printing a list of len <= 0\n");
    }

    for (int i = 0; i < len - 1; i++)
    {
        printf("%d,", L[i]);
    }
    printf("%d\n", L[len - 1]);

    return;
}

int main (int argc, char *argv[]){

    int n = (number_of_lines_in_file(argv[1]));
    int * lengths_of_reports = malloc (n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        lengths_of_reports[i] = 0;
    }
    

    FILE *f1 = fopen(argv[1], "r");
    if (f1 == NULL)
    {
        printf("did not managae to open the document\n");
    }
    int temp;
    for (int i = 0; i < n; i++)
    {
        while (fgetc(f1) != '\n')
        {
            fscanf(f1,"%d",&temp); 
            lengths_of_reports [i] += 1;
        }
    }

    fclose(f1);


    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("did not managae to open the document\n");
    }


    bool safe = false;
    int safe_reports = 0;
    int len;

    for (int i = 0; i < 20; i++)
    {
        len = lengths_of_reports[i];
        int* i_th_report = malloc(len * sizeof(int));
   
        for (int k = 0; k < len; k++)
        {
            fscanf(f,"%d",&i_th_report[k]);
        }
        printf("this is report %d\n",i);
        print_list (i_th_report,len);


        if (is_safe(i_th_report,len))
        {
            safe = true;
        }
        else{
            
            for (int j = 0; j < len; j++){
                int* report_no_jth_elt = report_no_jth(i_th_report,len,j);
                safe = safe || is_safe(report_no_jth_elt,len-1);
                
                free (report_no_jth_elt);
            }
        
        }
        if (safe) {safe_reports += 1;}

        safe = false;
        free(i_th_report);
    }
    printf("%d\n",safe_reports);
    free(lengths_of_reports);
    fclose(f);
    return 0;
}
