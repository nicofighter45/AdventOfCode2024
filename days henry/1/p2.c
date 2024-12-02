#include <stdlib.h>
#include <stdio.h>

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

int *concatenate_two_int_lists(int *l1, int *l2, int len1, int len2)
{
    //printf("start of concatenation\n");
    int *L = malloc((len1 + len2) * sizeof(int));
    for (int i = 0; i < len1; i++)
    {
        L[i] = l1[i];
    }
    for (int i = 0; i < len2; i++)
    {
        L[len1 + i] = l2[i];
    }
    //printf("concatenation complete\n");
    free (l1);
    free (l2);
    return L;
}

int *quick_sort_concatenate(int *l1, int *l2, int pivot, int len1, int len2)
{
    //printf("start of concatenation\n");
    int *L = malloc((len1 + len2 + 1) * sizeof(int));
    for (int i = 0; i < len1; i++)
    {
        L[i] = l1[i];
    }

    L[len1] = pivot;

    for (int i = 0; i < len2; i++)
    {
        L[len1 + 1 + i] = l2[i];
    }
    //printf("concatenation complete\n");
    free (l1);
    free (l2);
    return L;
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

int *quick_sort(int *L, int len)
{
    if (len <= 1)
    {
        return L;
    }
    else
    {
        int pivot = L[0];
        int *l1 = malloc (len * sizeof(int));
        int *l2 = malloc (len * sizeof(int));
        int i1 = 0, i2 = 0, k;
        //printf("first loop\n");
        for (int i = 1; i < len; i++)
        {
            k = L[i];
            if (k <= pivot)
            {
                l1[i1++] = k;
            }
            else
            {
                l2[i2++] = k;
            }
        }
        //printf("the pivot is %d\n", pivot);
        //print_list(l1, i1);
        //print_list(l2, i2);

        int *lf = quick_sort_concatenate(quick_sort(l1, i1), quick_sort(l2, i2),pivot, i1, i2);

        return lf;
    }
}



int main(int argc, char *argv[])
{
    int n = number_of_lines_in_file(argv[1]);
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("did not managae to open the document\n");
    }

        int *l1 = malloc (n * sizeof(int));
        int *l2 = malloc (n * sizeof(int));

    int a,b;

    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d %d", &a, &b);
        l1[i] = a;
        l2[i] = b; 
    }
    
    l1 = quick_sort(l1, n);
    l2 = quick_sort(l2, n);

    int counter = 0;

    int i,k = 0;

    while (i < n && k < n)
    {
        while (k < n && l1[i] > l2[k])
        {
            k += 1; 
        }
        while (k < n && l1[i] == l2[k])
        {
            counter += l1[i];
            k += 1;
        }   
        i += 1;     
    }
    
    
    printf("%d", counter);
    free (l1);
    free (l2);

    return 0;
}