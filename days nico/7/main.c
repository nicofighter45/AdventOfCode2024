#include <stdlib.h>
#include <stdio.h>


typedef long long ulong;

ulong powlong(ulong base, ulong exp){
    if (exp == 0)
    {
        return 1;
    }
    return powlong(base, exp - 1) * base;
}

ulong **getValues(char *name)
{
    FILE *file = fopen(name, "r");
    char ch;
    char *buffer = malloc(10 * sizeof(char));
    ulong **values = (ulong **)malloc(850 * sizeof(ulong *));
    for (int i = 0; i < 850; i++)
    {
        values[i] = (ulong *)malloc(20 * sizeof(ulong));
    }
    int i = 0;
    int j = 1;
    int k = 0;
    while (0 < 1)
    {
        ch = fgetc(file);
        if (ch == ' ')
        {
            if (k == 0)
            {
                continue;
            }
            values[i][j++] = atoll(buffer);
        }
        else if (ch == '\n')
        {
            values[i][0] = j;
            values[i++][j] = atoll(buffer);
            j = 1;
        }
        else if (ch == EOF)
        {
            values[i][0] = j;
            values[i++][j] = atoll(buffer);
            break;
        }
        else if (ch == ':')
        {
            values[i][j++] = atoll(buffer);
        }
        else
        {
            buffer[k++] = ch;
            continue;
        }
        k = 0;
        buffer = (char *)malloc(10 * sizeof(char));
    }

    return values;
}

ulong get_sum_one(ulong **values, int size){
    ulong sum = 0;
    for (int i = 0; i < size; i++)
    {
        ulong size = values[i][0];
        ulong total = values[i][1];
        for (ulong k = 0; k < powlong(2, size-2); k++)
        {
            ulong calc = values[i][2];
            for (int j = 2; j < size; j++)
            {   
                if(k%powlong(2, j-1) < powlong(2, j-2)){
                    calc += values[i][j+1];
                }else{
                    calc *= values[i][j+1];
                }
            }
            if (calc == total)
            {
                sum += calc;
                break;
            }
        }
    }
    return sum;
}

int digits(ulong n){
    if(n < 10){
        return 1;
    }
    return digits(n/10) + 1;
}

ulong get_sum_two(ulong **values, int size){
    ulong sum = 0;
    for (int i = 0; i < size; i++)
    {
        ulong size = values[i][0];
        ulong total = values[i][1];
        for (ulong k = 0; k < powlong(3, size-2); k++)
        {
            ulong calc = values[i][2];
            for (int j = 2; j < size; j++)
            {   
                ulong ratio = k%powlong(3, j-1);
                ulong power = powlong(3, j-2);
                if(ratio < power){
                    calc += values[i][j+1];
                }else if(ratio < 2*power){
                    calc *= values[i][j+1];
                }else{
                    calc = calc*powlong(10,digits(values[i][j+1])) + values[i][j+1];
                }
            }
            if (calc == total)
            {
                sum += calc;
                break;
            }
        }
    }
    return sum;
}

int main()
{
    ulong **values = getValues("input.txt");
    int size = 850;
    
    ulong sum = get_sum_one(values, size);

    ulong sumsum = get_sum_two(values, size);

    printf("%lld\n", sumsum);

    return 1;
}
