#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (int argc, char *argv[]){
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("did not managae to open the document\n");
    }
    int safe_reports = 0;
    int temp;
    int last_int;
    fscanf(f,"%d",&last_int);
    bool b = true;
    

    while (!feof(f))
    {
        while (fgetc(f) != '\n')
        {
            fscanf(f,"%d",&temp); 

            if (abs(temp - last_int) > 3)
            {
                b = false;
            }
            last_int = temp;
        }
        fscanf(f,"%d",&last_int);
        if (!b)
        {
            safe_reports += 1;
        }
        b = true;
    }
    printf("%d", safe_reports);
    fclose(f);
    return 0;
}