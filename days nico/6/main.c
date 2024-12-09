#include "get_text_file.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Pos
{
    int x;
    int y;
} Pos;

int main()
{
    File file = *createFile("input.txt");
    printf("%d %d", file.lines, file.size_of_line[0]);
    Matrix final_matrix = *create_matrix(file.lines, file.size_of_line[0]);
    Matrix matrix = *create_matrix(file.lines, file.size_of_line[0]);
    Pos mult = {0, 0};
    Pos pos = {-1, -1};
    for (int i = 0; i < file.lines; i++)
    {
        for (int j = 0; j < file.size_of_line[i]; j++)
        {
            final_matrix.data[i][j] = 0;
            if (file.matrice[i][j] == '.')
            {
                matrix.data[i][j] = 0;
            }
            else if (file.matrice[i][j] == '#')
            {
                matrix.data[i][j] = 1;
            }
            else
            {
                matrix.data[i][j] = 0;
                pos = (Pos){i, j};
                if (file.matrice[i][j] == '^')
                {
                    mult = (Pos){-1, 0};
                }
                else if (file.matrice[i][j] == 'v')
                {
                    mult = (Pos){1, 0};
                }
                else if (file.matrice[i][j] == '<')
                {
                    mult = (Pos){0, -1};
                }
                else if (file.matrice[i][j] == '>')
                {
                    mult = (Pos){0, 1};
                }
            }
        }
    }

    if ((mult.x == 0 && mult.y == 0) || (pos.x == -1 && pos.y == -1))
    {
        printf("No direction found\n");
        return 0;
    }

    final_matrix.data[pos.x][pos.y] = 1;
    int total = 1;
    while (0 < 1)
    {
        Pos next = {pos.x + mult.x, pos.y + mult.y};
        if (next.x < 0 || next.x >= file.lines || next.y < 0 || next.y >= file.size_of_line[0])
        {
            break;
        }
        if (matrix.data[next.x][next.y] == 1)
        {
            int temp = mult.x;
            mult.x = mult.y;
            mult.y = -temp;
            continue;
        }
        if(matrix.data[next.x][next.y] == 0)
        {
            if (final_matrix.data[next.x][next.y] == 0)
            {
                final_matrix.data[next.x][next.y] = 1;
                total++;
            }
            pos = next;
        }
    }

    printf("Total: %d\n", total);
    return 1;
}