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
    int last_int = atoi(fgetc(f));
    bool b = true;

    while (feof(f) != 0)
    {
        while (fgetc(f) != '\n')
        {
            temp = fgetc(f); // this will be a space
            temp = atoi(fgetc(f)); // this will be a number

            if (abs(temp - last_int) > 2)
            {
                b = false;
            }
            last_int = temp;
        }
        last_int = atoi(fgetc(f));
    }
    printf("%d", safe_reports);
    fclose(f);
    return 0;
}