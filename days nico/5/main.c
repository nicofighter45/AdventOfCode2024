#include "get_text_file.h"
#include <stdio.h>
#include <stdlib.h>
#include "printer.h"

int respectTheRule(Printable printable, Rule rule)
{
    for (int l = 0; l < printable.pages_count; l++)
    {
        if (printable.pages[l] == rule.first)
        {
            for (int k = 0; k < l; k++)
            {
                if (printable.pages[k] == rule.second)
                {
                    return 0;
                }
            }
        }
    }
    return -1;
}

int isCorrectlyPlace(Printer *printer, Printable printable)
{
    for (int j = 0; j < printer->rules_count; j++)
    {
        Rule rule = printer->rules[j];
        if (respectTheRule(printable, rule) == 0)
        {
            return j;
        }
    }
    return -1;
}

int getCorrectlyOrdered(Printer *printer)
{
    int total = 0;
    for (int i = 0; i < printer->printables_count; i++)
    {
        Printable printable = printer->printables[i];
        if (isCorrectlyPlace(printer, printable) == -1)
        {
            total += printable.pages[(printable.pages_count - 1) / 2];
        }
    }
    return total;
}

int getCorrected(Printer *printer)
{
    int total = 0;
    for (int i = 0; i < printer->printables_count; i++)
    {
        Printable printable = printer->printables[i];
        int j;
        while((j = isCorrectlyPlace(printer, printable)) != -1){
            Rule rule = printer->rules[j];
            for(int k = 0; k < printable.pages_count; k++){
                if(printable.pages[k] == rule.first){
                    printable.pages[k] = rule.second;
                }else if(printable.pages[k] == rule.second){
                    printable.pages[k] = rule.first;
                }
            }
        }
        total += printable.pages[(printable.pages_count - 1) / 2];
    }
    return total;
}

int main()
{
    File *file = createFile("input.txt");
    Printer *printer = createPrinter(file);
    int correct = getCorrectlyOrdered(printer);
    int incorrect = getCorrected(printer)-correct;
    printf("Correctly Ordered: %d\n", correct);
    printf("Incorrecly Ordered: %d\n", incorrect);
    return 1;
}
