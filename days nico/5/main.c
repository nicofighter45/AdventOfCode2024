#include "get_text_file.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    File* file = createFile("test.txt");
    printFile(file);
    
    return 1;
}
