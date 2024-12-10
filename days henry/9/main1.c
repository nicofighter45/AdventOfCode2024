#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"
#include "utils.h"

/**
 * to do list --------------------------------------:
 * 
 * 
 * in main.c : 
 * read file, 
 */


int_list files_sizes(char*filename){
    int n = nb_char(filename);
    if (n%2 == 1)
    {
        n ++;
    }
    int* files = malloc(sizeof(int) * n / 2);

    FILE*f = fopen(filename,"r");

    // check that the file opened correctly

    if (f == NULL)
    {
        perror("could not open file");
    }

    // read through the text to find the length of the files
    char c;
    for (int i = 0; i < n; i += 2)
    {
        c = fgetc(f);
        files[i/2] = c - '0';
        c = fgetc(f) ;
    }
    fclose(f);

    return (int_list){n/2,files};
}

int_list free_spaces(char*filename){
    int n = nb_char(filename);
    int* files = malloc(sizeof(int) * n / 2 );
    if (!files)
    {
        perror("could not allocate space for files");
    }
    
    FILE*f = fopen(filename,"r");

    // check that the file opened correctly

    if (f == NULL)
    {
        perror("could not open file");
    }

    // read through the text to find the length of the files
    char c;
    c = fgetc(f);
    for (int i = 0; i < n ; i += 2)
    {
        c = fgetc(f);
        files[i/2] = c - '0';
        c = fgetc(f) ;
    }

    fclose(f);

    return (int_list){n/2,files};
}



int main(){
    char * filename = "input.txt";
    int_list files = files_sizes(filename);
    int_list free_space = free_spaces(filename);

    /*for (int i = 0; i < files.n; i++)
    {
        for (int j = 0; j < files.l[i]; j++)
        {
            printf("%d",i);
        }
        for (int j = 0; j < free_space.l[i]; j++)
        {
            printf(".");
        }
        
        
    }
    printf("\n");*/
    int n = 0 ;
    for (int i = 0; i < files.n; i++)
    {
        n += files.l[i];
    }
    
    long total = 0;
    int pos = 0;
    int id_incr = 0, nb_incr = 0, nb_incr_temp = 0;
    int id_incr_fs = 0, nb_incr_temp_fs = 0;
    int id_desc = files.n - 1, nb_desc = 0 , nb_desc_temp = 0;
    bool in_free_space = false;

    while (nb_desc + nb_incr < n)
    {
        if (!in_free_space)
        {
            total += id_incr * pos;
            //printf("total: %d += %d * %d\n",total,pos,id_incr);
            //printf("%d",id_incr);
            nb_incr ++;
            nb_incr_temp ++;
            if (nb_incr_temp >= files.l[id_incr])
            {
                id_incr ++;
                nb_incr_temp = 0;
                in_free_space = true;
            }

        }
        else
        {
            if (free_space.l[id_incr_fs] == 0)
            {
                id_incr_fs ++;
                nb_incr_temp_fs = 0;
                in_free_space = false;
                pos -= 1;
            }
            else {
            total += id_desc * pos;
            //printf("%d",id_desc);
            //printf("total: %d += %d * %d\n",total,pos,id_desc);
            nb_desc ++;
            nb_desc_temp ++;
            nb_incr_temp_fs ++;
            if (nb_incr_temp_fs >= free_space.l[id_incr_fs])
            {
                id_incr_fs ++;
                nb_incr_temp_fs = 0;
                in_free_space = false;
            }
            if (nb_desc_temp >= files.l[id_desc])
            {
                id_desc -= 1;
                if (id_desc < 0)
                {
                    printf("iddesc = %d\n",id_desc);
                }
                
                nb_desc_temp = 0;
            }
            }

        }
        if (pos < 0)
        {
            printf("pos is %d\n",pos);
        }
        
        pos ++;
        
        
    }
    printf("\n");
    free(files.l);
    free(free_space.l);
    printf("total is %ld\n",total);
    
    printf("\n");
    return 0;

}