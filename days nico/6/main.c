#include "get_text_file.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Pos
{
    int x;
    int y;
} Pos;

int totalCase(File file, Matrix matrix, Matrix final_matrix, Pos pos, Pos mult)
{
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
        if (matrix.data[next.x][next.y] == 0)
        {
            if (final_matrix.data[next.x][next.y] == 0)
            {
                final_matrix.data[next.x][next.y] = 1;
                total++;
            }
            pos = next;
        }
    }
    return total;
}

int obstructions(File file, Matrix matrix, Pos pos, Pos mult)
{
    Pos ini = pos;
    Pos ini_mul = mult;
    int total = 0;
    for (int i = 0; i < file.lines; i++)
    {
        for (int j = 0; j < file.size_of_line[0]; j++)
        {
            if(matrix.data[i][j] == 1 || i == ini.x && j == ini.y){
                continue;
            }
            Pos change = {i, j};
            Matrix final_matrix = *create_matrix(file.lines, file.size_of_line[0]);
            for (int l = 0; l < file.lines; l++)
            {
                for (int m = 0; m < file.size_of_line[0]; m++)
                {
                    final_matrix.data[l][m] = 0;
                }
            }
            final_matrix.data[pos.x][pos.y] = 1;
            matrix.data[i][j] = 1;
            Pos last_seen = {-1, -1};
            Pos next_last_seen = {-1, -1};
            pos = ini;
            mult = ini_mul;
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
                if (matrix.data[next.x][next.y] == 0)
                {
                    if (final_matrix.data[next.x][next.y] == 0)
                    {
                        next_last_seen = (Pos){-1, -1};
                        last_seen = (Pos){-1, -1};
                        final_matrix.data[next.x][next.y] = 1;
                    }
                    else
                    {
                        if (next_last_seen.x == next.x && next_last_seen.y == next.y && last_seen.x == pos.x && last_seen.y == pos.y)
                        {
                            total += 1;
                            break;
                        }
                        if (last_seen.x == -1 && last_seen.y == -1)
                        {
                            last_seen = next;
                        }
                        else if (next_last_seen.x == -1 && next_last_seen.y == -1)
                        {
                            next_last_seen = next;
                        }
                    }
                    pos = next;
                }
            }
            matrix.data[i][j] = 0;

        }
    }
    return total;
}

int main()
{
    File file = *createFile("input.txt");
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

    printf("Obstructions: %d\n", obstructions(file, matrix, pos, mult));

    printf("Total: %d\n", totalCase(file, matrix, final_matrix, pos, mult));
    return 1;
}