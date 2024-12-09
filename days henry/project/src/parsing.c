#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/parsing.h"

sterr make_str_in_mat(char_matrix M, int expected_len,point deb,point dir){
    //check if it is even possible to read such a word
    char* word = malloc((expected_len + 1) * sizeof(char));
    
    if (!in_mat(deb, M) || !in_mat(add_points(deb,scale((expected_len-1),dir)),M))
    {
        sterr s = {word,0};
        return s;
    }
    if (!word)
    {
        perror("could not allocate memory for a word in matrix");
    }
    
    point curr;
    for (int i = 0; i < expected_len; i++)
    {   
        curr = add_points(deb,scale(i,dir));
        word[i] = M.mat[curr.i][curr.j];

    }
    word[expected_len] = '\0';
    
    sterr s = {word,1};
    return s;
    
}

char_matrix make_submat_in_mat(char_matrix M, point shape,point deb){
    char** matrix = malloc(shape.i*sizeof(char*));

    if (matrix == NULL)
    {
        perror("could not allocate space for matrix\n");
    }

    for (int i = 0; i < shape.i; i++)
    {
        matrix[i] = malloc(shape.j * sizeof(char));
        for (int j = 0; j < shape.j; j++)
        {
            matrix[i][j] = M.mat[deb.i + i][deb.j + j];
        }
        
    }
    
    char_matrix m = {shape.i,shape.j,matrix};

    return m;

}

int map_subwords(char_matrix M, int expected_len,int (*f)(char*)){
    point direction;
    sterr s;
    int total = 0;
    for (int k = 0; k < NUM_DIRECTIONS; k++)
    {
        direction = DIRECTIONS[k];
        for (int i = 0; i < M.n; i++)
        {
            for (int j = 0; j < M.m; j++)
            {   
                s = make_str_in_mat(M,expected_len,(point){i,j},direction);
                if (s.b)
                {
                    total += f(s.s);
                }
                free(s.s);
                
            }
            
        }
        

    }

    return total;
    
}

int map_submatrices(char_matrix M, point shape,int (*f)(char_matrix)){
    int total = 0;
    char_matrix m;
    for (int i = 0; i < M.n-shape.i + 1; i++)
    {
        for (int j = 0; j < M.m-shape.j + 1; j++)
        {
            m = make_submat_in_mat(M,shape,(point){i,j});
            total += f(m);
            free_mat(m);
        }
        
    }

    return total;
    
}

void map_int_list(int_list l,int (*f)(int)){
    for (int i = 0; i < l.n; i++)
    {
        l.l[i] = f(l.l[i]);
    }
    return;
}

int number_of_lines_with_commas(char * filename){
    FILE*f = fopen(filename,"r");

    // check that the file opened correctly

    if (f == NULL)
    {
        perror("could not open file");
    }

    char c;
    int n = 0;
    bool comma_on_curr_line = false;

    while (!feof(f))
    {
        if ((c = fgetc(f)) == ',' && !comma_on_curr_line)
        {
            comma_on_curr_line = true;
            n += 1;
        }
        else if (c == '\n')
        {
            comma_on_curr_line = false;
        }
        
    }

    fclose(f);

    return n;
}

int_list length_of_reports(char * filename){

    int len = number_of_lines_with_commas(filename);
    int* lr = malloc(len * sizeof(int));

    // specifically for the formating of AoC 2024 day 5

    FILE*f = fopen(filename,"r");

    if (f == NULL)
    {
        perror("could not open file");
    }

    char c;
    int n = 0,i = 0;
    bool in_report = false;

    while ((c = fgetc(f)) != EOF)
    {
        if (c == ',')
        {   
            in_report = true;
            n += 1;
        }
        else if (c == '\n' && in_report)
        {
            lr[i++] = n+1;
            n = 0;
            in_report = false;
        }
        
    }

    if (in_report)
    {
        lr[i] = n+1;
    }
    

    fclose(f);


    return (int_list){len,lr};

}

int_int_list fill_reports(char* filename){
    int_list lr = length_of_reports(filename);

    printf("there are %d reports, of lengths: \n",lr.n);
    print_int_list(lr);

    int**reports = malloc(lr.n*sizeof(int*));

    for (int i = 0; i < lr.n; i++)
    {
        reports[i] = malloc(lr.l[i] * sizeof(int));
    }

    FILE*f = fopen(filename,"r");

    if (f == NULL)
    {
        perror("could not open file");
    }

    char c;
    bool found = false, wasn = false;

    //finds where the reports start, it is where two \n follow
    while (!found && (c = fgetc(f)) != EOF)
    {   
        if (c == '\n'){
            if (wasn)
            {
                found = true;
            }
            else{
                wasn = true;
            }
        }
        else{
            wasn = false;
        }
    }

    if (!found)
    {
        printf("didnt find the pattern with two /n beside one another\n");
    }
    
    // fills the reports.

    int i = 0,j = 0;
    int temp = 0;
    bool in_number;

    while ((c = fgetc(f)) != EOF)
    {
        if (isdigit(c))
        {
            if (in_number)
            {
                temp *= 10;
                temp += c - '0'; // is like doing atoi(c)
            }
            else
            {   
                in_number = true;
                temp = c - '0';
            }
            
        }
        else if (in_number)
        {   
            reports[i][j++] = temp;
            in_number = false;
            if (j == lr.l[i])
            {
                i++;
                j = 0;
            }
            
        }

    }

    if (in_number)
    {
        reports[i][j] = temp; 
    }
    
    //build the int_int_list

    int_list* struc_reports = malloc(lr.n*sizeof(int_list));

    for (int i = 0; i < lr.n; i++)
    {
        struc_reports[i].n = lr.l[i];
        struc_reports[i].l = malloc(lr.l[i] * sizeof(int));
        for (int j = 0; j < lr.l[i]; j++)
        {
            struc_reports[i].l[j] = reports[i][j];
        }
        free(reports[i]);
    }

    free (lr.l);

    return (int_int_list){lr.n,struc_reports};
    
}