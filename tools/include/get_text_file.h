#include <stdlib.h>
#include <stdio.h>

typedef struct File
{
    char **matrice;
    int lines;
    char *size_of_line;
} File;

void printFile(File *file)
{
    for (int i = 0; i < file->lines; i++)
    {
        for (int j = 0; j < file->size_of_line[i]; j++)
        {
            printf("%c", file->matrice[i][j]);
        }
        printf("\n");
    }
}

File *createFile(char *name)
{
    FILE *file = fopen(name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
    }
    char ch;
    int lines = 1; //for the last line
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            lines += 1;
        }
    }
    fclose(file);
    file = fopen(name, "r");
    char **matrice = (char **)malloc(lines * sizeof(char *));
    char *size_of_lines = (char *)malloc(lines * sizeof(int));
    int line_length = 0;
    int i = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            matrice[i] = (char *)malloc(line_length * sizeof(char));
            size_of_lines[i] = line_length;
            line_length = 0;
            i++;
            continue;
        }
        line_length += 1;
    }
    matrice[i] = (char *)malloc(line_length * sizeof(char));
    size_of_lines[i] = line_length;
    fclose(file);
    file = fopen(name, "r");
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
    File *f = (File *)malloc(sizeof(File));
    f->matrice = matrice;
    f->lines = lines;
    f->size_of_line = size_of_lines;
    return f;
}