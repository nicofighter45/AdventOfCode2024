#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool no_comma (char*s){
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ',')
        {
            return false;
        }
        
    }
    return true;
}

int num_from_list(int* num){
    int n = 0;
    for (int i = 0; i < 3; i++)
    {
        if (num[i] >= 0)
        {
        n*= 10;
        n += num[i];
        }
    }
    
    return n;
}

int mul (char* s){

    //if s looks like "mul(i1,i2)" it returns i1*i2, otherwise it returns 0

    if (strlen(s) < 8 || no_comma (s))
    {   printf("no comma or too short\n");
        return 0;
    }
    
    bool b = true;
    char*reference = "mul(";
    for (int i = 0; i < 4; i++)
    {
        if (reference[i] != s[i]){
            printf("no matching mul( pattern found\n");
            return 0;
        }
    }

    int k1 = 0;
    int num[3] = {-1,-1,-1};
    while (s[4 + k1] != ',')
    {
        if (!isdigit(s[4 + k1])){
            printf("read number is nor a digit nor a comma\n");
            return 0;}
        num[k1++] = s[4+k1];
    }
    
    int num1 = num_from_list(num);
    printf("first read number is %d\n",num1);

    int k2 = 0;
    num[0] = -1; num[1] = -1; num[2] = -1;
    printf("start of the second number :");
    while (s[5+k1+k2] !=')')
    {   
        if (!isdigit(s[5 +k1+k2])){return 0;}
        printf("%d",s[5+k1+k2]);
        num[k2++] = s[5+k1+k2];
    }
    
    int num2 = num_from_list(num);
    printf("second read number is %d\n",num2);

    if (!(6 + k1 + k2 == strlen(s) && s[strlen(s) - 1] == ')'))
    {
        return 0;
    }
    else
    {   printf("found match\n");
        return num1*num2;
    }

}

int main(int argc, char *argv[]){
    FILE *f = fopen(argv[1],"r");
    if (f == NULL)
    {
        perror("file failed to open");
    }

    char*s = "mul(12,1)";
    printf("result for %s is %d\n",s,mul(s));

    int m = 0;
    char c;
    while (!feof){
        c = fgetc(f);
        while (c != 'm')
        {
            c = fgetc(f);
        }
        char* mult = malloc(12*sizeof(char));
        int i = 0;
        while (i<12 && c!=')')
        {
            mult[i++] = c;
            c = fgetc(f);
        }
        if (c == ')')
        {
            m += mul(mult);
        }
        free(mult);
    }

    /*int i1,i2;

    while (fscanf(f,"mul(%d,%d)",&i1,&i2) == 2)
    {
        m+= i1*i2;
    }
    fclose(f); */

    printf("%d\n",m);
    return 0;
}