#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/files_utils.h"
#include "../include/common_structures.h"
#include "../include/utils.h"


int number_of_lines(char*filename){

    int n = 1;
    FILE*f = fopen(filename,"r");
    // check that the file opened correctly
    if (f == NULL)
    {
        perror("could not open file");
    }
    while (!feof(f))
    {
        if (fgetc(f) == '\n')
        {
            n += 1;
        }
        
    }
    
    return n;
}

int max_len_lines(char*filename){

    int m = 0, n = 0;
    FILE*f = fopen(filename,"r");
    // check that the file opened correctly
    if (f == NULL)
    {
        perror("could not open file");
    }
    while (!feof(f))
    {
        if (fgetc(f) != '\n')
        {
            n += 1;
        }
        else 
        {
            if (n > m)
            {
                m = n;
            }
            n = 0;
        }

    }

    return m;

}

char_matrix text_to_matrix(char*filename){

    // this works best if the input file is a rectangle, otherwise, some values will be meaningless.

    int n = number_of_lines(filename);
    int m = max_len_lines(filename);

    char** matrix = malloc(n*sizeof(char*));

    if (matrix == NULL)
    {
        perror("could not allocate space for matrix\n");
    }
    

    struct char_matrix M = 
    {
        n,m,matrix
    };
    

    for (int i = 0; i < n; i++)
    {
        matrix[i] = malloc(m * sizeof(char));
        if (matrix[i] == NULL)
        {
            perror("could not allocate space for matrix line\n");
        }
    }
    
    FILE*f = fopen(filename,"r");

    // check that the file opened correctly

    if (f == NULL)
    {
        perror("could not open file");
    }

    int i = 0, j = 0;
    char c;

    while ((c = fgetc(f)) != EOF)
    {
        if (c != '\n')
        {
            matrix[i][j] = c;
            j += 1;
        }
        else
        {
            i += 1;
            j = 0;
        }
        
    }

    // be careful to free all sub lists. 

    return M;

}

//does the exact same thing twice, its not that long
int_list all_num_in_text(char* filename){

    //first go round figures out how many numbers there are

    FILE*f = fopen(filename,"r");

    // check that the file opened correctly

    if (f == NULL)
    {
        perror("could not open file");
    }

    //here we go through the file

    int n = 0,tempn = 0;
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
            n += 1;
            in_number = false;
        }
        

    }

    if (in_number)
    {
        n += 1;
    }

    int * table = malloc(n*sizeof(int));

    rewind(f);

    int i = 0;
    tempn = 0;

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
            table[i++] = tempn;
            in_number = false;
        }
        

    }

    if (in_number)
    {
        table[i++] = tempn; 
    }
    
    fclose(f);

    int_list u = unique((int_list){n,table});
    free (table);

    return u;

}

graph text_to_graph(char* filename){
    //get number of elements and their values.
    int_list L = all_num_in_text(filename);

    // initialise adjacency matrix
    int ** adj_mat = malloc(L.n*sizeof(int*));
    if (adj_mat == NULL)
    {
        perror("could not allocate space for adjmat");
    }

    for (int i = 0; i < L.n; i++)
    {   
        adj_mat[i] = malloc(L.n*sizeof(int));
        if (adj_mat[i] == NULL)
        {
            perror("could not allocate space for adj_mat i");
        }
        
        for (int j = 0; j < L.n; j++)
        {
            adj_mat[i][j] = 0;
        }
        
    }

    //initializing the graph
    graph g = {L.n,L.l,adj_mat};
    

    FILE*f = fopen(filename,"r");

    // check that the file opened correctly

    if (f == NULL)
    {
        perror("could not open file");
    }

    int tempd1 = 0,tempd2 = 0;
    char c;
    /** these will let us know if we are in the middle of reading an arc pattern which is %d|%d
      * 0: we are not in a pattern
      * 1: we are reading d1
      * 2: we have read |
      * 3: we are reading d2
      */
    int pattern = 0;

    while ((c = fgetc(f)) != EOF)
    {
        if (isdigit(c))
        {   
            if (pattern == 0)
            {
                tempd1 = c - '0';
                pattern ++;
            }
            else if (pattern == 1)
            {
                tempd1 *= 10;
                tempd1 += c - '0';
            }
            else if (pattern == 2)
            {
                tempd2 = c - '0';
                pattern ++;
            }
            else if (pattern == 3)
            {
                tempd2 *= 10;
                tempd2 += c - '0';
            }
            else {
                printf("pattern number out of bounds [|0:3|] : %d\n",pattern);
            }

        }

        else if (c == '|' && pattern == 1)
        {
            pattern ++;
        }
        
        else if (pattern == 3)
        {   
            add_arc(g,index(L,tempd1),index(L,tempd2));
            pattern = 0;
        }

        else{
            pattern = 0;
        }
        

    }

    if (pattern == 3)
        {
            add_arc(g,index(L,tempd1),index(L,tempd2));
        }    

    return g;

}

int_list nb_num_on_lines(char* filename){
    int nb_lines = number_of_lines(filename);
    int_list ln = (int_list){nb_lines,malloc(nb_lines*sizeof(int))};

    FILE*f = fopen(filename,"r");

    // check that the file opened correctly

    if (f == NULL)
    {
        perror("could not open file");
    }

    //here we go through the file

    int i = 0,j = 0,tempn = 0;
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
            j += 1;
            in_number = false;
        }
        if (c == '\n')
        {   
            ln.l[i++] = j;
            j = 0;
        }
        

    }

    if (in_number)
    {
        j += 1;
        ln.l[i] = j;
    }
    

    return ln;



}


int_int_list text_to_int_int_list(char* filename){

    int_list ln = nb_num_on_lines(filename);
    

    int_list * ll = malloc (ln.n * sizeof(int_list));;

    for (int i = 0; i < ln.n; i++)
    {
        ll[i].n = ln.l[i];
        ll[i].l = malloc(ln.l[i] * sizeof(int));
    }

    FILE*f = fopen(filename,"r");

    // check that the file opened correctly

    if (f == NULL)
    {
        perror("could not open file");
    }


    int i = 0, j = 0, tempn = 0;
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

    int_int_list l = (int_int_list){ln.n,ll};

    return l;
}


int nb_char (char* filename){
    FILE*f = fopen(filename,"r");

    // check that the file opened correctly

    if (f == NULL)
    {
        perror("could not open file");
    }

    int n = 0;
    char c;
    while((c = fgetc(f) != EOF)){
        n ++;
    }

    return n;
    
}




















