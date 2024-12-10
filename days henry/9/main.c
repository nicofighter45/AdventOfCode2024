#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common_structures.h"
#include "struc_funcs.h"
#include "files_utils.h"
#include "utils.h"


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

    // read through the text to find the length of the freespace.
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

int disk_size (int_list free_space,int_list file_size){
    return sum(free_space) + sum(file_size);
}

bool * used (int_list free_space,int_list file_size){
    int ds = disk_size(free_space,file_size);
    bool* is_used = malloc(ds * sizeof(bool));
    int k = 0;
    bool in_use = true;
    for (int i = 0; i < file_size.n; i ++)
    {
        for (int j = 0; j < file_size.l[i]; j++)
        {
            is_used[k++] = in_use;
        }
        in_use = !in_use;

        for (int j = 0; j < free_space.l[i]; j++)
        {
            is_used[k++] = in_use;
        }
        
        in_use = !in_use;
    }
    if (k != ds)
    {
        for (int j = 0; j < file_size.l[j]; j++)
        {
            is_used[k++] = in_use;
        }
    }
    
    return is_used;
}

int find_small_file(int_list file_size,int max_space, int id_fs){
    for (int i = 0; i < file_size.n - id_fs; i++)
    {
        if (file_size.l[file_size.n-i-1] <= max_space)
        {
            return i;
        }
        
    }

    return -1;
    
}

int_list fill_space(int_list free_space,int_list file_size, int id_fs){
    int rem = free_space.l[id_fs];
    int id_mv;
    while (rem > 0 && (id_mv = find_small_file(file_size,rem,id_fs)) != -1)
    {
        
    }
    
}



int main(){
    char * filename = "test.txt";
    int_list files = files_sizes(filename);
    int_list free_space = free_spaces(filename);

    int n = disk_size(free_space,files);
    printf("the size of the disk is %d\n",n);
    print_int_list(files);
    print_int_list(free_space);

    bool* is_used = used(free_space,files);

    for (int i = 0; i < n; i++)
    {
        printf("%d",is_used[i]);
    }
    printf("\n");
    return 0;

}