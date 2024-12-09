#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main(){
    FILE* f = fopen("input","r");
    if (f = NULL)
    {
        perror("did not manage to open file");
    }
    
    char c = fgetc(f);
    int n1 = 0,n2 = 0, m = 0;
    bool b = true;
    while (c != EOF)
    {
        if (c == 'm')
        {
            c = fgetc(f);
            if (c == 'u')
            {
                c = fgetc(f);
                if (c == 'l')
                {
                    c = fgetc(f);
                    if (c == '(')
                    {
                        c = fgetc(f);
                        while (isdigit(c))
                        {   
                            n1 *= 10;
                            n1 += c - '0';
                            c = fgetc(f);
                        }
                        if (c == ',')
                        {
                            c = fgetc(f);
                            while (isdigit(c))
                            {
                                n2 *= 10;
                                n2 += c - '0';
                                c = fgetc(f);
                            }
                            if (c == ')')
                            {
                                m += n1 * n2 * b;
                                b = true;
                            }
                        }
                        n1 = 0;
                        n2 = 0;
                        
                    }   
                }   
            }
        }
        else if (c == 'd')
        {
            if ((c = fgetc(f)) == 'o')
            {
                if ((c = fgetc(f)) == '(')
                {
                    if ((c = fgetc(f)) == ')')
                    {
                        //printf("found do()\n");
                        b = true;
                    }
                }
                else if (c == 'n')
                {
                    if ((c = fgetc(f)) == '\'')
                    {
                        if ((c = fgetc(f)) == 't')
                        {
                            if ((c = fgetc(f)) == '(')
                            {
                                if ((c = fgetc(f)) == ')')
                                {
                                    //printf("found don't()\n");
                                    b = false;
                                }
                            }
                        }
                    } 
                }
            }
        }
        else{c = fgetc(f);}
    }
    printf("the answer to the mul proglem is %d\n",m);
    fclose(f);
    return 0;
    
}