#include "get_text_file.h"
#include <stdio.h>
#include <stdlib.h>
#include "printer.h"

int main(){
    File* file = createFile("input.txt");
    Printer *printer = createPrinter(file);
    int total = 0;
    for(int i = 0; i < printer->printables_count; i++){
        int souldBreak = 0;
        Printable printable = printer->printables[i];
        for(int j = 0; j < printer->rules_count; j++){
            Rule rule = printer->rules[j];
            for(int l = 0; l < printable.pages_count; l++){
                if(printable.pages[l] == rule.first){
                    for (int k = 0; k < l; k++){
                        if(printable.pages[k] == rule.second){
                            souldBreak = 1;
                            break;
                        }
                    }
                }
                if(souldBreak == 1){
                    break;
                }
            }
            if(souldBreak == 1){
                break;
            }
        }
        if(souldBreak == 0){
            //printf("should not break: %d %d\n", i, printable.pages[(printable.pages_count-1)/2]);
            total += printable.pages[(printable.pages_count-1)/2];
        }
    }
    printf("total: %d", total);
    return 1;
}
