#include <stdlib.h>
#include <stdio.h>

char **get_matrice(int size)
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
    }
    char ch;
    char **matrice = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++)
    {
        matrice[i] = malloc(size * sizeof(char));
    }
    int i = 0;
    int j = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            i++;
            j = 0;
            continue;
        }
        matrice[i][j] = ch;
        j++;
    }

    fclose(file);
    return matrice;
}

int vertical_and_horizontal(char y[], char **matrice, int size)
{
    int total = 0;
    int straight_k = 0;
    int reverse_straight_k = 3;
    int vertical_k = 0;
    int reverse_vertical_k = 3;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (y[straight_k] == matrice[i][j])
            {
                straight_k++;
                if (straight_k == 4)
                {
                    total += 1;
                    straight_k = 0;
                }
            }
            else
            {
                straight_k = 0;
            }
            if (y[reverse_straight_k] == matrice[i][j])
            {
                reverse_straight_k--;
                if (reverse_straight_k == -1)
                {
                    total += 1;
                    reverse_straight_k = 3;
                }
            }
            else
            {
                reverse_straight_k = 3;
            }
            if (y[vertical_k] == matrice[j][i])
            {
                vertical_k++;
                if (vertical_k == 4)
                {
                    total += 1;
                    vertical_k = 0;
                }
            }
            else
            {
                vertical_k = 0;
            }
            if (y[reverse_vertical_k] == matrice[j][i])
            {
                reverse_vertical_k--;
                if (reverse_vertical_k == -1)
                {
                    total += 1;
                    reverse_vertical_k = 3;
                }
            }
            else
            {
                reverse_vertical_k = 3;
            }
        }
        straight_k = 0;
        reverse_straight_k = 3;
        vertical_k = 0;
        reverse_vertical_k = 3;
    }
    return total;
}

int diagonal(char y[], char **matrice, int size)
{
    int total = 0;
    int diag_k = 0;
    int reverse_diag_k = 3;
    int other_diag_k = 0;
    int reverse_other_diag_k = 3;

    for (int i = -(size-1); i < size; i++)
    {
        for (int k = 0; k < size - abs(i); k++)
        {
            char c1;
            char c2;
            if (i >= 0)
            {
                c1 = matrice[k][k + i];
                c2 = matrice[k][size - 1 - k - i];
            }
            else
            {
                c1 = matrice[k - i][k];
                c2 = matrice[k - i][size - 1 - k];
            }

            if (y[diag_k] == c1)
            {
                diag_k++;
                if (diag_k == 4)
                {
                    total += 1;
                    diag_k = 0;
                }
            }
            else
            {
                diag_k = 0;
            }
            if (y[reverse_diag_k] == c1)
            {
                reverse_diag_k--;
                if (reverse_diag_k == -1)
                {
                    total += 1;
                    reverse_diag_k = 3;
                }
            }
            else
            {
                reverse_diag_k = 3;
            }
            if (y[other_diag_k] == c2)
            {
                other_diag_k++;
                if (other_diag_k == 4)
                {
                    total += 1;
                    other_diag_k = 0;
                }
            }
            else
            {
                other_diag_k = 0;
            }
            if (y[reverse_other_diag_k] == c2)
            {
                reverse_other_diag_k--;
                if (reverse_other_diag_k == -1)
                {
                    total += 1;
                    reverse_other_diag_k = 3;
                }
            }
            else
            {
                reverse_other_diag_k = 3;
            }
        }
        int diag_k = 0;
        int reverse_diag_k = 3;
        int other_diag_k = 0;
        int reverse_other_diag_k = 3;
    }
    return total;
}

int main()
{
    int size = 140;
    char **matrice = get_matrice(size);

    int total = 0;
    char y[] = {'X', 'M', 'A', 'S'};

    total += vertical_and_horizontal(y, matrice, size);
    printf("Total:%d", total);
    total += diagonal(y, matrice, size);

    printf("Total:%d", total);

    return 0;
}