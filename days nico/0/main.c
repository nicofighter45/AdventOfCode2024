#include "get_text_file.h"
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int first(File file){
    int total = 0;
    return total;
}

int second(File file){
    int total = 0;
    return total;
}

int main(){
    File file = *createFile("input.txt");

    printf("First: %d\n", first(file));
    printf("Second: %d\n", second(file));

    return 1;
}