#include <stdlib.h>
#include <stdio.h>

int first(){
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    char ch;
    char *chars = malloc(1000 * sizeof(char));
    int total = 0;
    int state = 0;
    int i = 0;
    int j = 0;
    int l = 0;
    int a;
    while ((ch = fgetc(file)) != EOF)
    {
        chars[l] = ch;
        l++;
        if (l > 3 && chars[l - 1] == '(' && chars[l - 2] == 'l' && chars[l - 3] == 'u' && chars[l - 4] == 'm' && state == 0)
        {
            state = 1;
            l = 0;
        }
        else if (atoi(&ch) != 0 || ch == '0')
        {
            if (state == 1 && i < 3)
            {
                i++;
            }
            else if (state == 2 && j < 3)
            {
                j++;
            }
            else
            {
                state = 0;
                i = 0;
                j = 0;
                l = 0;
            }
        }
        else if (ch == ',' && state == 1)
        {
            a = atoi(chars);
            state = 2;
            l = 0;
        }
        else if (ch == ')' && state == 2)
        {
            total += a * atoi(chars);
            printf("%d %d\n", a, atoi(chars));
            i = 0;
            j = 0;
            l = 0;
            state = 0;
        }
        else
        {
            i = 0;
            j = 0;
            state = 0;
        }
    }

    fclose(file);
    free(chars);
    return total;
}

int second(){
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    char ch;
    char *chars = malloc(1000 * sizeof(char));
    int total = 0;
    int state = 0;
    int i = 0;
    int j = 0;
    int l = 0;
    int a;
    int enabled = 1;
    while ((ch = fgetc(file)) != EOF)
    {
        chars[l] = ch;
        l++;
        if(l > 3 && chars[l-1] == ')' && chars[l-2] == '(' && chars[l-3] == 'o' && chars[l-4] == 'd')
        {
            enabled = 1;
            l = 0;
            state = 0;
            i = 0;
            j = 0;
        }
        else if(l > 6 && chars[l-1] == ')' && chars[l-2] == '(' && chars[l-3] == 't' && chars[l-4] == '\''
        && chars[l-5] == 'n' && chars[l-6] == 'o' && chars[l-7] == 'd')
        {
            enabled = 0;
            l = 0;
            state = 0;
            i = 0;
            j = 0;
        }
        else if (enabled == 1 && l > 3 && chars[l - 1] == '(' && chars[l - 2] == 'l' && chars[l - 3] == 'u' && chars[l - 4] == 'm' && state == 0)
        {
            state = 1;
            l = 0;
        }
        else if (atoi(&ch) != 0 || ch == '0')
        {
            if (state == 1 && i < 3)
            {
                i++;
            }
            else if (state == 2 && j < 3)
            {
                j++;
            }
            else
            {
                state = 0;
                i = 0;
                j = 0;
                l = 0;
            }
        }
        else if (ch == ',' && state == 1)
        {
            a = atoi(chars);
            state = 2;
            l = 0;
        }
        else if (ch == ')' && state == 2)
        {
            total += a * atoi(chars);
            printf("%d %d\n", a, atoi(chars));
            i = 0;
            j = 0;
            l = 0;
            state = 0;
        }
        else
        {
            i = 0;
            j = 0;
            state = 0;
        }
    }

    fclose(file);
    free(chars);
    return total;
}

int main()
{
    

    printf("First: %d, Second: %d", first(), second());

    return 0;
}