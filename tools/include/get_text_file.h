#include <stdlib.h>
#include <stdio.h>

char** getChars(char* name){
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
    }
    char ch;
    int lines = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            lines += 1;
        }
    }
    fclose(file);
    file = fopen("input.txt", "r");
    char **matrice = (char **)malloc(lines * sizeof(char *));
    int line_length = 0;
    int i = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            matrice[i] = (char*) malloc(line_length * sizeof(char));
            line_length = 0;
            i++;
            continue;
        }
        line_length += 1;
    }
    i = 0;
    int j = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        
        if (ch == '\n')
        {
            j = 0;
            i++;
            continue;
        }
        matrice[i][j] = ch;
        j++;
    }

    fclose(file);
    return matrice;
}

