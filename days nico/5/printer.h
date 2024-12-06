#pragma once
#include <stdlib.h>

typedef struct Rule {
    int first;
    int second;
} Rule;

typedef struct Printable {
    int* pages;
    int pages_count;
} Printable;

typedef struct Printer {
    Rule* rules;
    int rules_count;
    Printable* printables;
    int printables_count;
} Printer;

Rule* createRule(char* line, int size){
    Rule* rule = (Rule*)malloc(sizeof(Rule));
    char* buffer = (char*) malloc(size * sizeof(char));
    int decal = 0;
    for(int i = 0; i < size; i++){
        if(line[i] == '|'){
            rule->first = atoi(buffer);
            decal = i + 1;
            continue;
        }
        buffer[i - decal] = line[i];
    }
    rule -> second = atoi(buffer);
    return rule;
}

Printable* createPrintable(char* line, int size){
    Printable* printable = (Printable*)malloc(sizeof(Printable));
    printable->pages_count = 1;
    for(int i = 0; i < size; i++){
        if(line[i] == ','){
            printable->pages_count++;
        }
    }
    char* buffer = (char*) malloc(size * sizeof(char));
    printable->pages = (int*)malloc(printable->pages_count * sizeof(int));
    int decal = 0;
    int k = 0;
    for(int i = 0; i < size; i++){
        if(line[i] == ','){
            printable->pages[k++] = atoi(buffer);
            decal = i + 1;
            continue;
        }
        buffer[i - decal] = line[i];
    }
    printable -> pages[k] = atoi(buffer);
    return printable;
}

Printer* createPrinter(File* file){
    Printer *printer = malloc(sizeof(Printer));
    int delta = -1;
    for(int i = 0; i < file->lines; i++){
        if(file->size_of_line[i] == 0){
            delta = i;
            break;
        }
    }
    printer->rules_count = delta;
    printer->printables_count = file->lines - delta - 1;
    printer->rules = (Rule*)malloc(printer->rules_count * sizeof(Rule));
    printer->printables = (Printable*)malloc(printer->printables_count * sizeof(Printable));
    for(int i = 0; i < printer->rules_count; i++){
        printer->rules[i] = *createRule(file->matrice[i], file->size_of_line[i]);
    }
    for(int i = 0; i < printer->printables_count; i++){
        printer->printables[i] = *createPrintable(file->matrice[i + delta + 1], file->size_of_line[i + delta + 1]);
    }
    return printer;
}
